#include "Key.h"
#include "Display.h"
uchar S7 = 0,S6 = 0,S5 = 0,S4 = 0;
uchar Timec = 1;
uchar Cai_Start = 0;
void ScanKey()
{
    if(P30 == 0)
    {
        Delay2ms();
        if(P30 == 0)
        {
            if(Cai_Start == 3)//only there Cai_Start3 use 
            Cai_Start = 0;//anew circulation
        }
		while(!P30);
    }
    else if(P31 == 0)
    {
        Delay2ms();
        if(P31 == 0)
        {
          if(Cai_Start == 2)//only there cai_Start2 use
          {
            LED_shan = 0;
            P2 = 0x80; P0 = 0xff;
          }
        }
		while(!P31);
    }
    else if(P32 == 0)
    {
        Delay2ms();
        if(P32 == 0)
        { 
            if(Cai_Start == 0)
            {
                Cai_Start = 1;
                tt = 0;
            }
        }
		while(!P32);
    }
    if(P33 == 0)
    {
        Delay2ms();
        if(P33 == 0)
        {
            if(Cai_Start == 0)
            {
            if(Timec == 1){Timec = 5;}
            else if(Timec == 5){Timec = 30;}
            else if(Timec == 30){Timec = 60;}
            else if(Timec == 60){Timec = 1;}
            }
        }
		while(!P33);
    }
}