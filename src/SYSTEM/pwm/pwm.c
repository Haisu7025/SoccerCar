#include "pwm.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//定时器 驱动代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/4
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.1 20120904
//1,增加TIM3_PWM_Init函数。
//2,增加LED0_PWM_VAL宏定义，控制TIM3_CH2脉宽
//////////////////////////////////////////////////////////////////////////////////

//TIM3 PWM部分初始化
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);						 //使能定时器3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE); //使能GPIO外设时钟

	//输出TIM3 CH3的PWM脉冲波形	GPIOB.0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;		//TIM3_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化GPIO

	//输出TIM3 CH4的PWM脉冲波形	GPIOB.1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM3_CH4
	GPIO_Init(GPIOB, &GPIO_InitStructure);	//初始化GPIO

	//输出TIM3 CH1的PWM脉冲波形	GPIOA.6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM3_CH4
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//初始化GPIO

	//输出TIM3 CH2的PWM脉冲波形	GPIOA.7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM3_CH4
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//初始化GPIO

	//初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr;						//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;					//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);				//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	//初始化TIM3 Channel1234 PWM模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;			  //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	 //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);					  //根据T指定的参数初始化外设TIM3 OC1
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);					  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);					  //根据T指定的参数初始化外设TIM3 OC3
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);					  //根据T指定的参数初始化外设TIM3 OC4

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能TIM3在CCR1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能TIM3在CCR2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能TIM3在CCR3上的预装载寄存器
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能TIM3在CCR3上的预装载寄存器

	TIM_Cmd(TIM3, ENABLE); //使能TIM3

	TIM_SetCompare1(TIM3, 0);
	TIM_SetCompare2(TIM3, 0);
	TIM_SetCompare3(TIM3, 0);
	TIM_SetCompare4(TIM3, 0);
}

void set_speed_left(s32 speed)
{
	if (speed >= 0 && speed <= 10000)
	{
		TIM_SetCompare1(TIM3, speed);
		TIM_SetCompare2(TIM3, 0);
	}
	else if (speed < 0 && speed >= -10000)
	{
		TIM_SetCompare1(TIM3, 0);
		TIM_SetCompare2(TIM3, -speed);
	}
}

void set_speed_right(s32 speed)
{
	if (speed >= 0 && speed <= 10000)
	{
		TIM_SetCompare3(TIM3, speed);
		TIM_SetCompare4(TIM3, 0);
	}
	else if (speed < 0 && speed >= -10000)
	{
		TIM_SetCompare3(TIM3, 0);
		TIM_SetCompare4(TIM3, -speed);
	}
}
