#include "STC15F2K60S2.H"
#include "intrins.h"
typedef unsigned int uint;
typedef unsigned char uchar;
uchar code SMG[]={0xc0, 0xf9, 0xa4, 0xb0,
                  0x99, 0x92, 0x82, 0xf8,
                  0x80, 0x90, 0xbf, 0xff};
uchar yi=9,er=8,san=7,si=11,wu=11,liu=11,qi=11,ba=11;
uchar i = 0;
void Delay5ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 54;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Init_All()
{
    P2 = 0xa0; P0 = 0x00;//buzz
    P2 = 0x80; P0 = 0xff;//LED
    P2 = 0xc0; P0 = 0xff;//位选
    P2 = 0xff; P0 = 0xff;//段选
}
void display1(uchar yi,uchar er)
{
    P2 = 0xc0; P0 = 0x01;
    P2 = 0xff; P0 =SMG[yi];
    Delay5ms();
    P2 = 0xc0; P0 = 0x02;
    P2 = 0xff; P0 = SMG[er];
    Delay5ms();
}
void display2(uchar san, uchar si)
{
    P2 = 0xc0; P0 = 0x04;
    P2 = 0xff; P0 = SMG[san];
    Delay5ms();
    P2 = 0xc0; P0 = 0x08;
    P2 = 0xff; P0 = SMG[si];
    Delay5ms();
}
void scanf_key()
{
    if(P30 == 0)
    {
        Delay5ms();
        if(P30 == 0)
        {
            yi = 1;
        }
        while(!P30);//状态改变才跳出
    }
    if(P31 == 0)
    {
        Delay5ms();
        if(P31 == 0)
        {
            er = 2;
        }
        while(!P31);
    }
    if(P32 == 0)
    {
        Delay5ms();
        if(P32 == 0)
        {
            san = 3;
        }
        while(!P32);
    }
    if(P33 == 0)
    {
        Delay5ms();
        if(P33 == 0)
        {
            si = 4;
        }
        while(!P33);
    }
}
void Timer0Init(void)		//500微秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xEA;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
    ET0 = 1;       //定时器0溢出中断允许位
    EA = 1;     //中断允许位
}

void main()
{
    Init_All();
	Timer0Init();
    while(1)
    {
        
        display1(yi,er);
        display2(san,si);
    }
}
void Intertup_time0() interrupt 1
{
    TL0 = 0x66;
    TH0 = 0xEA;
    scanf_key();
}