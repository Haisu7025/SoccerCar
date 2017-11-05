#include "kicker.h"
#include "delay.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void KICK_Init()
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //LED0-->PB.12 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.12
 GPIO_ResetBits(GPIOB,GPIO_Pin_12);						 //PB.12 �����
	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 //LED0-->PB.10 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.10
 GPIO_ResetBits(GPIOB,GPIO_Pin_10);						 //PB.10 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 //LED0-->PB.11 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.11

}
 

void KICK()
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);	
  delay_ms(200);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);	
}

s16 DISTANCE_mm()
{
	u16 i=0;
	GPIO_SetBits(GPIOB,GPIO_Pin_10);
	delay_us(10);
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0);
	while ((i<10000)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11))) 
	{
		i++;
	}
	return (i);
}
