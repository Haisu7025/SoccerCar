#ifndef __STATE_H
#define __STATE_H

#include "sys.h"

extern s16 *speed1;
extern s16 *speed2;
extern s16 adj_pace;
extern s16 target_speed1, target_speed2;
extern s16 surface_speed1, surface_speed2;
extern unsigned char usart_msg[100];

void adj_spd(s16 *adj_pace, s16 *surface_speed, s16 speed, s16 target_speed, char lr);
#endif