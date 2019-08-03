#include "Scan_Key.h"
#include "Hread.h"
uchar S7 = 0,S6 = 0,S5 = 0,S4 = 0;

void Scan_Key()
{
    if(P30 == 0)
    {
        Delay2ms();
        if(P30 == 0)
        {
            if(S7 == 0)
            {
                S7 = 1;Min = Min+1;
              
            }
            else if(S7 == 1)
            {
                S7 = 0;Min = Min+1;  
            }
        }
        while(!P30);
    }
    else if(P31 == 0)
    {
        Delay2ms();
        if(P31 == 0)
        {
             if(S6 == 0){S6 = 1;Min = Min-1;}
            else if(S6 == 1){S6 = 0;Min = Min-1;}
        }
        while(!P31);
    }
    else if(P32 == 0)
    {
        Delay2ms();
        if(P32 == 0)
        {
            if(S5 == 0)
            {
               S5 = 1;Max = Max-1;
              
            }
            else if(S5 == 1)
            {
                S5 = 0;Max = Max-1;
             
            }
        }
        while(!P32);
    }
    else if(P33 == 0)
    {
        Delay2ms();
        if(P33 == 0)
        {
            if(S4 == 0){S4 = 1;Max = Max+1;}
            else if(S4 == 1){S4 = 0;Max = Max+1; }
        }
        while(!P33);
    }
  
}