#include "Head.h"
#include "Display.h"
#include "key.h"
#include "iic.h"


void InitAll();
void Timer0Init(void);
void LED_blibli(uchar mode);

uchar temp;
uchar mode = 4;
uint Interval = 400;
bit flag = 0;
uchar luminance = 1;

uchar num = 0;
void main()
{
 //P2 = 0x80; P0 = 0xff;
	InitAll();
 	Timer0Init();
	ET0 = 1; EA = 1;
   		Delay2ms();
 	 mode = Read_EEPROM(0x00);
			Delay2ms();
	 Interval = Read_EEPROM(0x01)*10;
	  
	
	while(1)
	{
		luminance = Read_AD(0x03);
		if(S6 == 0)
		{
			yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = 11,ba = 11;
 		 }

 		else if(S6 == 1)
		{
			if(Interval >= 1000)
			{
				if(flag == 1)
				{yi = 10,er = mode,san = 10,si = 11,wu = Interval/1000, liu = Interval/100%10,qi = Interval/10%10,ba = Interval%10;}
				else if(flag == 0)
				{yi = 11,er = 11,san = 11,si = 11,wu = Interval/1000, liu = Interval/100%10,qi = Interval/10%10,ba = Interval%10;}
			}
			else if(Interval < 1000)
			{
				if(flag == 1)
				{yi = 10,er = mode,san = 10,si = 11,wu = 11, liu = Interval/100,qi = Interval/10%10,ba = Interval%10;}
				else if(flag == 0)
				{yi = 11,er = 11,san = 11,si = 11,wu = 11, liu = Interval/100,qi = Interval/10%10,ba = Interval%10;}
			}
		}
		else if(S6 == 2)
		{
			if(Interval >= 1000)
			{
				if(flag == 1)
				{yi = 10,er = mode,san = 10,si = 11,wu = Interval/1000,liu = Interval/100%10,qi = Interval/10%10,ba = Interval%10;}
				else if(flag == 0)
				{yi = 10,er = mode,san = 10,si = 11,wu = 11,liu = 11,qi = 11,ba = 11;}	
			}
			else if(Interval < 1000)
			{
				 if(flag == 1)
				{yi = 10,er = mode,san = 10,si = 11,wu = 11,liu = Interval/100,qi = Interval/10%10,ba = Interval%10;}
				else if(flag == 0)
				{yi = 10,er = mode,san = 10,si = 11,wu = 11,liu = 11,qi = 11,ba = 11;}	
			}
		}
		 
		Key();
	 Display1(yi,er); 
	 Display2(san,si);
	 Display3(wu,liu);
	 Display4(qi,ba);	
	}
}

void Time0() interrupt 1
{
	static uint i,j;
	static uint AD_tt;
	
	if(S7 == 1)
	{
		if(++i >= Interval/2)  //400 interval
		{
			i = 0;
		 	LED_blibli(mode);
		}
	}
	if(++j >= 400)
	{
		j = 0;
		 flag = ~flag;
	}
}

void LED_blibli(uchar mode)
{
	static uchar i = 0;
	static uchar temp;
	static uchar tem1,tem2;
	if(mode == 1)
	{
		temp = 0xfe;
		P2 = 0x80;
		P0 = _crol_(temp,i);
		if(++i >= 8)
		{i = 0;temp = 0xfe;}
	}
	else if(mode == 2)
	{
		temp = 0x7f;
		P2 = 0x80;
		P0 = _cror_(temp,i);
		if(++i >= 8)
		{i = 0;temp = 0x7f;}
	}
	else if(mode == 3)
	{	
		tem1 = 0x7f;
		tem2 = 0xfe;
		P2 = 0x80;
		P0 = _cror_(tem1,i)&_crol_(tem2,i);
		if(++i > 4)
		{i = 0;tem1 = 0x7f;tem2 = 0xfe;}
	}
	else if(mode == 4)
	{
		tem1 = 0xef;
		tem2 = 0xf7;
		P2 = 0x80;
		P0 = _crol_(tem1,i)&_cror_(tem2,i);
		if(++i > 4)
		{i = 0;tem1 = 0xef;tem2 = 0xf7;}
	}
}

void Timer0Init(void)		//2毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x9A;		//设置定时初值
	TH0 = 0xA9;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

void InitAll()
{
	P2 = 0xa0; P0 = 0x00;
	P2 = 0x80; P0 = 0xff;
	P2 = 0xc0; P0 = 0xff;
	P2 = 0xff; P0 = 0xff;
}