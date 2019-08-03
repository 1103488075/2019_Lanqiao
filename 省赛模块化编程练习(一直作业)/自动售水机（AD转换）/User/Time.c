#include "Time.h"

uint i = 0,value = 0,litre = 0;//interrupt value

void Init_Time0()
{
    AUXR |= 0x80;
    TMOD &= 0xf0;
    TL0 = 0x9a;
    TH0 = 0xa9;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;
    EA = 1;
}
void Time0()    interrupt 1
{
    if(S7 == 1)
    {
        i++;
        if(i >= 500)//one second
        {
            i = 0;
            WaterGross++;//water gross ++
            value++;
            if(value >= 10)//water litre
            {
                value = 0;
                litre++;
                TotalPrice += 5;//every litre add 5 unit
            }
        }
    }
}