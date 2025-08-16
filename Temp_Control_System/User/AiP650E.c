#include "ch32x035_rcc.h"
#include "AiP650E.h"
#include "ch32x035_gpio.h"
#include "debug.h"

char Dig_Number[10] = {
    0b00111111,      // 0
    0b00000110,      // 1
    0b01011011,      // 2
    0b01001111,      // 3
    0b01100110,      // 4
    0b01101101,      // 5
    0b01111101,      // 6
    0b00000111,      // 7
    0b01111111,      // 8
    0b01101111,      // 9
};
char Dig_Letter[4] = {
    0b01110111,      // A
    0b00111001,      // C
    0b01111001,      // E
    0b01110001,      // F
};

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

//  GPIO_SetBits(soft_iic_SDA_port, soft_iic_SDA);
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


/*********************************************************************
 * @fn      AiP_Display
 *
 * @brief   Start display.
 *
 * @return  void
 */
static void AiP_Display()
{
AiP650E_START();
soft_AiP650E_Write(0x48);
AiP650E_waitACK();
soft_AiP650E_Write(0x71);
AiP650E_waitACK();
AiP650E_STOP();
}


/*********************************************************************
 * @fn      AiP_Temp2Array
 *
 * @brief   change short to Array of Number .
 *
 * @return  void
 */
void AiP_Temp2Array(u8 *arr,u16 temp)
{
    arr[0] = Dig_Letter[1];                 // C
    arr[1] = Dig_Number[temp%10];
    arr[2] = Dig_Number[temp/10%10];
}


/*********************************************************************
 * @fn      AiP_PWM2Array
 *
 * @brief   change short to Array of Number .
 *
 * @return  void
 */
void AiP_PWM2Array(u8 *arr, u16 PWM)
{
    PWM = PWM * 100 / 1200;
    arr[0] = Dig_Number[PWM%10];
    arr[1] = Dig_Number[PWM/10%10];
    arr[2] = Dig_Number[PWM/100%10];
}


/*********************************************************************
 * @fn      AiP_Mode2Array
 *
 * @brief   change short to Array of Number .
 *
 * @return  void
 */
void AiP_Mode2Array(u8 *arr, u8 mode)
{
    arr[0] = Dig_Number[mode];
    arr[1] = Dig_Number[mode];
    arr[2] = Dig_Number[mode];
}


/*********************************************************************
 * @fn      AiP650E_Write_Number
 *
 * @brief   change short to Array of Number .
 *
 * @return  void
 */
void AiP650E_Display_Number(u8 *arr)
{
    AiP650E_START();
    soft_AiP650E_Write(0x68);
    AiP650E_waitACK();
    soft_AiP650E_Write(0xFF);
    AiP650E_waitACK();
    AiP650E_STOP();

    AiP650E_START();
    soft_AiP650E_Write(0x6A);
    AiP650E_waitACK();
    soft_AiP650E_Write(arr[2]);
    AiP650E_waitACK();
    AiP650E_STOP();

    AiP650E_START();
    soft_AiP650E_Write(0x6C);
    AiP650E_waitACK();
    soft_AiP650E_Write(arr[1]);
    AiP650E_waitACK();
    AiP650E_STOP();

    AiP650E_START();
    soft_AiP650E_Write(0x6E);
    AiP650E_waitACK();
    soft_AiP650E_Write(arr[0]);
    AiP650E_waitACK();
    AiP650E_STOP();

    AiP_Display();
}


/*********************************************************************
 * @fn      AiP650E_Fresh
 *
 * @brief   change short to Array of Number .
 *
 * @return  void
 */
void AiP650E_Fresh()
{
    u8 AiP_fresh[] = {0xFF, 0xFF, 0xFF};
    AiP650E_Display_Number(AiP_fresh);
    AiP_Display();
}


/*********************************************************************
 * @fn      AiP650E_Return_KEY
 *
 * @brief   .
 *
 * @return  void
 */
u8 AiP650E_Return_KEY()
{
    u8 Aip_temp = 0;
    AiP650E_START();
    soft_AiP650E_Write(0x49);
    AiP650E_waitACK();
    Aip_temp = soft_AiP650E_Read();
    AiP650E_waitACK();
    AiP650E_STOP();

    return Aip_temp;
}
