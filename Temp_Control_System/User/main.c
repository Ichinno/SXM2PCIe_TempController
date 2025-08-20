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
#include "button_utils.h"
#include "adc_utils.h"

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
            COUNT_Display_Temper_OR_PWM++;  // 直接增加计数器
        }
        else if(!Display_Temper_OR_PWM)
        {
            AiP_PWM2Array(arr, calculatePWM(Temper_ADC, Voltage, Temper_Curve_Mode));
            AiP650E_Display_Number(arr);
            COUNT_Display_Temper_OR_PWM++;  // 直接增加计数器
        }

        // 检查是否需要切换显示模式（每5秒切换一次）
        if(COUNT_Display_Temper_OR_PWM == 5)
        {
            COUNT_Display_Temper_OR_PWM = 0;  // 重置计数器
            Display_Temper_OR_PWM = !Display_Temper_OR_PWM;  // 切换显示模式
        }
    }
}