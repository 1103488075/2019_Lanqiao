#include "Scan_Key.h"
uchar S7 = 0,S6 = 0,S5 = 0,S4 = 0;

void Scan_Key()
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
    if(P31 == 0)
    {
        Delay2ms();
        if(P31 == 0)
        {
            S6 = 1;
        }
        while(!P31);
    }
    if(P32 == 0)
    {
        Delay2ms();
        if(P32 == 0)
        {
            S5 = 1;
        }
        while(!P32);
    }
    if(P33 == 0)
    {
        Delay2ms();
        if(P33 == 0)
        {
            S4 = 1;  //start key
        }
        while(!P33);
    }

}