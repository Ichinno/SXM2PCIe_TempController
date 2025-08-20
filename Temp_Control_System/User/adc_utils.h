/********************************** (C) COPYRIGHT *******************************
 * File Name          : adc_utils.h
 * Author             : Yaohui
 * Version            : V1.1.0
 * Date               : 2025/08/16
 * Description        : ADC utility functions header.
 *******************************************************************************/

#ifndef __ADC_UTILS_H
#define __ADC_UTILS_H

#include "ch32x035.h"

// ADC相关函数声明

// ADC功能初始化函数
// 功能：配置ADC1用于温度采集，使用GPIOA的Pin1作为模拟输入
void ADC_Function_Init(void);

// 获取ADC转换值的函数
// 功能：读取指定ADC通道的转换结果
// 参数：ch - ADC通道号（0-15）
// 返回值：ADC转换结果（12位，0-4095）
u16 Get_ADC_Val(u8 ch);

// ADC值转温度函数
// 功能：将ADC原始数据转换为温度值（摄氏度）
// 参数：Temp_ADC - ADC原始值, Vcc - 系统电压
// 返回值：温度值（摄氏度）
u16 ADC2TEMP(u16 Temp_ADC, float Vcc);

#endif
