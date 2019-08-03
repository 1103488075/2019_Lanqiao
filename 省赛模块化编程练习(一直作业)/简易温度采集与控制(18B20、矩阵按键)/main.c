#include "Hread.h"
#include "Display.h"
#include "Key.h"
#include "onewire.h"

uchar wendu = 0;
uchar Max = 30,Min = 20;
uchar qujian;
uint tt;
bit flag = 0;

void InitAll();
void InitTimer0();
 
void main()
{
    InitAll();
    InitTimer0();
    yi = 10,er = 1,san = 10,si = 11,wu = 11;
    liu = 11,qi = wendu/10,ba = wendu %10; 
    while(1)
    {
        if(shezhi == 0)//is not seting interface
        {
            wendu = Get_18B20();
            if(wendu < Min)
            {qujian = 0; P2 = 0xa0; P0 = 0x00;}
            else if(wendu >= Min && wendu <= Max)
            {qujian = 1; P2 = 0xa0; P0 = 0x00;}
            else if(wendu > Max)
            {qujian = 2; P2 = 0xa0; P0 = 0x10;}

            yi = 10,er = qujian,san = 10,si = 11,wu = 11;
            liu = 11, qi = wendu/10,ba  =wendu%10;
        }
        else if(shezhi == 1)//is there parameter seting interface
        {
            P2 = 0x80; P0 = 0xff; P2 = 0xa0; P0 = 0x00;
            
        }
        ScanKey16();
        Display1(yi,er);
        Display2(san,si);
        Display3(wu,liu);
        Display4(qi,ba);
    }
}
void Timer0() interrupt 1
{
    tt++;
   
    if((qujian == 0)&&(tt >= 160))
    { 
        tt = 0;
        if(flag == 0){flag = 1;P2 = 0x80; P0 = 0xfe;}
        else if(flag == 1){flag = 0; P2 = 0x80; P0 = 0xff;}     
    }
    else if((qujian == 1)&&(tt >= 80))
    {      
        tt = 0;
        if(flag == 0){flag = 1;P2 = 0x80; P0 = 0xfe;}
        else if(flag == 1){flag = 0; P2 = 0x80; P0 = 0xff;}
    }
    else if((qujian == 2)&&(tt >= 40))
    {
        tt = 0;
        if(flag == 0){flag = 1; P2 = 0x80; P0 = 0xfe;}
        else if(flag == 1){flag = 0; P2 = 0x80; P0 = 0xff;}
    }
}
void InitAll()
{
    P2 = 0xa0; P0 = 0x00;
    P2 = 0x80; P0 = 0xff;
    P2 = 0xc0; P0 = 0xff;
    P2 = 0xff; P0 = 0xff;
}
void InitTimer0()
{
    AUXR |= 0x80;
    TMOD &= 0xf0;
    TL0 = 0x00;
    TH0 = 0x28;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;
    EA = 1;
}

 