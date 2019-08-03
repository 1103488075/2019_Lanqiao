//=======================自动售水机
#include "STC15F2K60S2.h"
#include "intrins.h"
typedef unsigned int uint;
typedef unsigned char uchar;

uchar yi, er, san, si, wu, liu, qi, ba,jiu,shi;
void Init_All();
void Delay2ms();
void Display1(uchar yi ,uchar er);
void Display2(uchar san ,uchar si);
void Display3(uchar wu ,uchar liu);
void Display4(uchar qi ,uchar ba);
void ScanKey();
void Display5(uchar jiu,uchar shi);
void Init_Time0();

uchar S7,S6;
uchar code duanxuan[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xbf, 0xff, 0x7f};//0x7f is decimal point
uint Cost = 0.5*10;//费率、*10 split display
uint WaterGross = 1*10;//出水总量
uint TotalPrice = 0.5*10;//总价、*10 split diplay
uint i,value,litre;//interrupt value
void main()
{

    yi = 11,er = 11, san = 11, si = 11, wu = 11, liu = 11, qi = 11, ba = 11, jiu = 11, shi = 11;
    Init_All();
    Init_Time0();
    while(1)
    {
	    ScanKey();
        Init_Time0();//time0 interrup tow ms once
        if(S7 == 1)//key control、nixietube display
        {
            
			yi = 11; er = Cost/10%10; san = Cost%10; si = 0;// display cost
			wu = WaterGross/100%10; liu = WaterGross/10%10; qi = WaterGross%10; ba = 0;   //display water gross //and total price s
			jiu = 12; shi = 12;		//decimal point display
            
            P2 = 0xa0; P0 = 0x10; //open relay
            P2 = 0x80; P0 = 0x7f;   //open led
        }
        if(S6 == 1)//diplay cost and total price s
        {
            S7 = 0;
            S6 = 0;
            P2 = 0xa0; P0 = 0x00;//close
            P2 = 0x80; P0 = 0xff;//close
            wu = TotalPrice/100%10; liu = TotalPrice/10%10; qi = TotalPrice%10; ba = 0; //display total price s
            shi = 12;   //  decimal poinit
        }
        if(WaterGross >= 999)//water gross greater than value
        {
            P2 = 0xa0; P0 = 0x00;//relay close
        }
        Display1(yi, er);
        Display2(san, si);
        Display3(wu, liu);
        Display4(qi, ba);
		Display5(jiu,shi);	//jiu,shi is decimal point 
    }
}
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
void Init_All()//all init
{
    P2 = 0x80; P0 = 0xff;//led
    P2 = 0xa0; P0 = 0x00;//buzz
    P2 = 0xc0; P0 = 0xff;//weixuan
    P2 = 0xff; P0 = 0xff;
}
void Display1(uchar yi, uchar er) //is nixietube
{
    P2 = 0xc0; P0 = 0x01;
    P2 = 0xff; P0 = duanxuan[yi];
    Delay2ms();
    P2 = 0xc0; P0 = 0x02;
    P2 = 0xff; P0 = duanxuan[er];
    Delay2ms();
}
void Display2(uchar san, uchar si)
{
    P2 = 0xc0; P0 = 0x04;
    P2 = 0xff; P0 = duanxuan[san];
    Delay2ms();
    P2 = 0xc0; P0 = 0x08;
    P2 = 0xff; P0 = duanxuan[si];
    Delay2ms();
}
void Display3(uchar wu, uchar liu)
{
    P2 = 0xc0; P0 = 0x10;
    P2 = 0xff; P0 = duanxuan[wu];
    Delay2ms();
    P2 = 0xc0; P0 = 0x20;
    P2 = 0xff; P0 = duanxuan[liu];
    Delay2ms();
}
void Display4(uchar qi, uchar ba)
{
    P2 = 0xc0; P0 = 0x40;
    P2 = 0xff; P0 = duanxuan[qi];
    Delay2ms();
    P2 = 0xc0; P0 = 0x80;
    P2 = 0xff; P0 = duanxuan[ba];
    Delay2ms();
}
void Display5(uchar jiu,uchar shi)
{
    P2 = 0xc0; P0 = 0x02;
    P2 = 0xff; P0 = duanxuan[jiu];
    Delay2ms();
    P2 = 0xc0 ; P0 = 0x20;
    P2 = 0xff; P0 = duanxuan[shi];
    Delay2ms();
}
