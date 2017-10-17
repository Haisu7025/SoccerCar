#ifndef __COM_H
#define __COM_H

#include "sys.h"

char penalty_kick_state(unsigned char *raw);

char game_state(unsigned char *raw);

char game_rounds(unsigned char *raw);

char self_x(unsigned char *raw);

char self_y(unsigned char *raw);

char oppo_x(unsigned char *raw);

char oppo_y(unsigned char *raw);

char ball_x(unsigned char *raw);

char ball_y(unsigned char *raw);

char self_forceStop(unsigned char *raw);

char oppo_forceStop(unsigned char *raw);

char self_evil(unsigned char *raw);

char oppo_evil(unsigned char *raw);

char self_score(unsigned char *raw);

char oppo_score(unsigned char *raw);

#endif