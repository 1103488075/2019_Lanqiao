#include "Key.h"
#include "Display.h"
#include "ds1302.h"

uchar S7 = 0, S6 = 0, S5 = 0, S4 = 0;
uchar wendu = 0;
void Scan_Key()
{
    if(P30 == 0)
    {
        Delay2ms();
        if(P30 == 0)//seting key
        {
            if(S7 == 0) S7 = 1; //seting huor
            else if(S7 == 1)  S7 = 2;   //seting minute
            else if(S7 == 2)    S7 = 3; //seting second
            else if(S7 == 3)    S7 = 0;    //return
        }
		while(!P30);
    }
    else if(P31 == 0)
    {
        Delay2ms();
        if(P31 == 0)
        {
            if(S6 == 0) S7 = 1;
            else if(S6 == 1) S6 = 2;
            else if(S6 == 2) S6 = 3;
            else if(S6 == 3) S6 = 0;
        }
		while(!P31);
    }
    else if(P32 == 0)//seting time
    {
        Delay2ms();
        if(P32 == 0)
        {
            if(S7 == 1)//seting 
            {Time[2]++; Init_Time();}
            else if(S7 == 2)
            { Time[1]++; Init_Time();}
            else if(S7 == 3)
            {Time[0]++; Init_Time();}
        }
		while(!P32);
    }
    else if(P33 == 0)
    {
        Delay2ms();
        if(P33 == 0)
        {
            S4 = 1;
            if(S7 == 0) wendu = 1;
        }
    }
    if((S4 == 1) && (P33 == 1))
    {
        S4 = 0; wendu = 0;
            if(S7 == 1)
            {Time[2]--; Init_Time();}
            else if(S7 == 2)
            {Time[1]--; Init_Time();}
            else if(S7 == 3)
            {Time[0]--; Init_Time();}
    }
}