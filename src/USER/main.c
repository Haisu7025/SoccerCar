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
s16 speed_1, speed_2;
void init_paras()
{
	speed_1 = 0;
	speed_2 = 0;
	distance = 0;
	target_speed1 = target_speed2 = 0;
	surface_speed1 = surface_speed2 = 0;
	ZW = 0;
	adj_pace = 500;
}
int system_init()
{
	init_paras();
	delay_init();

	speed1 = &speed_1;
	speed2 = &speed_2;
	TIM6_Int_Init(999, 7199);  //count speed every 100ms
	TIM5_Int_Init(9999, 7199); //receive usart every 500ms
	TIM2_Encoder_Init(0xffff, 0);
	TIM4_Encoder_Init(0xffff, 0);
	I2C_MPU6050_Init();
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
