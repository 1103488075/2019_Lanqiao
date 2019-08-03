#include "Head.h"
#include "Display.h"
#include "Key.h"
#include "Ds1302.h"	
#include "iic.h"

void InitAll();
void Timer0Init();
uchar temp;
uchar mode = 0;
uchar sonic = 31;//distance
uint i;
bit j = 0;
uchar a = 6,b = 5,c = 4,d = 3,e = 2,f = 1;
void main()
{	 
	InitAll();
	Timer0Init();
	Init_Time();
 
	while(1)
	{
	//	Read_Time();

		if((time[2] >= 7) && (time[2]<= 22)) //automation status
		{
			yi = time[2]/10,er = time[2]%10,san = 10,si = time[1]/10;
			wu = time[1]%10,liu = 10,qi = time[0]/10,ba = time[0]%10;
			//sonic
		}
		else if((time[2] < 7 ) )	 //operation status
		{
			if(flag2 == 1) //change password
			{
				yi = 11,er = 10,san = 11,si = 11;
				wu = 11,liu = 11,qi = 11,ba = 11;
				flag2 = 2;
			}
			else if(flag1 == 0)//input password
			{
			yi = 10,er = 10,san = 11,si = 11;
			wu = 11,liu = 11,qi = 11,ba = 11;
			}
			if((san == 11)&&(num == 1))
			{
				san = Password;
				num = 0;
			}
			else if((si == 11)&&(num == 1))
			{
				si = Password;
				num = 0;
			}
			else if((wu == 11)&&(num == 1))
			{
				wu = Password;
				num = 0;
			}
			else if((liu == 11)&&(num == 1))
			{
				liu = Password;
				num = 0;
			}
			else if((qi == 11)&&(num == 1))
			{
				qi = Password;
				num = 0;
			}
			else if((ba == 11)&&(num == 1))
			{
				ba = Password;
				num = 0;
			} 
			if(flag1 == 1)
			{
				if((san == a)&&(si == b)&&(wu == c)&&(liu == d)&&(qi == e)&&(ba == f))
				{
					if(j == 0)
					{P2 = 0xa0; P0 = 0x10;EA = 1;ET0 = 1;}
					else if(j == 1)
					{P2 = 0xa0; P0 = 0x00;EA = 0; ET0 = 0;}
				}

			}
			if(flag2 == 2)
			{
				P2 = 0xa0; P0 = 0x00;
				if((san == a)&&(si == b)&&(wu == c)&&(liu == d)&&(qi == e)&&(ba == f))
				{
					yi = 10,er = 11,san = 11,si = 11;
					wu = 11,liu = 11,qi = 11,ba = 11;
					 flag2 = 3;
					 if(flag2 == 3)
					 {
			 				if((san == 11)&&(num == 1))
							{
								san = Password;
								num = 0;
							}
							else if((si == 11)&&(num == 1))
							{
								si = Password;
								num = 0;
							}
							else if((wu == 11)&&(num == 1))
							{
								wu = Password;
								num = 0;
							}
							else if((liu == 11)&&(num == 1))
							{
								liu = Password;
								num = 0;
							}
							else if((qi == 11)&&(num == 1))
							{
								qi = Password;
								num = 0;
							}
							else if((ba == 11)&&(num == 1))
							{
								ba = Password;
								num = 0;
							} 
					 }
				}
			}
		}  

		Key16();
	  	Display1(yi,er);
  		Display2(san,si);
  		Display3(wu,liu);
  		Display4(qi,ba);
	}

}
void Time0() interrupt 1	
{
	i++;
	if(i >= 2500)
	{
		j = 1;
		i = 0;	
	}	
}	
void InitAll()
{
	P2 = 0xa0; P0 = 0x00;
	P2 = 0x80; P0 = 0xff;
	P2 = 0xc0; P0 = 0xff;
	P2 = 0xff; P0 = 0xff;
	
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
