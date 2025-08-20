/********************************** (C) COPYRIGHT *******************************
 * File Name          : adc_utils.c
 * Author             : Yaohui
 * Version            : V1.1.0
 * Date               : 2025/08/16
 * Description        : ADC utility functions.
 *******************************************************************************/

#include "debug.h"
#include "math.h"
#include "adc_utils.h"

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
