#pragma once
#ifndef __AiP650E_H__
#define __AiP650E_H__
#endif

#include "ch32x035.h"

#define soft_iic_RCC RCC_APB2Periph_GPIOA

#define soft_iic_SCL_port GPIOA
#define soft_iic_SDA_port GPIOA

#define soft_iic_SCL GPIO_Pin_10
#define soft_iic_SDA GPIO_Pin_11

#define DelayHalfTimes_us 5

void soft_AiP650E_Init();
void AiP650E_START();
void AiP650E_STOP(void);
u8 AiP650E_waitACK(void);
void soft_AiP650E_Write(u8 i2c_data_output);
u8 soft_AiP650E_Read(void);
