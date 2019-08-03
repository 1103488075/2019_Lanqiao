#include "Head.h"
#include "Display.h"
#include "Key.h"
#include "onewire.h"
 
void InitAll();
void Timer0Init(void);
void Timer1Init(void);
uchar temp;
uchar PWM = 20;
int JobTime = 0;
   
void main()
{
 	InitAll();
  	Timer0Init();
	Timer1Init();
		ET1 = 1;
		ET0 = 1;
		EA = 1;
	while(1)
	{  
		if(S7 == 0)
		{
			if(S4 == 0)
			{yi = 10,er = 1,san = 10,si = 11,wu = 0,liu = JobTime/100,qi = JobTime/10%10,ba = JobTime%10;
			P2 = 0x80; P0 = 0xfe;}
			 else if(S4 == 1)
			{yi = 10,er = 2,san = 10,si = 11,wu = 0,liu = 0,qi = JobTime/10,ba = JobTime%10;
			P2 = 0x80; P0 = 0xfd;}
			 else if(S4 == 2)
			{yi = 10,er = 3,san = 10,si = 11,wu = 0,liu = 0,qi = JobTime/10,ba = JobTime%10;
			P2 = 0x80; P0 = 0xfb;}
		}
		else if(S7 == 1)
		{	
			P2 = 0x80; P0 = 0xff;
			temp = Read_18B20();
		   yi = 10,er = 4,san = 10,si = 11,wu = 11,liu = temp/10,qi = temp%10,ba = 12;
		}	

	
	 	if(JobTime <= 0)
		{
			ET1 = 0;
			ET0 = 0;
			JobTime = 0;
			P2 = 0x80; P0 = 0xff;
		}
			Key();
		Display1(yi,er);
		Display2(san,si);
		Display3(wu,liu);
		Display4(qi,ba);
	 }
	
}

void Time1()	interrupt 3
{
	static uint i;
	i++;
	if(i >= 1000)
	{
		i = 0;	
		JobTime--;
	}
}
void Time0()	interrupt 1
{
	 static uchar value;
	 value++;
	if(value >= 100)//1khz
	{
		value = 0;
		P34 = 0;
	}
	if(value < PWM) 
		P34 = 1;
	else
		P34 = 0;

} 
 void Timer1Init(void)		//2毫秒@11.0592MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xcd;		//设置定时初值
	TH1 = 0xd4;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	ET1 = 1;
	EA = 1;
}

 void Timer0Init(void)		//100微秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x91;		//设置定时初值
	TH0 = 0xff;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
//	ET0 = 1;
	EA = 1;

}

void InitAll()
{
	P2 = 0xa0; P0 = 0x00;
	P2 = 0x80; P0 = 0xff;
	P2 = 0xc0; P0 = 0xff;
	P2 = 0xff; P0 = 0xff;
				 	
}