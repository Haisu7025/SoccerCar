#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "pwm.h"

/************************************************
 ALIENTEK 战舰STM32F103开发板实验0
 工程模板
 注意，这是手册中的新建工程章节使用的main文件 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
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
