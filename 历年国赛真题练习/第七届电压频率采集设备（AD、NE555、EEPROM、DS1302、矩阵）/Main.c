#include "Head.h"
#include "Display.h"
#include "Key.h"
#include "iic.h"
#include "ds1302.h"

void InitAll();
void Timer0Init();

double voltage = 0;

uint tt = 0;
bit flag = 0;

uchar VMAX = 20,VMIN = 10;
void main()
{

	InitAll();
	Timer0Init();
	Write_Time();
	while(1)
	{	   
		Read_Time();
 
		 if(S7 == 1)
		 {
		 //	S6 = 0;
			 	if(S4 == 0)
				{yi = Time[2]/10; er = Time[2]%10; san = 10; si = Time[1]/10; wu = Time[1]%10; liu = 10; qi = Time[0]/10; ba = Time[0]%10;}
				else if(S4 == 1)
				{
					if(Time[0]%2 == 1)
					{yi = Time[2]/10; er = Time[2]%10; san = 10; si = Time[1]/10; wu = Time[1]%10; liu = 10; qi = Time[0]/10; ba = Time[0]%10;}
					else if(Time[0]%2 == 0)
					{yi = 11; er = 11; san = 10; si = Time[1]/10; wu = Time[1]%10; liu = 10; qi = Time[0]/10; ba = Time[0]%10;}
				}
				else if(S4 == 2)
				{
					if(Time[0]%2 == 1)
					{yi = Time[2]/10; er = Time[2]%10; san = 10; si = Time[1]/10; wu = Time[1]%10; liu = 10; qi = Time[0]/10; ba = Time[0]%10;}
					else if(Time[0]%2 == 0)
					{yi = Time[2]/10; er = Time[2]%10; san = 10; si = 11; wu = 11; liu = 10; qi = Time[0]/10; ba = Time[0]%10;}
				}
				else if(S4 == 3)
				{
					if(Time[0]%2 == 1)
					{yi = Time[2]/10; er = Time[2]%10; san = 10; si = Time[1]/10; wu = Time[1]%10; liu = 10; qi = Time[0]/10; ba = Time[0]%10;}
					else if(Time[0]%2 == 0)
					{yi = Time[2]/10; er = Time[2]%10; san = 10; si = Time[1]/10; wu = Time[1]%10; liu = 10; qi = 11; ba = 11;}
				}			
		 }
//		 else if(S7 == 0)
//		 {yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = 11,ba = 11;}
//		 
		 if(S6 == 1)
		 {
		 //	S7 = 0;
		 	if(S4 == 0)
			{
				voltage = Read_AD(0x03);
				voltage = voltage*10;
			 	yi = 10,er = 1,san = 10,si = 11,wu = (uint)voltage/10,liu = (uint)voltage%10,qi = 0,ba = 0;
			}
			else if(S4 == 1)
			{
				if(Time[0]%2 == 1)
				{yi = VMAX/10,er = VMAX%10,san = 0,si = 0,wu = VMIN/10,liu = VMIN%10,qi = 0,ba = 0;}
				else if(Time[0]%2 == 0)
				{yi = 11,er = 11,san = 11,si = 11,wu = VMIN/10,liu = VMIN%10,qi = 0,ba = 0;}	
			}
			else if(S4 == 2)
			{
				if(Time[0]%2 == 1)
				{yi = VMAX/10,er = VMAX%10,san = 0,si = 0,wu = VMIN/10,liu = VMIN%10,qi = 0,ba = 0;}
				else if(Time[0]%2 == 0)
				{yi = VMAX/10,er = VMAX%10,san = 0,si = 0,wu = 11,liu = 11,qi = 11,ba = 11;}	
			}
		 }
		  
 	
		Key16();
		Display1(yi,er);
		Display2(san,si);
		Display3(wu,liu);
		Display4(qi,ba);	
	}
}

void Timer0()	interrupt 1
{
	tt++;
	if(tt >= 500)
	{tt = 0;flag = ~flag;}
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
