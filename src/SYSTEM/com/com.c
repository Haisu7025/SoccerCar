#include "com.h"
#include "sys.h"
char penalty_kick_state(unsigned char *raw)
{
    switch (raw[0])
    {
    case 0xff:
        //self
        return 1;
    case 0xfe:
        //oppo
        return 0;
    default:
        return -1;
    }
    return -1;
}

char game_state(unsigned char *raw)
{
    char state = raw[1] >> 6;
    return state;
}

char game_rounds(unsigned char *raw)
{
    u16 rounds = raw[1] * 256 + raw[2];
    return rounds;
}

char self_x(unsigned char *raw)
{
    return raw[3];
}

char self_y(unsigned char *raw)
{
    u16 self_y = raw[4] * 256 + raw[5];
    return self_y;
}

char oppo_x(unsigned char *raw)
{
    return raw[5];
}

char oppo_y(unsigned char *raw)
{
    u16 self_y = raw[6] * 256 + raw[7];
    return self_y;
}

char ball_x(unsigned char *raw)
{
    return raw[8];
}

char ball_y(unsigned char *raw)
{
    u16 self_y = raw[9] * 256 + raw[10];
    return self_y;
}

char self_forceStop(unsigned char *raw)
{
    u16 self_forceStop = raw[12] * 256 + raw[13];
    return self_forceStop;
}

char oppo_forceStop(unsigned char *raw)
{
    u16 oppo_forceStop = raw[14] * 256 + raw[15];
}

char self_evil(unsigned char *raw)
{
    return raw[16];
}

char oppo_evil(unsigned char *raw)
{
    return raw[17];
}

char self_score(unsigned char *raw)
{
    return raw[18];
}

char oppo_score(unsigned char *raw)
{
    return raw[19];
}