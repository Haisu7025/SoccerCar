#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "pwm.h"
#include "state.h"
#include "timer.h"
#include "kicker.h"
#include "traceBall.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "state.h"
#include <math.h>

/************************************************
************************************************/
s16 speed_1, speed_2;
void init_paras()
{
	speed_1 = 0;
	speed_2 = 0;
	target_speed1 = target_speed2 = 0;
	surface_speed1 = surface_speed2 = 0;	
	
	A = K_p*(1+T/T_I+T_D/T); B = -K_p*(1+2*T_D/T); C = K_p*T_D/T;

	adj_pace = 500;
}
int system_init()
{
	init_paras();
	speed1 = &speed_1;
	speed2 = &speed_2;
	delay_init();

	TIM2_Encoder_Init(0xffff, 0);
	TIM4_Encoder_Init(0xffff, 0);
	TIM6_Int_Init(999, 7199);  //count speed every 100ms
	TIM5_Int_Init(4999, 7199); //receive usart every 500ms
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
	float pitch,roll; 		//欧拉角
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	short temp;					//温度	    
	
	system_init();
	TIM3_PWM_Init(10000, 0);
	KICK_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为9600
	MPU_Init();					//初始化MPU6050
	 
	surface_speed1 = surface_speed2 = 2000;
	target_speed1 = target_speed2 = 400;
	
	set_speed_left(target_speed1); set_speed_right(target_speed2);
	delay_ms(1000);
	//theta0 = atan2(vcy, vcx);
	theta0 = 0;   
	
	while(mpu_dmp_init())
 	{
		printf("MPU6050 Error \r\n");
		delay_ms(1000);
	}  
 
 	while(1)
	{
		
		
				traceBall_turn();
		printf("speed1:%d=====speed2:%d\n", *speed1, *speed2);

		KICK();
		
		
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{ 
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
//		printf("\r\n---------加速度X轴原始数据---------   %d \r\n",aacx);
//		printf("\r\n---------加速度Y轴原始数据---------   %d \r\n",aacy);	
//		printf("\r\n---------加速度Z轴原始数据---------   %d \r\n",aacz);	
//		printf("\r\n---------陀螺仪X轴原始数据---------   %d \r\n",gyrox);	
//		printf("\r\n---------陀螺仪Y轴原始数据---------   %d \r\n",gyroy);	
//		printf("\r\n---------陀螺仪Z轴原始数据---------   %d \r\n",gyroz);
//		printf("\r\n---------姿态角X数据---------   %1.4f \r\n",pitch);	
//		printf("\r\n---------姿态角Y数据---------   %1.4f \r\n",roll);	
		printf("\r\n---------姿态角Z数据---------   %1.4f \r\n",yaw);
		delay_ms(200);
		}
	}
} 	
 



