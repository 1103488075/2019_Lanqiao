#include "Head.h"
#include "Display.h"
#include "ScanKey.h"
#include "onewire.h"

void InitAll();
void Timer0Init();
uint i;
bit j;
uint qujian  = 400;
uchar temp = 0;
uchar TMIN = 25,TMAX = 35;

void main()
{
	InitAll();
		
   	  Timer0Init();

	while(1)
	{
	  	temp = Read_18B20();
 		if(set == 0)
		{
			if(temp < TMIN)
			{
				qujian = 400;
				if(j == 0)
				{P2 = 0x80; P0 = 0xfe;}
				else if(j == 1)
				{P2 = 0x80; P0 = 0xff;}

				P2 = 0xa0; P0 = 0x00;
			 
				yi = 10,er = 0,san = 10,si = 11,wu = 11,liu = 11,qi = temp/10,ba = temp%10;
			}
			else if(temp >= TMIN && temp <= TMAX)
			{
				qujian = 200;
					P2 = 0xa0; P0 = 0x00;
				if(j == 0)
				{P2 = 0x80; P0 = 0xfe;}
				else if(j == 1)
				{P2 = 0x80; P0 = 0xff;}
				yi = 10,er = 1,san = 10,si = 11,wu = 11,liu = 11,qi = temp/10,ba = temp%10;
			}
			else if (temp > TMAX)
			{
				P2 = 0xa0; P0 = 0x10;
				qujian = 100;
				if(j == 0)
				{P2 = 0x80; P0 = 0xfe;}
				else if(j == 1)
				{P2 = 0x80; P0 = 0xff;}
				yi = 10,er = 2,san = 10,si = 11,wu = 11,liu = 11,qi = temp/10,ba = temp%10;
			}
		}

		else if(set == 1)
		{
			P2 = 0x80; P0 = 0xff;
			
			 //  yi = 10,er = 11,san = 11,si = 11,wu = 11,liu = 10,qi = 11,ba = 11;
//			if(Value == 0)
//			{
//		  		yi = 10,er = 11,san = 11,si = 11,wu = 11,liu = 10,qi = 11,ba = 11;
//			 }
//			 else if(Value > 0)
//			 {

//			 	yi = 10,er = TMAX/10,san = TMAX %10,si = 11;
//				wu = 11,liu = 10,qi = TMIN/10,ba = TMIN%10;
//
//
//				TMAX =  (Value/1000)*10+(Value%1000/100);
//			   	TMIN = (Value%100/10)*10+(Value%10); 
//			
//
//			 
//				yi = 10,er = TMIN/10,san = TMIN %10,si = 11;
//				wu = 11,liu = 10,qi = TMAX/10,ba =TMAX%10;
				if(num == 1 && er == 11)
				{
					er = Value;
					num = 0;
					  
				}
				if(num == 1 && san == 11)
				{
				san = Value;
				num = 0;
				}
				if(num == 1 && qi == 11)
				{
					qi = Value;
					num = 0;	
				}
				if(num == 1 && ba == 11)
				{
					ba = Value;
					num = 0;	
				}
				TMAX = er *10 +san;
				TMIN = qi *10 +ba;
				if(a == 1)
				{
				TMAX =0;
				TMIN =0;
				er = 11,san = 11;
				qi  = 11,ba  =11;
				a = 0;
				}
				if(TMAX < TMIN)
				{P2 = 0x80;P0 = 0xfd;}
			 

		}
	

			
	 ScanKey16();
	 Display1(yi,er);
	 Display2(san,si);
	 Display3(wu,liu);
	 Display4(qi,ba);
	}

}
void Time0() interrupt 1
{
	i++;
	if(i >= qujian)
	{
		i = 0;
	   j = ~j;
	}	
}

void InitAll()
{
	P2 = 0xa0; P0 = 0x00;
	P2 = 0x80; P0 = 0xff;
	P2 = 0xc0; P0 = 0xff;
	P2 = 0xff; P0 = 0xff;
}
void Timer0Init(void)		//2秒@11.0592MHz
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


