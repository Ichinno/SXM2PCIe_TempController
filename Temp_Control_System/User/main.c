/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Yaohui
 * Version            : V1.1.0
 * Date               : 2025/08/16
 * Description        : Main program body.
 *******************************************************************************/

#include "debug.h"
#include "math.h"
#include "AiP650E.h"
#include "pwm_utils.h"
#include "display_utils.h"
#include "button_utils.h"

// 系统电压定义，用于温度计算
#define Voltage 3.3

// Flash存储地址和大小定义
#define Fadr    0x0800F700    // Flash存储地址
#define Fsize   (256>>2)      // Flash存储大小：256字节/4 = 64个32位整数
// 初始化缓冲区，第一个值为0x02（默认模式），其余为0xFF
u32 buf[Fsize] = {  0x02, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF  };





/*********************************************************************
 * @fn      ADC_Function_Init
 *
 * @brief   Initializes ADC collection.
 *
 * @return  none
 */
// ADC功能初始化函数
// 功能：配置ADC1用于温度采集，使用GPIOA的Pin1作为模拟输入
void ADC_Function_Init(void)
{
    ADC_InitTypeDef  ADC_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // 使能GPIOA和ADC1的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    // 配置GPIOA的Pin1为模拟输入模式（连接NTC热敏电阻）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;    // 模拟输入模式
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 复位ADC1到默认状态
    ADC_DeInit(ADC1);

    // 配置ADC时钟为6分频
    ADC_CLKConfig(ADC1, ADC_CLK_Div6);

    // 配置ADC参数
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;           // 独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;                // 禁用扫描模式
//    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;         // 连续转换模式（已注释）
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;          // 单次转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;       // 右对齐数据
    ADC_InitStructure.ADC_NbrOfChannel = 1;                      // 1个转换通道
    ADC_Init(ADC1, &ADC_InitStructure);

    // 启用ADC和DMA
    ADC_DMACmd(ADC1, ENABLE);    // 启用DMA传输
    ADC_Cmd(ADC1, ENABLE);       // 启用ADC
}


/*********************************************************************
 * @fn      Get_ADC_Val
 *
 * @brief   Returns ADCx conversion result data.
 *
 * @param   ch - ADC channel.
 *            ADC_Channel_0 - ADC Channel0 selected.
 *            ADC_Channel_1 - ADC Channel1 selected.
 *            ADC_Channel_2 - ADC Channel2 selected.
 *            ADC_Channel_3 - ADC Channel3 selected.
 *            ADC_Channel_4 - ADC Channel4 selected.
 *            ADC_Channel_5 - ADC Channel5 selected.
 *            ADC_Channel_6 - ADC Channel6 selected.
 *            ADC_Channel_7 - ADC Channel7 selected.
 *            ADC_Channel_8 - ADC Channel8 selected.
 *            ADC_Channel_9 - ADC Channel9 selected.
 *            ADC_Channel_10 - ADC Channel10 selected.
 *            ADC_Channel_11 - ADC Channel11 selected.
 *            ADC_Channel_12 - ADC Channel12 selected.
 *            ADC_Channel_13 - ADC Channel13 selected.
 *            ADC_Channel_14 - ADC Channel14 selected.
 *            ADC_Channel_15 - ADC Channel15 selected.
 *
 * @return  none
 */
// 获取ADC转换值的函数
// 功能：读取指定ADC通道的转换结果
// 参数：ch - ADC通道号（0-15）
// 返回值：ADC转换结果（12位，0-4095）
u16 Get_ADC_Val(u8 ch)
{
    u16 val;

    // 配置ADC通道和采样时间
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_11Cycles);
    // 启动软件转换
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    // 等待转换完成（轮询方式）
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    // 读取转换结果
    val = ADC_GetConversionValue(ADC1);

    return val;
}


/*********************************************************************
 * @fn      ADC2TEMP
 *
 * @brief   Change ADC RAW DATA to digital Temperature.
 *
 * @return  none
 */
// ADC值转温度函数
// 功能：将ADC原始数据转换为温度值（摄氏度）
// 参数：Temp_ADC - ADC原始值, Vcc - 系统电压
// 返回值：温度值（摄氏度）
u16 ADC2TEMP(u16 Temp_ADC, float Vcc)
{
    // 将ADC值转换为电压值（12位ADC，满量程4095）
    float U_Temp = (float)Temp_ADC/4095*Vcc;
    // 根据分压电路计算NTC热敏电阻阻值
    // 电路：Vcc -> 11K电阻 -> NTC -> 2.2K电阻 -> GND
    float Rth = 11000/U_Temp-2200;
    // 使用Steinhart-Hart方程计算温度
    // 这是NTC热敏电阻的标准温度计算公式
    float temp = 1/(1/(273.15+25)+1/3985.85*log(Rth/10000))-273.15;

    return floor(temp);    // 返回向下取整的温度值
}





