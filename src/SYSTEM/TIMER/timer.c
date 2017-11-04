#include "timer.h"
#include "usart.h"
#include "state.h"
#include "ultrasonic.h"
#include "I2C_MPU6050.h"

//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//定时器 驱动代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!

void TIM6_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //时钟使能

	//定时器TIM6初始化
	TIM_TimeBaseStructure.TIM_Period = arr;						//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;					//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);				//根据指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE); //使能指定的TIM6中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;			  //TIM6中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);							  //初始化NVIC寄存器

	TIM_Cmd(TIM6, ENABLE); //使能TIMx
}

void TIM5_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //时钟使能

	//定时器TIM6初始化
	TIM_TimeBaseStructure.TIM_Period = arr;						//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;					//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);				//根据指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); //使能指定的TIM6中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;			  //TIM6中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;		  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);							  //初始化NVIC寄存器

	TIM_Cmd(TIM5, ENABLE); //使能TIMx
}

void TIM7_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //时钟使能

	//定时器TIM6初始化
	TIM_TimeBaseStructure.TIM_Period = arr;						//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;					//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);				//根据指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE); //使能指定的TIM6中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;			  //TIM6中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;		  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);							  //初始化NVIC寄存器

	TIM_Cmd(TIM7, ENABLE); //使能TIMx
}

void TIM6_IRQHandler(void) //TIM6中断
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查TIM6更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //清除TIMx更新中断标志
		//TODO:TIM6 interruption

		//speed-1:
		*speed1 = (u16)((s16)(TIM2->CNT));
		//speed-2:
		*speed2 = (u16)((s16)(TIM4->CNT));
		TIM2_Encoder_Write(0);
		TIM4_Encoder_Write(0);

		adj_spd(NULL, &surface_speed1, *speed1, target_speed1, 0);
		adj_spd(NULL, &surface_speed2, *speed2, target_speed2, 1);

		ZA = GetData(ACCEL_ZOUT_H);
		ZW = GetData(GYRO_ZOUT_H);
	}
}

void TIM5_IRQHandler(void)
{
	u16 len = 0, t = 0;
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //检查TIM6更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update); //清除TIMx更新中断标志
		//TODO:TIM5 interruption
		//recive usart message
		if (USART_RX_STA & 0x8000)
		{
			len = USART_RX_STA & 0x3fff; //得到此次接收到的数据长度
			for (t = 0; t < len; t++)
			{
				usart_msg[t] = USART_RX_BUF[t]; //向串口1发送数据
			}
			USART_RX_STA = 0;
		}
	}
}

void TIM7_IRQHandler(void) //TIM6中断
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查TIM6更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //清除TIMx更新中断标志
		Ultra_Ranging(&distance);
	}
}

void TIM2_Encoder_Init(u16 arr, u16 psc)
{
	RCC->APB1ENR |= 1 << 0; //TIM2时钟使能
	RCC->APB2ENR |= 1 << 2; //使能PORTA时钟

	// GPIOA->CRL &= 0XFFFFFF00; //PA0、PA1 清除之前设置
	GPIOA->CRL |= 0X00000044; //PA0、PA1 浮空输入

	TIM2->ARR = arr; //设定计数器自动重装值
	TIM2->PSC = psc; //预分频器

	TIM2->CCMR1 |= 1 << 0; //输入模式，IC1FP1映射到TI1上
	TIM2->CCMR1 |= 1 << 8; //输入模式，IC2FP2映射到TI2上
	TIM2->CCER |= 0 << 1;  //IC1不反向
	TIM2->CCER |= 0 << 5;  //IC2不反向
	TIM2->SMCR |= 3 << 0;  //所用输入均在上升沿或下降沿有效
	TIM2->CR1 |= 1 << 0;   //使能计数器
}

void TIM4_Encoder_Init(u16 arr, u16 psc)
{
	RCC->APB1ENR |= 1 << 2; //TIM4时钟使能
	RCC->APB2ENR |= 1 << 3; //使能PORTA时钟

	// GPIOA->CRL &= 0XFFFFFF00;
	GPIOA->CRL |= 0x44000000; //PB6、PA7 浮空输入

	TIM4->ARR = arr; //设定计数器自动重装值
	TIM4->PSC = psc; //预分频器

	TIM4->CCMR1 |= 0x4141;
	TIM4->CCER |= 0x11;
	TIM4->SMCR |= 3 << 0; //所用输入均在上升沿或下降沿有效
	TIM4->CR1 |= 1 << 0;  //使能计数器
}

void TIM2_Encoder_Write(u16 data)
{
	TIM2->CNT = data;
}

void TIM4_Encoder_Write(u16 data)
{
	TIM4->CNT = data;
}
