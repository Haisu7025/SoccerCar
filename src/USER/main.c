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
	TIM5_Int_Init(9999, 7199); //receive usart every 500ms
	TIM2_Encoder_Init(0xffff, 0);
	TIM4_Encoder_Init(0xffff, 0);
	
	delay_init();
}


int TIM2_Encoder_Read(void)
{
    TIM2_Encoder_Write(0);	//��������0
	  delay_ms(1700);	  //���ʱ�䣬�ɵ���
    return (int)((s16)(TIM2->CNT));	   //��������ת��
	                     //��¼���ر仯����������դ�񱻼�¼4�Σ�
}


int main(void)
{
	system_init();
	TIM3_PWM_Init(10000, 0);
  TIM2_Encoder_Init(0xffff, 0);
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	while(1)
    {
			printf("speed1:%d=====speed2:%d\n",speed1,speed2);
			delay_ms(1000);
    }		
}
