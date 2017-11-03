#ifndef __STATE_H
#define __STATE_H

#include "sys.h"

extern u16 *speed1;
extern u16 *speed2;
extern u16 adj_pace;
extern u16 target_speed1, target_speed2;
extern u16 surface_speed1, surface_speed2;
extern unsigned char usart_msg[100];

void adj_spd(u16 *adj_pace, u16 *surface_speed, u16 speed, u16 target_speed, char lr);
#endif