#include "ScanKey.h"
#include "Display.h"
uchar S7 = 0,S6 = 0,S5 = 0,S4 = 0;
void Key()
{
    if(P30 == 0)
    {
        Delay2ms();
        if(P30 == 0)
        {
            S7 = 1;
        }
        while(!P30);
    }
    else if(P31 == 0)
    {
        Delay2ms();
        if(P31 == 0)
        {
            S6 = 1;
        }
        while(!P31);
    }
    else if(P32 == 0)
    {
        Delay2ms();
        if(P32 == 0)
        {
            S5 = 1;
        }
        while(!P32);
    }
    else if(P33 == 0)
    {
        Delay2ms();
        if(P33 == 0)
        {
            S4 = 1;
        }
        while(!P33);
    }
}