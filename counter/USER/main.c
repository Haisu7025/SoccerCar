#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
 
/************************************************
 ALIENTEK战舰STM32开发板实验10
 输入捕获实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

extern u8  TIM5CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值	

u16 count_flag;
u32 cur_count;

 int main(void)
 {		
 	u32 temp=0; 
	
	count_flag=0;
	cur_count=0;
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
 
 	TIM3_Int_Init(10000,7199); 		//不分频。PWM频率=72000/(899+1)=80Khz
 	TIM5_Cap_Init(0XFFFF,72-1);	//以1Mhz的频率计数 
   	while(1)
	{
 		delay_ms(10);	
		 		 
 		
	}
 }

void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		printf("本阶段技计数：%d\n",cur_count);
//		if(TIM5CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
//		{
//			printf("hello\n");
//			TIM5CH1_CAPTURE_STA=0;//开启下一次捕获
//		}
		}
}