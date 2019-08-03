#include "Head.h"
#include "Display.h"
#include "key.h"
#include "iic.h"
#include "onewire.h"

void InitAll();
void Timer1Init(void);

double Voltage = 0;
uint Khz = 32;//频率
uint sum1;
float sum2;//temperature
uchar fazhi = 10;

uint tt;
bit flag = 0;
 


uchar addr;
void main()
{
	InitAll();
 	Timer1Init();
	while(1)
	{
 		 P2 = 0x80; P0 = 0xff;
		 if(S4 == 1)	 //voltage
		{
			 P2 = 0x80; P0 = 0xfe;
			sum1 = Read_18B20();  //read temperature int  
			sum2 =   Read_18B201(); //read temperature float
			yi = 15;er = 11;san = 11;si = 11;
			wu = sum1 / 10; liu = sum1 % 10; 
			qi = (uint)sum2 / 10; ba = (uint)sum2 % 10;
			jiu = 12; addr = 0x20;


		}
		else if(S4 == 2)   //khz
		{
			 P2 = 0x80; P0 = 0xfd;
			Voltage = Read_AD(0x03);
			Voltage = Voltage*10;
			yi = 13;er = 11;san = 11;si = 11;wu = 11;
			liu = 11; qi = (uint)Voltage/10;ba = (uint)Voltage%10;jiu = 12;addr = 0x40;
		}
		else if(S4 == 3)  //temperature
		{
			 P2 = 0x80; P0 = 0xfb;
			yi = 14;er = 11;san = 11;si = Khz/10;wu = Khz%10;
			liu = 0; qi = 0;ba = 0;jiu = 11;addr = 0xff;
		}
	 	if(S7 == 1)
		{
			yi = 17;er = 11;san = 11;si = 11;wu = 11;
			liu = 11; qi = fazhi/10;ba = fazhi%10;
			jiu = 12;addr = 0x40;
		}
		if(Voltage > fazhi)
		{
			if(flag == 0)
			{P2 = 0x80; P0 = 0x7f;}
			else if(flag == 1)
			{P2 = 0x80; P0 = 0xff;}
		}

		Key();
		Display1(yi,er);
	 	Display2(san,si);
	 	Display3(wu,liu);
	 	Display4(qi,ba);
		Display5(addr,jiu);	 //display location and "."
	}
}
void Timer0() interrupt 1
{
	tt++;
	if(tt >= 100)
	{
		tt = 0;
		flag = ~flag;
	}	
}
void Timer1Init(void)		//2毫秒@11.0592MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x9A;		//设置定时初值
	TH1 = 0xA9;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	ET0 = 1;
	EA = 1;
}

void InitAll()
{
	P2 = 0xa0; P0 = 0x00;
	P2 = 0x80; P0 = 0xff;
	P2 = 0xc0; P0 = 0xff;
	P2 = 0xff; P0 = 0xff;
}