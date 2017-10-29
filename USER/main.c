#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "pwm.h"
#include "state.h"
#include "timer.h"

/************************************************
************************************************/
u16 speed_1,speed_2;
int system_init()
{
	speed_1=10;
	speed_2=10;
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
    TIM2_Encoder_Write(0);	//计数器清0
	  delay_ms(1700);	  //检测时间，可调节
    return (int)((s16)(TIM2->CNT));	   //数据类型转换
	                     //记录边沿变化次数（几个栅格被记录4次）
}


int main(void)
{
	system_init();
	TIM3_PWM_Init(10000, 0);
	uart_init(115200);	 //串口初始化为115200
	
	set_speed_left(4000);
	set_speed_right(4000);
	while(1)
    {
			printf("speed1:%d=====speed2:%d\n",*speed1,*speed2);
			delay_ms(888);
    }		
}
