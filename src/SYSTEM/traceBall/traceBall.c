#include "traceBall.h"
#include "state.h"
#include <math.h>
#include "pwm.h"


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

