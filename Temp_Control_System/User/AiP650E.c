#include "ch32x035_rcc.h"
#include "AiP650E.h"
#include "ch32x035_gpio.h"
#include "debug.h"

/*********************************************************************
 * @fn      IIC_Init
 *
 * @brief   Initializes the IIC peripheral.
 *
 * @return  none
 */
void soft_AiP650E_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure={0};
    RCC_APB2PeriphClockCmd( soft_iic_RCC, ENABLE );

    GPIO_InitStructure.GPIO_Pin = soft_iic_SCL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( soft_iic_SCL_port, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = soft_iic_SDA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( soft_iic_SDA_port, &GPIO_InitStructure );

    GPIO_SetBits(soft_iic_SCL_port, soft_iic_SCL);
    GPIO_SetBits(soft_iic_SDA_port, soft_iic_SDA);

}

void AiP650E_START(void)
{
    GPIO_SetBits(soft_iic_SCL_port, soft_iic_SCL);
    GPIO_SetBits(soft_iic_SDA_port, soft_iic_SDA);
    Delay_Us(DelayHalfTimes_us);
    GPIO_ResetBits(soft_iic_SDA_port, soft_iic_SDA);
    Delay_Us(DelayHalfTimes_us);
}

void AiP650E_STOP(void)
{
    Delay_Us(DelayHalfTimes_us);
    Delay_Us(DelayHalfTimes_us);
    GPIO_SetBits(soft_iic_SCL_port, soft_iic_SCL);
    Delay_Us(DelayHalfTimes_us); //
    GPIO_ResetBits(soft_iic_SDA_port, soft_iic_SDA);
    Delay_Us(DelayHalfTimes_us);
    GPIO_SetBits(soft_iic_SDA_port, soft_iic_SDA);
    Delay_Us(DelayHalfTimes_us);
}

u8 AiP650E_waitACK(void)
{
    u8 res = {0};
    GPIO_InitTypeDef GPIO_InitStructure={0};
    GPIO_InitStructure.GPIO_Pin = soft_iic_SDA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( soft_iic_SDA_port, &GPIO_InitStructure );

    GPIO_ResetBits(soft_iic_SCL_port, soft_iic_SCL);
    Delay_Us(DelayHalfTimes_us);
//  Delay_Us(DelayHalfTimes_us);

    GPIO_SetBits(soft_iic_SCL_port, soft_iic_SCL);
    Delay_Us(DelayHalfTimes_us);
    GPIO_ReadInputDataBit(soft_iic_SDA_port, soft_iic_SDA);
    Delay_Us(DelayHalfTimes_us);

    GPIO_ResetBits(soft_iic_SCL_port, soft_iic_SCL);

    GPIO_InitStructure.GPIO_Pin = soft_iic_SDA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( soft_iic_SDA_port, &GPIO_InitStructure );
    GPIO_ResetBits(soft_iic_SDA_port, soft_iic_SDA);

    return res;
}

void AiP650E_send_ACK(void)
{
    GPIO_ResetBits(soft_iic_SCL_port, soft_iic_SCL);
    GPIO_ResetBits(soft_iic_SDA_port, soft_iic_SDA);
    Delay_Us(DelayHalfTimes_us);
    GPIO_SetBits(soft_iic_SCL_port, soft_iic_SCL);
    Delay_Us(DelayHalfTimes_us);
    GPIO_ResetBits(soft_iic_SCL_port, soft_iic_SCL);
    Delay_Us(DelayHalfTimes_us);
}

/*********************************************************************
 * @fn      AiP_Write
 *
 * @brief   Initializes the IIC peripheral.
 *
 * @return  none
 */
void soft_AiP650E_Write(u8 i2c_data_output)
{
    for(u8 i = 0; i < 8; ++i )
    {
        GPIO_ResetBits(soft_iic_SCL_port, soft_iic_SCL);
        Delay_Us(DelayHalfTimes_us);

        if(i2c_data_output & 0x80) 
        {
            GPIO_SetBits(soft_iic_SDA_port, soft_iic_SDA);
        } else {
            GPIO_ResetBits(soft_iic_SDA_port, soft_iic_SDA);
        }

        i2c_data_output <<= 1;
        Delay_Us(DelayHalfTimes_us);

        GPIO_SetBits(soft_iic_SCL_port, soft_iic_SCL);
        Delay_Us(DelayHalfTimes_us);
        Delay_Us(DelayHalfTimes_us);
    }

    GPIO_ResetBits(soft_iic_SCL_port, soft_iic_SCL);
}

u8 soft_AiP650E_Read(void)
{
    u8 res = {0};

//    GPIO_SetBits(soft_iic_SDA_port, soft_iic_SDA);
    GPIO_InitTypeDef GPIO_InitStructure={0};
    GPIO_InitStructure.GPIO_Pin = soft_iic_SDA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( soft_iic_SDA_port, &GPIO_InitStructure );


    for(u8 i = 0; i < 8; ++i )
    {
        res <<= 1;
        GPIO_ResetBits(soft_iic_SCL_port, soft_iic_SCL);
        Delay_Us(DelayHalfTimes_us);
        Delay_Us(DelayHalfTimes_us);

        GPIO_SetBits(soft_iic_SCL_port, soft_iic_SCL);
        Delay_Us(DelayHalfTimes_us);
        if(GPIO_ReadInputDataBit(GPIOA, soft_iic_SDA)) 
        {
            res |= 0x01;
        }
        Delay_Us(DelayHalfTimes_us);
    }

    GPIO_ResetBits(soft_iic_SCL_port, soft_iic_SCL);

    GPIO_InitStructure.GPIO_Pin = soft_iic_SDA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( soft_iic_SDA_port, &GPIO_InitStructure );
    GPIO_SetBits(soft_iic_SDA_port, soft_iic_SDA);


    return res;
}



