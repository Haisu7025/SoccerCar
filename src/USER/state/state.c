#include "state.h"
#include "pwm.h"

s16 *speed1;
s16 *speed2;
float distance;
s16 adj_pace;
s16 ZW;
s16 ZA;
s16 target_speed1, target_speed2;
s16 surface_speed1, surface_speed2;
unsigned char usart_msg[100];

void adj_spd(s16 *adj_pace, s16 *surface_speed, s16 speed, s16 target_speed, char lr)
{
    s16 pace;
    if (speed > target_speed)
    {
        pace = (speed - target_speed) * 67 / 100;
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
        pace = (target_speed - speed) * 67 / 100;
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