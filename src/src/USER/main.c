#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "pwm.h"
#include "state.h"
#include "timer.h"
#include "kicker.h"

/************************************************
************************************************/
u16 speed_1, speed_2;
void init_paras()
{
	speed_1 = 0;
	speed_2 = 0;
	target_speed1 = target_speed2 = 0;
	surface_speed1 = surface_speed2 = 0;

	adj_pace = 500;
}
int system_init()
{
	init_paras();
	speed1 = &speed_1;
	speed2 = &speed_2;
	TIM6_Int_Init(999, 7199);  //count speed every 100ms
	TIM5_Int_Init(9999, 7199); //receive usart every 500ms
	TIM2_Encoder_Init(0xffff, 0);
	TIM4_Encoder_Init(0xffff, 0);

	delay_init();
}

int TIM2_Encoder_Read(void)
{
	TIM2_Encoder_Write(0);			//计数器清0
	delay_ms(1700);					//检测时间，可调节
	return (int)((s16)(TIM2->CNT)); //数据类型转换
									//记录边沿变化次数（几个栅格被记录4次）
}

int main(void)
{
	system_init();
	TIM3_PWM_Init(10000, 0);
	uart_init(115200); //串口初始化为115200
	surface_speed1 = surface_speed2 = 2000;
	target_speed1 = target_speed2 = 600;
	KICK_Init();
	while (1)
	{
		printf("speed1:%d=====speed2:%d\n", *speed1, *speed2);
		delay_ms(888);
		KICK();
	}
}
