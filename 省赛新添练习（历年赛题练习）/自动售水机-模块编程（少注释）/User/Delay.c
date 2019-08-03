#include "Delay.h"

void Delay2ms()
{
    uchar i,j;
   _nop_(); _nop_();
    i = 22; j = 128;
    do
    {
        while(--j);
    }while(--i);
}
  