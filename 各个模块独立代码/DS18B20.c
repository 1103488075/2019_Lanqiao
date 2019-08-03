#include "STC15F2K60S2.h"
#include "intrins.h"
typedef unsigned int uint;
typedef unsigned char uchar;

uchar code SMG[] = {0xc0, 0xf9, 0xa4, 0xb0,
                    0x99, 0x92, 0x80, 0xf8,
                    0x80, 0x90, 0xbf, 0xff};
uchar yi=11, er=11,san=11,si=11,wu=11,liu=11,qi=11,ba=11;
sbit DQ = P1^4;//温测线
uchar num = 0;

void Delay3ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 33;
	j = 66;
	do
	{
		while (--j);
	} while (--i);
}

void Delay500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}
void Delay100us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 2;
	j = 15;
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
void display1(uchar yi, uchar er)
{
    P2 = 0xc0; P0 = 0x01;
    P2 = 0xff; P0 = SMG[yi];
    Delay3ms();
    P2 = 0xc0; P0 = 0x02;
    P2 = 0xff; P0 = SMG[er];
    Delay3ms(); 
}
void display2(uchar san, uchar si)
{
    P2 = 0xc0; P0 = 0x04;
    P2 = 0xff; P0 = SMG[san];
    Delay3ms();
    P2 = 0xc0; P0 = 0x08;
    P2 = 0xff; P0 = SMG[si];
    Delay3ms();
}

void ds_init()
{
    DQ = 0;
    Delay500us();
    DQ = 1;
    Delay500us();
}
void write(uchar dat)
{
    uchar i;
    for(i = 0;i < 8; i++)
    {
        DQ = 0;//拉低温控线，写进数值
        DQ = dat & 0x01;
        Delay100us();
        DQ = 1;//每接收完一个字节，都要拉高一次温控线
        dat >>= 1;       
    }
}
uchar read()
{
    uchar i; uchar dat;
    for(i = 0;i < 8;i++)
    {
        DQ = 0; //读温度前，拉低温控线
        _nop_();//延时一个机械周期
        dat >>= 1;
        DQ = 1;
        if (DQ == 1)
        {
            dat |= 0x80;
        }
        Delay100us();
    }
    return dat;//返回到temgit函数
}
uchar temgit()
{
    uchar temp; uchar low,high;
    ds_init();
    write(0xcc);//忽略rom指令
    write(0x44);//温度转换指令
    Delay500us();//写指令后延时1毫秒
    Delay500us();

    ds_init();
    write(0xcc);
    write(0xbe);//忽略rom指令之后发送一条读寄存器指令

    low = read();
    high = read();
    temp = high<<4;
    temp |=(low >>4);
    return temp;
}
void Init_time0()
{
    AUXR |= 0x80;//1T 
    TMOD &= 0xf0;//工作方式1
    TL0 = 0x00;//5毫秒
    TH0 = 0x28;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;//定时器零允许溢出位
    EA = 1;//总中断开关
}
void scanf_key()
{
    if(P30 == 0)
    {
        Delay3ms();
        if (P30 == 0)
        {
            num = temgit();
        }
        while(!P30);
    }
}
void main()
{
    Init_All();
    ds_init();
    //Init_time0();
    while(1)
    {
         scanf_key();
        yi = num / 100;
        er = num % 100/10;
        san = num %10;
        
        //num = temgit();
        display1(yi,er);
        display2(san,si);
    }
}
void time0()    interrupt  1
{
    TL0 = 0x00;
    TH0 = 0x28;


}