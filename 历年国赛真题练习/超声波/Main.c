#include "Head.h"
#include "Display.h"

void IniAll();
void Timer0Init(void);
void Timer1Init(void);

 
 bit s_flag = 0;
 uint intr = 0;
 uint temp;


#define somenop {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();}
 

																					 
sbit TX = P1^0;
sbit RX = P1^1;

uchar ReadDistance();

void Send_wave();
uint t;
uint Distance;

			    

void main()
{
  	  IniAll();
	  Timer0Init();
	  Timer1Init();
	  ET0 = 1;
	  EA = 1;

	while(1)
	{
				if(s_flag)
				{
					s_flag = 0;
					Send_wave();
					TR1 = 1;
					while((RX == 1)&&(TF1 == 0));
					TR1 = 0;
			
					if(TF1 == 1)
					{
						TF1 = 0;
						Distance = 99;
					}
					else 
					{
						t = TH1;
						t <<= 8;
						t |= TL1;
						Distance = (unsigned int)(t*0.017);
						Distance = Distance/12;
					}
					TH1 = 0;
					TL1 = 0;
			
				}

		yi = Distance/100;
		er = Distance/10%10;
		san = Distance%10;
	 
		 Display1(yi,er);
		 Display2(san,si);
		 Display3(wu,liu);
		 Display4(qi,ba);
	}

}

void Timer0() interrupt 1
{
	TL0 = 0x9A;		//设置定时初值
	TH0 = 0xA9;		//设置定时初值
	if(++intr >= 100)
	{
		s_flag = 1;
		intr = 0;
	}
}
 	
void Send_wave()
{
	uchar i ;
	do
	{
		TX = 1;
		somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop ;somenop;
		TX = 0;
		somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;
	}while(i--);
}

void IniAll()
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
void Timer1Init()
{
	AUXR |= 0x40;
	TMOD &= 0x0f;
}

 
