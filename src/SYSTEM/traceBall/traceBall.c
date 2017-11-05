#include "traceBall.h"
#include "state.h"
#include <math.h>
#include "pwm.h"
#include "com.h"
#include "usart.h"

#define PI (3.1415926535)
void traceBall()
{
    char xbc = xb - xc;
    u16 ybc = yb - yc;
	float thetac, deltaSpeed;
    thetac = atan2(vcy, vcx);
	if (vbx*vbx + vby*vby > 200)
	{
		float alpha = acos((vbx*xbc+vby*ybc) / (sqrt(vbx*vbx+vby*vby)*sqrt(xbc*xbc+ybc*ybc)));
		float theta = asin(sqrt(vbx*vbx+vby*vby)*sin(alpha)/sqrt(vcx*vcx+vcy*vcy));
		error2 = (1-theta/alpha)*atan2(ybc, xbc) + theta/alpha*atan2(vby, vbx) - thetac;
	}
	else
	{
		error2 = atan2(ybc, xbc) - thetac;
	}
    deltaSpeed = 100 * (A*error2 + B*error1 + C*error0);
    target_speed1 -= deltaSpeed; target_speed2 += deltaSpeed;
    set_speed_left(target_speed1); set_speed_right(target_speed2);
    error0 = error1; error1 = error2;
}

void traceBall_turn()
{
	char xbc = xb - xc; 
    u16 ybc = yb - yc;
	float alpha = (atan2(ybc, xbc) - theta0) * 180 / PI - yaw;
	printf("atan2(ybc, xbc):%f,theta0:%f,yaw:%f,alpha:%f\r\n",atan2(ybc, xbc),theta0,yaw,alpha);
	alpha = (alpha > 180) ? alpha - 360 : ( (alpha < -180) ? alpha + 360 : alpha );
		if (game_state(usart_msg) != 1) return;

	if (alpha > 10 || alpha < -10)
	{
		target_speed1 = 300; target_speed2 = 300 + alpha * 3;
		set_speed_left(target_speed1); set_speed_right(target_speed2);
	}
	else
	{
		if (xbc*xbc + ybc*ybc > 100)
		{
			target_speed1 = 400; target_speed2 = 400;
			set_speed_left(target_speed1); set_speed_right(target_speed2);
		}
		else
		{
			target_speed1 = 0; target_speed2 = 0;
			set_speed_left(target_speed1); set_speed_right(target_speed2);
		}
	}
}