/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
// 主函数 - 温度控制系统的核心程序
// 功能：实现基于NTC热敏电阻的温度测量和PWM输出控制
 int main(void)
{
    // 变量定义和初始化
    u16 Temper_ADC= 0;                  // 温度转换值
    u8  KEY_SCAN = 0x00;                // 按键事件
    u8  arr[3] = {0};                   // 数组
    u8  Temper_Curve_Mode = 0x01;       // 温度曲线模式
    _Bool Display_Temper_OR_PWM = 0;     // 显示切换标志：0显示温度，1显示PWM
    u8 COUNT_Display_Temper_OR_PWM = 0;  // 显示切换计数器

    // 系统初始化阶段
    SystemCoreClockUpdate();             // 更新系统时钟
    Delay_Init();                       // 延时函数初始化
    USART_Printf_Init(115200);          // 串口初始化，波特率115200
    TIM1_PWMOut_Init(1200, 2-1, 600);   // PWM初始化（周期1200，预分频1，占空比600）
    ADC_Function_Init();                // ADC初始化
    soft_AiP650E_Init();                // I2C初始化（用于数码管显示）

    // 重新配置PWM参数
    TIM1_PWMOut_Init(1200, 2-1, 1200);  // PWM设置（最大占空比）
    AiP650E_Fresh();                    // 数码管刷新初始化
    Delay_Ms(1000);                     // 延时1秒

    // 从Flash读取温度控制模式配置
    Temper_Curve_Mode = button_get_mode();  // 从Flash读取模式值
    buf[0] =  *(u32 *)(Fadr);           // 同步到缓冲区
    printf("Temp:Mode=%d\r\n", Temper_Curve_Mode);
    
    // 验证模式值是否有效，如果无效则使用默认模式0x02
    if (!button_is_valid_mode(Temper_Curve_Mode))
    {
        button_set_default_mode();       // 设置默认模式
        Temper_Curve_Mode = button_get_mode(); // 重新读取
    }
    
    // 显示当前模式
    AiP_Mode2Array(arr, Temper_Curve_Mode);  // 将模式转换为显示数组
    AiP650E_Display_Number(arr);             // 在数码管上显示模式
    Delay_Ms(1000);                          // 延时1秒

    // 主循环 - 温度控制系统的核心逻辑
    while(1)
    {
        // 按键检测和处理
        KEY_SCAN = AiP650E_Return_KEY();     // 扫描按键状态
        if(button_process_key(KEY_SCAN))     // 如果检测到有效按键
        {
            button_switch_mode();             // 切换模式
            
            button_save_config();             // 保存新模式到Flash
            Temper_Curve_Mode = button_get_mode(); // 重新读取模式值
            printf("Temp:Mode=%d\r\n", Temper_Curve_Mode);

            // 显示新选择的模式
            AiP_Mode2Array(arr, Temper_Curve_Mode);
            AiP650E_Display_Number(arr);
        }

        Delay_Ms(1000);                     // 延时1秒
        
        // 温度测量和PWM控制
        Temper_ADC = Get_ADC_Val(ADC_Channel_1);  // 读取ADC通道1的温度值
        // 根据温度计算PWM值并更新输出
        TIM1_PWMOut_Init(1200, 2-1, calculatePWM(Temper_ADC, Voltage, Temper_Curve_Mode));

        // 根据显示标志选择显示内容
        if(Display_Temper_OR_PWM)
        {
            AiP_Temp2Array(arr, ADC2TEMP(Temper_ADC, Voltage));
            AiP650E_Display_Number(arr);
            display_increment_counter(&COUNT_Display_Temper_OR_PWM);
        }
        else if(!Display_Temper_OR_PWM)
        {
            AiP_PWM2Array(arr, calculatePWM(Temper_ADC, Voltage, Temper_Curve_Mode));
            AiP650E_Display_Number(arr);
            display_increment_counter(&COUNT_Display_Temper_OR_PWM);
        }

        // 增加计数器并检查是否需要切换显示模式
        if(display_is_time_to_switch(COUNT_Display_Temper_OR_PWM))
        {
            display_reset_counter(&COUNT_Display_Temper_OR_PWM);
            display_toggle_mode(&Display_Temper_OR_PWM);
        }
    }
}