#include "Head.h"
#include "Display.h"
#include "ScanKey.h"
#include "iic.h"
#include "ds1302.h"
#include "onewire.h"
#include "Sonic.h"

void IniAll();
void Timer0Init(void);
 void Timer1Init(void);//sonic funtion user
uchar Voltage = 0;
uint i,k,l,n,intr;
bit j = 0,m = 0,s_flag;	//s_flag is sonic funtion user
uint Sonic = 30;
char Transfer1 = 2,Transfer2 = 4;
 
void main()
{
   	 IniAll();
	 Timer0Init();
	 Timer1Init();
	 Transfer1 = EEPROMRead(0x00);
	 Delay2ms();
	 Transfer2 = EEPROMRead(0x01);
	// yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = 11,ba = 11;
	 while(1)
	 {
		 Voltage = ReadAD(0x03);
	 
		if(Voltage < 1 )		//no-load
		{
			P2 = 0xa0; P0 = 0x00;
			P2 = 0x80; P0 = 0xfe;
	 
		}
		else if(Voltage < 4 && Voltage >= 1)//normal
		{
			P2 = 0x80; P0 = 0xfd;
			P2 = 0xa0; P0 = 0x00;
			if(Start == 0)
			{
			    Sonic = ReadDistance();
		 	 	if(Sonic <= 30 && Voltage >=1)
				{
					yi = 1;er = 11;san = 11;si = Sonic / 10;wu = Sonic %10;liu = 11;qi = 11;ba = 1;
				}
				else if(Sonic > 30 && Voltage >=1)
				{
					yi = 2;er = 11;san = 11;si = Sonic / 10;wu = Sonic %10;liu = 11;qi = 11;ba = 2;
				}
			}
			else if(Start == 1)
			{
				P2 = 0xa0; P0 = 0x10;
			   yi = 2,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = Transfer1/10,ba = Transfer1%10;
			}
			else if(Start == 2)
			{
				P2 = 0xa0; P0 = 0x00;
				 if(m == 0)
				 {P2 = 0x80; P0 = 0xff;}
				 else if(m == 1)
				 {P2 = 0x80; P0 = 0xf7;}
			}
		}
		else if(Voltage >= 4)  // overload
		{
			   if(j == 1)
			   {P2 = 0x80; P0 = 0xfb;}
			   else if(j == 0)
			   {P2 = 0x80; P0 = 0xff;} 
				P2 = 0xa0; P0 = 0x40;
		}

		if(S6 == 1)
		{		 
			if(k %2 == 0)
			{yi = 1,er = 11,san = 11,si = Transfer1/10,wu = Transfer1%10,liu = 11,qi = Transfer2/10,ba = Transfer2%10;}
			else if(k %2 == 1)
			{yi = 1,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = Transfer2/10,ba = Transfer2%10;}
		}
		else if(S6 == 2)
		{ 
			if(k %2 == 0)
			{yi = 2,er = 11,san = 11,si = Transfer1/10,wu = Transfer1%10,liu = 11,qi = 11,ba = 11;}
			else if(k %2 == 1)
			{yi = 2,er = 11,san = 11,si = Transfer1/10,wu = Transfer1%10,liu = 11,qi = Transfer2/10,ba = Transfer2%10;}
		}
	 	ScanKey();
	 	Display1(yi,er);
		Display2(san,si);
		Display3(wu,liu);
		Display4(qi,ba);
	 }
}

void Time0() interrupt 1
{
	i++;
	l++;
//	intr++;
	if(Start == 2)
	{  
		n++;
		if(n >= 250)
		{n = 0;m = ~m;}
	}
	if(i >= 250)
	{
		i = 0;
		j = ~j;	
		k++;
		if(k>=10)
		k = 0;
	}
	if(Start == 1)
	{
		l++;
		if(l >=  1000)
		{	
			l = 0;
			Transfer1--;
			if(Transfer1 <= 0)
			{
			Transfer1 = 0;
			//P2 = 0xa0; P0 = 0x00;
			Start = 0;
			}
		}
	}
	if(++intr >= 100)
	{
		s_flag = 1;
		intr = 0;
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
	ET0 = 1;
	EA = 1;
}

 void Timer1Init()
{
	AUXR |= 0x40;
	TMOD &= 0x0f;
}

void IniAll()
{
	P2 = 0xa0; P0 = 0x00;
	P2 = 0x80; P0 = 0xff;
	P2 = 0xc0; P0 = 0xff;
	P2 = 0xff; P0 = 0xff;
}
 
