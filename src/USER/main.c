#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "pwm.h"

/************************************************
 ALIENTEK ս��STM32F103������ʵ��0
 ����ģ��
 ע�⣬�����ֲ��е��½������½�ʹ�õ�main�ļ� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

 int main(void)
 {	
	 delay_init();	 
	 TIM3_PWM_Init(10000,0);
	 while (1)
	 {
		 TIM_SetCompare1(TIM3,10000);
		 TIM_SetCompare2(TIM3,0);
		 delay_ms(20000);
	   TIM_SetCompare1(TIM3,0);
		 TIM_SetCompare2(TIM3,10000);
		 delay_ms(20000);
	   TIM_SetCompare1(TIM3,0);
		 TIM_SetCompare2(TIM3,0);
		 
		 TIM_SetCompare3(TIM3,10000);
		 TIM_SetCompare4(TIM3,0);
		 delay_ms(20000);
	   TIM_SetCompare3(TIM3,0);
		 TIM_SetCompare4(TIM3,10000);
		 delay_ms(20000);
	   TIM_SetCompare3(TIM3,10000);
		 TIM_SetCompare4(TIM3,10000);
	 }
 }
