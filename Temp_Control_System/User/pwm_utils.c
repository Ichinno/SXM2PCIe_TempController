/********************************** (C) COPYRIGHT *******************************
 * File Name          : pwm_utils.c
 * Author             : Yaohui
 * Version            : V1.1.0
 * Date               : 2025/08/16
 * Description        : PWM utility functions.
 *******************************************************************************/

#include "debug.h"
#include "math.h"

// 系统电压定义，用于温度计算
#define Voltage 3.3

/* PWM Output Mode Definition */
// PWM输出模式定义
#define PWM_MODE1   0    // PWM模式1
#define PWM_MODE2   1    // PWM模式2

/* PWM Output Mode Selection */
// PWM输出模式选择
//#define PWM_MODE PWM_MODE1
#define PWM_MODE PWM_MODE2    // 当前使用PWM模式2

/* PWM Supersede Mode Enable Definition*/
// PWM替代模式使能定义
#define PWM_SPE_MODE_DISABLE   0    // 禁用替代模式
#define PWM_SPE_MODE_ENABLE    1    // 启用替代模式

/* PWM Supersede Mode Enable Selection */
// PWM替代模式使能选择
#define PWM_SPE_MODE   PWM_SPE_MODE_DISABLE    // 当前禁用替代模式
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
// TIM1 PWM输出初始化函数
// 参数说明：
// arr: 自动重装值，决定PWM周期
// psc: 预分频值，决定PWM频率
// ccp: 捕获比较值，决定PWM占空比
void TIM1_PWMOut_Init(u16 arr, u16 psc, u16 ccp)
{
	GPIO_InitTypeDef GPIO_InitStructure={0};
	TIM_OCInitTypeDef TIM_OCInitStructure={0};
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

	// 使能GPIOB和TIM1的时钟
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_TIM1, ENABLE );

	// 配置GPIOB的Pin9为复用推挽输出模式（用于PWM输出）
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // 50MHz速度
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	// 配置定时器时间基准
	TIM_TimeBaseInitStructure.TIM_Period = arr;                    // 设置周期值
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;                // 设置预分频值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;   // 时钟分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
	TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStructure);

	// 根据选择的PWM模式配置输出比较模式
#if (PWM_MODE == PWM_MODE1)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;    // PWM模式1

#elif (PWM_MODE == PWM_MODE2)
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;  // PWM模式2

#endif

	// 配置PWM输出参数
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  // 启用输出
	TIM_OCInitStructure.TIM_Pulse = ccp;                          // 设置脉冲值（占空比）
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     // 输出极性为高
	TIM_OC1Init( TIM1, &TIM_OCInitStructure );                    // 初始化通道1

	// 如果启用替代模式，配置替代功能
#if (PWM_SPE_MODE == PWM_SPE_MODE_ENABLE)
	TIM_OC12_SupersedeModeCmd( TIM1, TIM_Supersede_Mode_OC1_H, TIM_Supersede_Mode_OC2_H, ENABLE);
#endif

	// 启用PWM输出和定时器
	TIM_CtrlPWMOutputs(TIM1, ENABLE );                    // 启用PWM输出
	TIM_OC1PreloadConfig( TIM1, TIM_OCPreload_Disable ); // 禁用通道1预装载
	TIM_ARRPreloadConfig( TIM1, ENABLE );                 // 启用自动重装预装载
	TIM_Cmd( TIM1, ENABLE );                              // 启用定时器
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
// 根据温度计算PWM值的函数
// 参数说明：
// Temp_ADC: ADC采集的温度原始值
// Vcc: 系统电压
// mode: 温度控制模式（0,1,2三种模式）
// 返回值: 计算出的PWM值
 u16 calculatePWM(u16 Temp_ADC, float Vcc, u8 mode) {
    u16 pwm = 0;
    
    // 三种模式的温度下限值（摄氏度）
    u16 LL[3] = { 55, 50, 45};
    // 三种模式的温度上限值（摄氏度）
    u16 UL[3] = { 90, 80, 70};
    // 三种模式的斜率系数
    short k[3] = { 15, 20, 22};
    // 三种模式的截距系数
    short b[3] = { -350, -400, -400};

	// 将ADC值转换为电压值
	float U_Temp = (float)Temp_ADC/4095*Vcc;
	// 根据电压计算NTC热敏电阻阻值
	float Rth = 11000/U_Temp-2200;
	// 使用Steinhart-Hart方程计算温度（摄氏度）
	float temp = 1/(1/(273.15+25)+1/3985.85*log(Rth/10000))-273.15;

    // 根据温度范围计算PWM值
    if (temp < LL[mode]) {
        // 温度过低时，使用下限温度计算PWM（最小输出）
        pwm = k[mode] * LL[mode] + b[mode];
    } else if (temp > UL[mode]) {
        // 温度过高时，输出最大PWM值
        pwm = 1200;
    } else {
        // 温度在正常范围内时，使用线性公式计算PWM
        pwm = k[mode] * temp + b[mode];
    }
    

//	printf("U_Temp: %f\r\n", U_Temp);
//	printf("Rth: %d\r\n", (int)Rth);
//	printf("Temp: %d\r\n", (int)temp);
//	printf("PWM: %04d\r\n", pwm);
//	printf("Mode: %04d\r\n", mode);
    return pwm;
}
