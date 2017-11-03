#include "LCD5110.h"
#include "ultrasonic.h"
#include"delay.h"

int main()
{
	float temp;
	char DisNum[16];
	SystemInit();
	delay_init(72);
	LCD5110_GPIOInit();
	Ultran_Init();
	
	
	while(1)
	{
			Ultra_Ranging(&temp);
			LCD5110Clear();
			sprintf(DisNum,"%1.4f",temp);
			LCD5110WriteEnStr(0,0,(u8 *)DisNum);			
// 			delay_ms(500);			
	}

}




