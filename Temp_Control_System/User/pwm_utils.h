/********************************** (C) COPYRIGHT *******************************
 * File Name          : pwm_utils.h
 * Author             : Yaohui
 * Version            : V1.1.0
 * Date               : 2025/08/16
 * Description        : PWM utility functions header.
 *******************************************************************************/

#ifndef __PWM_UTILS_H
#define __PWM_UTILS_H

#include "ch32x035.h"

// PWM相关函数声明
// TIM1 PWM输出初始化函数
// 参数：arr-周期值, psc-预分频值, ccp-脉冲值（占空比）
void TIM1_PWMOut_Init(u16 arr, u16 psc, u16 ccp);

// 根据温度计算PWM值的函数
// 参数：Temp_ADC-ADC温度值, Vcc-系统电压, mode-控制模式(0,1,2)
// 返回值：计算出的PWM值
u16 calculatePWM(u16 Temp_ADC, float Vcc, u8 mode);

#endif
