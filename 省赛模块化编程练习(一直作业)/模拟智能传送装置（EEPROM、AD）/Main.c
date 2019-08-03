#include "Hread.h"
#include "Display.h"
#include "ScanKey.h"
#include "iic.h"
 
uint temp = 0;
uint Value = 0; 
uint Weight[];
uchar i,j,k;	
uchar weishu = 0x00;
void InitAll();
void Timer0Init(void);

void main()
{
	InitAll();
 	Timer0Init();
	while(1)
	{
		temp = GetAD(0x03);
		temp = temp *10;

		yi = temp/100;er = temp/10%10;san = temp%10;
 
		ScanKey();
		Display1(yi,er);
		Display2(san,si);
		Display3(wu,liu);
		Display4(qi,ba);

		if(Start == 0)
		{
			P2 = 0x80; P0 = 0xff;
			P2 = 0xa0; P0 = 0x00;
		}
		else if(Start == 1)
		{
			P2 = 0xa0; P0 = 0x10;//pen relay
		}

		if(temp > 750)
		{
			P2 = 0xa0; P0 = 0x40;	  //open buzz	over relay
			P2 = 0x80; P0 = 0xff;
			EA = 0; ET0 = 0;

			if(Value != temp)
			{
				EEPROM_Write(weishu,temp);
				weishu = weishu + 1;
				if(weishu == 0xff)
				weishu = 0x00;
			}
			else if(Value == temp)
			{
			   	EEPROM_Write(weishu,temp);
			}
			Value = temp;
		}

//		else if(temp <= 750 && Start == 1)
//		{
//			P2 = 0xa0; P0 = 0x00;
//		}	 
	}
}
void Time0() interrupt 1
{
 
   if(Start == 1)
   {
	i++;
	 if(i>=100)
	 {
	   i = 0;
	   if(direction == 1)
	   {
		   	j++;
	   		P2 = 0x80; P0 = 0xfe;
	   		P0 = _crol_(P0,j);
	   		if(j > 7)
	   		{j = 0;P0 = 0xfe;}
	   }
	   else if(direction == 2)
	   {
			j++;
			P2 = 0x80; P0 = 0x7f;
			P0 = _cror_(P0,j);
			if(j > 7)
			{j = 0; P0 = 0x7f;}
	   }
	  
	 }
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