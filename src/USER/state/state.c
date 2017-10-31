#include "state.h"
#include "pwm.h"

u16 *speed1;
u16 *speed2;
u16 adj_pace;
u16 target_speed1, target_speed2;
u16 surface_speed1, surface_speed2;
unsigned char usart_msg[100];

void adj_spd(u16 *adj_pace, u16 *surface_speed, u16 speed, u16 target_speed, char lr)
{
    u16 pace;
    if (speed > target_speed)
    {
        pace = (speed - target_speed) * 67 / 100;
        *surface_speed = *surface_speed - pace;
        if (lr == 0)
        {
            set_speed_left(*surface_speed);
        }
        else
        {
            set_speed_right(*surface_speed);
        }
    }
    else if (speed < target_speed)
    {
        pace = (target_speed - speed) * 67 / 100;
        *surface_speed = *surface_speed + pace;
        if (lr == 0)
        {
            set_speed_left(*surface_speed);
        }
        else
        {
            set_speed_right(*surface_speed);
        }
    }
}