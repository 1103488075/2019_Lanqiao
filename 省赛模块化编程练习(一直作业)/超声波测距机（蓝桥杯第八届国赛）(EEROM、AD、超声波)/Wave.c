#include "Wave.h"

uint Distance = 123;
uint t = 0;
void SendWave()
{
    uchar i = 8; //send eight PWM
    do
    {
        TX = 1;
        somenop2;
        TX = 0;
        somenop2;
    } while(i--);
}