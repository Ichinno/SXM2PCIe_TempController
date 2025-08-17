/********************************** (C) COPYRIGHT *******************************
 * File Name          : display_utils.h
 * Author             : Yaohui
 * Version            : V1.1.0
 * Date               : 2025/08/16
 * Description        : Display utility functions header.
 *******************************************************************************/

#ifndef __DISPLAY_UTILS_H
#define __DISPLAY_UTILS_H

#include "ch32x035.h"

// 显示切换逻辑函数声明
// 增加显示计数器
void display_increment_counter(u8 *count);

// 检查是否到了切换显示的时间
_Bool display_is_time_to_switch(u8 count);

// 重置显示计数器
void display_reset_counter(u8 *count);

// 切换显示模式
void display_toggle_mode(_Bool *display_flag);

#endif
