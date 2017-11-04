#include "state.h"
#include "pwm.h"

s16 *speed1;
s16 *speed2;
s16 adj_pace;
s16 target_speed1, target_speed2;
s16 surface_speed1, surface_speed2;
unsigned char usart_msg[100];

float K_p = 0.4, T_I = 1, T_D = 0, T = 1;
float A, B, C;
float error0 = 0, error1 = 0, error2 = 0;
char xb = 0, xc = 0, vbx = 0, vcx = 0;
u16 yb = 0, yc = 0, vby = 0, vcy = 0;

void adj_spd(s16 *adj_pace, s16 *surface_speed, s16 speed, s16 target_speed, char lr)
{
    s16 pace;
    //		if (target_speed==0){
    //				*surface_speed = 0;
    //        if (lr == 0)
    //        {
    //            printf("%c stop!surface_speed:%d,speed:%d,target_speed:%d\n",
    //                   lr + '1', surface_speed1, *speed1, target_speed1);
    //            set_speed_left(*surface_speed);
    //        }
    //        else
    //        {
    //            printf("%c stop!surface_speed:%d,speed:%d,target_speed:%d\n",
    //                   lr + '1', surface_speed2, *speed2, target_speed2);
    //            set_speed_right(*surface_speed);
    //        }
    //		}
    if (speed > target_speed)
    {
        if (speed - target_speed < 5)
        {
            return;
        }
        pace = (speed - target_speed) * 89 / 100;
        *surface_speed = *surface_speed - pace;
        if (lr == 0)
        {
            printf("%c too fast!surface_speed:%d,speed:%d,target_speed:%d\n",
                   lr + '1', surface_speed1, *speed1, target_speed1);
            set_speed_left(*surface_speed);
        }
        else
        {
            printf("%c too fast!surface_speed:%d,speed:%d,target_speed:%d\n",
                   lr + '1', surface_speed2, *speed2, target_speed2);
            set_speed_right(*surface_speed);
        }
    }
    else if (speed < target_speed)
    {
        if (target_speed - speed < 5)
        {
            return;
        }
        pace = (target_speed - speed) * 89 / 100;
        *surface_speed = *surface_speed + pace;
        if (lr == 0)
        {
            printf("%c too slow!surface_speed:%d,speed:%d,target_speed:%d\n",
                   lr + '1', surface_speed1, *speed1, target_speed1);
            set_speed_left(*surface_speed);
        }
        else
        {
            printf("%c too slow!surface_speed:%d,speed:%d,target_speed:%d\n",
                   lr + '1', surface_speed2, *speed2, target_speed2);
            set_speed_right(*surface_speed);
        }
    }
}