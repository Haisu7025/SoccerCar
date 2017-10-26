#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "pwm.h"
#include "state.h"
#include "timer.h"

/************************************************
************************************************/

int system_init()
{
	speed1 = 0;
	speed2 = 0;
	TIM3_Int_Init(999, 7199);  //count speed every 100ms
	TIM5_Int_Init(4999, 7199); //receive usart every 500ms
	TIM2_Encoder_Init(0xffff, 0);
	TIM4_Encoder_Init(0xffff, 0);
}
int main(void)
{
	delay_init();
	TIM3_PWM_Init(10000, 0);
	while (1)
	{
		TIM_SetCompare1(TIM3, 10000);
		TIM_SetCompare2(TIM3, 0);
		delay_ms(20000);
		TIM_SetCompare1(TIM3, 0);
		TIM_SetCompare2(TIM3, 10000);
		delay_ms(20000);
		TIM_SetCompare1(TIM3, 0);
		TIM_SetCompare2(TIM3, 0);

		TIM_SetCompare3(TIM3, 10000);
		TIM_SetCompare4(TIM3, 0);
		delay_ms(20000);
		TIM_SetCompare3(TIM3, 0);
		TIM_SetCompare4(TIM3, 10000);
		delay_ms(20000);
		TIM_SetCompare3(TIM3, 10000);
		TIM_SetCompare4(TIM3, 10000);
	}
}
