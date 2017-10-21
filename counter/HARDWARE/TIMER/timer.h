#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

extern u16 count_flag;
extern u32 cur_count;

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM5_Cap_Init(u16 arr,u16 psc);
#endif
