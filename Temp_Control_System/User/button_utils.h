/********************************** (C) COPYRIGHT *******************************
 * File Name          : button_utils.h
 * Author             : Yaohui
 * Version            : V1.1.0
 * Date               : 2025/08/16
 * Description        : Button utility functions header.
 *******************************************************************************/

#ifndef __BUTTON_UTILS_H
#define __BUTTON_UTILS_H

#include "ch32x035.h"

// Flash相关函数声明
// Flash快速读取函数
void Flash_Read_Fast(void);

// Flash快速写入函数
void Flash_Write_Fast(void);

// 按键相关函数声明
// 按键检测和模式切换函数
// 参数：key_scan - 按键扫描值
// 返回值：1表示按键被按下并处理，0表示无按键或按键无效
u8 button_process_key(u8 key_scan);

// 模式切换函数
void button_switch_mode(void);

// 保存配置到Flash函数
void button_save_config(void);

// 从Flash读取配置函数
// 返回值：从Flash读取的模式值
u8 button_get_mode(void);

// 验证模式值是否有效函数
// 参数：mode - 要验证的模式值
// 返回值：1表示有效，0表示无效
u8 button_is_valid_mode(u8 mode);

// 设置默认模式函数
void button_set_default_mode(void);

#endif
