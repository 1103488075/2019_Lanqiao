#include "STC15F2K60S2.H"
#include "intrins.H"
typedef unsigned int uint;
typedef unsigned char uchar;
uchar code SMG[] = {0xc0, 0xf9, 0xa4, 0xb0, 
                    0x99, 0x92, 0x82, 0xf8,
                    0x80, 0x90, 0xbf, 0xff};
uchar yi= 11,er=11,san=11,si=11;
uchar i;
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
void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void Init_All()
{
    P2 = 0xa0; P0 = 0x00;//buzz
    P2 = 0x80; P0 = 0xff;//LED
    P2 = 0xc0; P0 = 0xff;//位选
    P2 = 0xff; P0 = 0xff;//段选
}
void LED(uchar j)
{
    uchar i;
    P2 = 0x80;
    P0 = 0xfe;
    if(j == 1)
    {
        for(i = 0; i<8; i++)
        {
        P0 = _cror_(P0, 1);
        Delay500ms();
        }
    }
    else if(j == 2)
    {
        for(i = 0; i<8; i++)
        {
            P0 = _crol_(P0, 1);
            Delay500ms();
        }
    }
    else if(j == 3)
    {
        for(i = 0; i<8; i++)
        {
            P0 = _cror_(P0, 1);
            Delay500ms();
        }
        for(i = 0; i<8; i++)
        {
            P0 = _crol_(P0, 1);
            Delay500ms();
        }
    }
    else if(j == 4)
    {
        P0 = 0x00;
    }
}
void scanf_key()
{
    if(P30 == 0)
    {
        Delay5ms();
        if(P30 == 0)
        {
            yi = 1;
            LED(1);
        }        
    }
    if(P31 == 0)
    {
        Delay5ms();
        if(P31 == 0)
        {
            LED(2);
            er = 2;
        }
    }
    if(P32 == 0)
    {
        Delay5ms();
        if(P32 == 0)
        {
            LED(3);
            san = 3;
        }
    }
    if(P33 == 0)
    {
        Delay5ms();
        if(P33 == 0)
        {
            LED(4);
            si = 4;
        }
    }
}
void dispaly1(uchar yi, uchar er)
{
    P2 = 0xc0; P0 = 0x01;
    P2 = 0xff; P0 =SMG[yi];
    Delay5ms();
    P2 = 0xc0; P0 = 0x02;
    P2 = 0xff; P0 = SMG[er];
    Delay5ms();
}

void dispaly2(uchar san, uchar si)
{
    P2 = 0xc0; P0 = 0x04;
    P2 = 0xff; P0 = SMG[san];
    Delay5ms();
    P2 = 0xc0; P0 = 0x80;
    P2 = 0xff; P0 = SMG[si];
    Delay5ms();
}
void Time0_Init()//5毫秒
{
    AUXR |= 0x80;//1T模式
    TMOD &= 0xf0;//模式1
    TL0 = 0x00;
    TH0 = 0x28;
    TF0 = 0;//清除TF0标志
    TR0 = 1;//定时器0开始计时
    ET0 = 1;//中断允许溢出位
    EA = 1;//总中断
}
void main()
{
    Init_All();
    Time0_Init();
    while(1)
    {
      scanf_key();
      dispaly1(yi,er);
      dispaly2(san,si);
    }
}
void Time0_interrupt() interrupt 1
{
    TL0 = 0x00;
    TH0 = 0x28;
  
}