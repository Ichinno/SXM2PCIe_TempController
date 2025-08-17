/********************************** (C) COPYRIGHT *******************************
 * File Name          : button_utils.c
 * Author             : Yaohui
 * Version            : V1.1.0
 * Date               : 2025/08/16
 * Description        : Button utility functions.
 *******************************************************************************/

#include "button_utils.h"
#include "debug.h"

// Flash存储地址和大小定义
#define Fadr    0x0800F700    // Flash存储地址
#define Fsize   (256>>2)      // Flash存储大小：256字节/4 = 64个32位整数

// 外部缓冲区声明
extern u32 buf[Fsize];

/*********************************************************************
 * @fn      Flash_Read_Fast
 *
 * @brief   Flash Fast Program Test.
 *
 * @return  none
 */
// Flash快速读取函数
// 功能：从指定地址读取Flash数据到缓冲区
void Flash_Read_Fast(void)
{
//    u32 i;
//    u8 Verify_Flag = 0;
//    FLASH_Status s;

    printf("Read flash\r\n");
//    for(i=0; i<Fsize; i++){
//        printf("adr-%08x v-%08x\r\n", Fadr +4*i, *(u32*)(Fadr +4*i));
//    }
    // 读取Flash地址Fadr处的数据
    printf("adr-%08x v-%08x\r\n", Fadr, *(u32*)Fadr);

    // 将读取的数据存储到缓冲区
    buf[0] =  *(u32*)Fadr;
}

/*********************************************************************
 * @fn      Flash_Write_Fast
 *
 * @brief   Flash Fast Program Test.
 *
 * @return  none
 */
// Flash快速写入函数
// 功能：将缓冲区数据写入Flash，包含擦除、写入和验证步骤
void Flash_Write_Fast(void)
{
//    u32 i;
    u8 Verify_Flag = 0;
    FLASH_Status s;

    // 第一步：擦除Flash扇区
    s = FLASH_ROM_ERASE(Fadr, Fsize*4);
    if(s != FLASH_COMPLETE)
    {
        printf("check FLASH_ADR_RANGE_ERROR FLASH_ALIGN_ERROR or FLASH_OP_RANGE_ERROR\r\n");
        return;
    }

    printf("Erase flash\r\n");
    printf("adr-%08x v-%08x\r\n", Fadr, *(u32*)Fadr);

    // 第二步：写入数据到Flash
    s = FLASH_ROM_WRITE( Fadr, buf, Fsize*4);

    if(s != FLASH_COMPLETE)
    {
        printf("check FLASH_ADR_RANGE_ERROR FLASH_ALIGN_ERROR or FLASH_OP_RANGE_ERROR\r\n");
        return;
    }

    printf("Write flash\r\n");
    printf("adr-%08x v-%08x\r\n", Fadr, *(u32*)Fadr);

    // 第三步：验证写入是否成功
    if(buf[0] == *(u32 *)(Fadr))
    {
        Verify_Flag = 0;    // 验证成功
    }
    else
    {
        Verify_Flag = 1;    // 验证失败
    }
    

    // 输出验证结果
    if(Verify_Flag)
        printf("%d Byte Verify Fail\r\n", (Fsize*4));
    else
        printf("%d Byte Verify Suc\r\n", (Fsize*4));
}

// 按键检测和模式切换函数
// 功能：检测按键并处理模式切换
// 参数：key_scan - 按键扫描值
// 返回值：1表示按键被按下并处理，0表示无按键或按键无效
u8 button_process_key(u8 key_scan)
{
    if(key_scan == 0x46)    // 如果检测到按键0x46
    {
        return 1;    // 返回1表示按键被处理
    }
    return 0;    // 返回0表示无按键或按键无效
}

// 模式切换函数
// 功能：将当前模式切换到下一个模式
// 参数：无
// 返回值：无
void button_switch_mode(void)
{
    buf[0]++;                        // 模式值加1
    // 模式值循环：0->1->2->0
    if (!((buf[0]==0x00)||(buf[0]== 0x01)||(buf[0]==0x02)))
        buf[0] = 0x00;
}

// 保存配置到Flash函数
// 功能：将当前配置保存到Flash存储器
// 参数：无
// 返回值：无
void button_save_config(void)
{
    Flash_Write_Fast();              // 保存新模式到Flash
}

// 从Flash读取配置函数
// 功能：从Flash读取配置并返回模式值
// 参数：无
// 返回值：从Flash读取的模式值
u8 button_get_mode(void)
{
    return (u8)(*(u32 *)(Fadr));    // 从Flash地址读取模式值
}

// 验证模式值是否有效函数
// 功能：检查模式值是否在有效范围内
// 参数：mode - 要验证的模式值
// 返回值：1表示有效，0表示无效
u8 button_is_valid_mode(u8 mode)
{
    return ((mode==0x00)||(mode==0x01)||(mode==0x02));
}

// 设置默认模式函数
// 功能：当模式值无效时，设置默认模式
// 参数：无
// 返回值：无
void button_set_default_mode(void)
{
    buf[0] = 0x02;                  // 设置默认模式
    Flash_Write_Fast();              // 写入Flash
}
