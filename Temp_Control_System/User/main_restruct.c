/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Yaohui
 * Version            : V1.1.0
 * Date               : 2025/08/16
 * Description        : Main program body.
 *******************************************************************************/

#include "debug.h"
#include "math.h"
#include "AiP650E.h"


/* PWM Output Mode Definition */
#define PWM_MODE1   0
#define PWM_MODE2   1

/* PWM Output Mode Selection */
//#define PWM_MODE PWM_MODE1
#define PWM_MODE PWM_MODE2

/* PWM Supersede Mode Enable Definition*/
#define PWM_SPE_MODE_DISABLE   0
#define PWM_SPE_MODE_ENABLE    1

/* PWM Supersede Mode Enable Selection */
#define PWM_SPE_MODE   PWM_SPE_MODE_DISABLE
//#define PWM_SPE_MODE   PWM_SPE_MODE_ENABLE


/*********************************************************************
 * @fn      TIM1_PWMOut_Init
 *
 * @brief   Initializes TIM1 output compare.
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *          ccp - the pulse value.
 *
 * @return  none
 */
void TIM1_PWMOut_Init(u16 arr, u16 psc, u16 ccp)
{
	GPIO_InitTypeDef GPIO_InitStructure={0};
	TIM_OCInitTypeDef TIM_OCInitStructure={0};
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_TIM1, ENABLE );

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStructure);

#if (PWM_MODE == PWM_MODE1)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;

#elif (PWM_MODE == PWM_MODE2)
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;

#endif

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = ccp;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init( TIM1, &TIM_OCInitStructure );

#if (PWM_SPE_MODE == PWM_SPE_MODE_ENABLE)
	TIM_OC12_SupersedeModeCmd( TIM1, TIM_Supersede_Mode_OC1_H, TIM_Supersede_Mode_OC2_H, ENABLE);
#endif

	TIM_CtrlPWMOutputs(TIM1, ENABLE );
	TIM_OC1PreloadConfig( TIM1, TIM_OCPreload_Disable );
	TIM_ARRPreloadConfig( TIM1, ENABLE );
	TIM_Cmd( TIM1, ENABLE );
}


/*********************************************************************
 * @fn      ADC_Function_Init
 *
 * @brief   Initializes ADC collection.
 *
 * @return  none
 */
void ADC_Function_Init(void)
{
    ADC_InitTypeDef  ADC_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_DeInit(ADC1);

    ADC_CLKConfig(ADC1, ADC_CLK_Div6);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
//    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);
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
u16 Get_ADC_Val(u8 ch)
{
    u16 val;

    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_11Cycles);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
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
u16 ADC2TEMP(u16 Temp_ADC, float Vcc)
{
    float U_Temp = (float)Temp_ADC/4095*Vcc;
	float Rth = 11000/U_Temp-2200;
	float temp = 1/(1/(273.15+25)+1/3985.85*log(Rth/10000))-273.15;

    return floor(temp);
}


/*********************************************************************
 * @fn      calculatePWM
 *
 * @brief   Calculate PWM from Temperature.
 *
 * @param   Temper - Temperatur from NTC.
 *          pwm - Frequency.
 *
 * @return  pwm
 */
 u16 calculatePWM(u16 Temp_ADC, float Vcc) {
    u16 pwm = 0;
	float U_Temp = (float)Temp_ADC/4095*Vcc;
	float Rth = 11000/U_Temp-2200;
	float temp = 1/(1/(273.15+25)+1/3985.85*log(Rth/10000))-273.15;

    if (temp < 50) {
        pwm = 600;
    } else if (temp > 80) {
        pwm = 1200;
    } else {
        pwm = 20 * temp - 400;
    }
    

//	printf("U_Temp: %f\r\n", U_Temp);
//	printf("Rth: %d\r\n", (int)Rth);
//	printf("Temp: %d\r\n", (int)temp);
//	printf("PWM: %04d\r\n", pwm);
    return pwm;
}


/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
 int main(void)
{
    u16 Temper_ADC= 0;                  // 温度中转值
    u8  KEY_SCAN = 0x00;                // 按键事件
    u8  arr[3] = {0};                   // 显存
    u8  Temper_Curve_Mode = 0xFF;       // 温度曲线模式

    SystemCoreClockUpdate();
    Delay_Init();                       // 延时函数初始化
    TIM1_PWMOut_Init(1200, 2-1, 600);   // PWM初始化
    ADC_Function_Init();                // ADC初始化
    soft_AiP650E_Init();                // I2C初始化
    AiP650E_Fresh();

    while(1);

}