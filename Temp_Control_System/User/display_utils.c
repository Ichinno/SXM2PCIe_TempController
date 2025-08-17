/********************************** (C) COPYRIGHT *******************************
 * File Name          : display_utils.c
 * Author             : Yaohui
 * Version            : V1.1.0
 * Date               : 2025/08/16
 * Description        : Display utility functions.
 *******************************************************************************/

#include "display_utils.h"

// 显示切换逻辑函数
// 功能：增加显示计数器
// 参数：count - 指向计数器的指针
void display_increment_counter(u8 *count)
{
    (*count)++;
}

// 显示切换逻辑函数
// 功能：检查是否到了切换显示的时间
// 参数：count - 计数器值
// 返回值：1表示需要切换，0表示不需要切换
_Bool display_is_time_to_switch(u8 count)
{
    return (count == 5);
}

// 显示切换逻辑函数
// 功能：重置显示计数器
// 参数：count - 指向计数器的指针
void display_reset_counter(u8 *count)
{
    *count = 0;
}

// 显示切换逻辑函数
// 功能：切换显示模式
// 参数：display_flag - 指向显示标志的指针
void display_toggle_mode(_Bool *display_flag)
{
    *display_flag = !(*display_flag);
}
