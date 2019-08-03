
#include "ScanKey.h"
#include "Delay.h"


uchar S7 = 0;
uchar S6 = 0;
void ScanKey()
{
    if(P30 == 0)//S7 is key
    {
        Delay2ms();
        if(P30 == 0)
        {
            S7 = 1;
        }
        while(!P30);
    }
    if(P31 == 0)
    {
        Delay2ms();
        if(P31 == 0)
        {
            S6 = 1;
        }
        while(!P31);
    }
}