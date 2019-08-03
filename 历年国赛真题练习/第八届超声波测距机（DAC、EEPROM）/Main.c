#include "Head.h"
#include "Display.h"
#include "Key.h"
#include "iic.h"
#include "Sonic.h"
 

void InitAll();
void Timer0Init(void);
void Timer1Init(void);

uint Distance[10];
uint intr = 0;	//timer0 value
bit s_flag = 0; 

uint addr = 0x00;//eeprom addr

uchar i = 0;  //s4 value
int j = 0;//timer0 value
uint k = 0,l = 0;//timer0 vlaue
bit flag1 = 0;

uint zone = 20;//sonic bad zone
void main()
{
 

	InitAll();
	Timer0Init();
	Timer1Init();
	zone = Eeprom_Read(0x10);
	Delay2ms();
	Distance[0] = Eeprom_Read(0x00);
	Delay2ms();
	Distance[1] = Eeprom_Read(0x01);
	Delay2ms();
	Distance[2] = Eeprom_Read(0x02);
	Delay2ms();
	Distance[3] = Eeprom_Read(0x03);
	Delay2ms();
 
	while(1)
	{

		 if(S5 == 1) //data display
		{
			//led8
		//	P2 = 0x80; P0 = 0x7f;
			if(S7 == 0)
			{yi = 1,er = 11,san = 11,si = 11,wu = 11,liu = Distance[0]/100,qi = Distance[0]%100/10,ba = Distance[0]%10;}
			else if(S7 == 1)
			{yi = 2,er = 11,san = 11,si = 11,wu = 11,liu = Distance[1]/100,qi = Distance[1]%100/10,ba = Distance[1]%10;}
			else if(S7 == 2)
			{yi = 3,er = 11,san = 11,si = 11,wu = 11,liu = Distance[2]/100,qi = Distance[2]%100/10,ba = Distance[2]%10;}
			else if(S7 == 3)
			{yi = 4,er = 11,san = 11,si = 11,wu = 11,liu = Distance[3]/100,qi = Distance[3]%100/10,ba = Distance[3]%10;}
		}
		else if(S6 == 1)
		{
		//	P2 = 0x80; P0 = 0xbf;
			if(S7 == 0)
			{zone = 0;yi = 13,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = zone/10%10,ba = zone %10;}
			else if(S7 == 1)
			{zone = 10;yi = 13,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = zone/10%10,ba = zone %10;}
			else if(S7 == 2)
			{zone = 20;yi = 13,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = zone/10%10,ba = zone %10;}
			else if(S7 == 3)
			{zone = 30;yi = 13,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = zone/10%10,ba = zone %10;}
		}

		if(flag1 == 1)
		{P2 = 0x80; P0 = 0xfe;}
		else if(flag1 == 0)
		{P2 = 0x80; P0 = 0xff;}
 
	 
		if(S5 == 1)
		{P2 = 0x80; P0 = 0x7f;}
		else if(S6 == 1)
		{P2 = 0x80; P0 = 0xbf;}
	 
	 
	 

	  	Key();
		Display1(yi,er);
		Display2(san,si);
		Display3(wu,liu);
		Display4(qi,ba);
	}
}

void Timer0() 	interrupt 1
{

	if(++intr >= 100)
	{
		s_flag = 1;
		intr = 0;
	}
	if(j >= 0)
	{j++;}
	if(i > 0 && j >= 500)
	{
		 flag1 = ~flag1;
		 j = 0;
		 l = l + 1;
		if(l > 5)
		{j = - 10;}
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
void Timer1Init(void)
{
	AUXR |= 0x40;
	TMOD &= 0x0f;
  
}

void InitAll()
{
	P2 = 0xa0; P0 = 0x00;
	P2 = 0x80; P0 = 0xff;
	P2 = 0xc0; P0 = 0xff;
	P2 = 0xff; P0 = 0xff;


}