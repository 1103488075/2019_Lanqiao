#include "Head.h"
#include "Display.h"
#include "ScanKey.h"
#include "ds1302.h" 
#include "iic.h" 
#include "Sonic.h"

void IniAll();
void Delay1000ms();
void Timer0Init(void);
void Timer1Init(void);

//----------------------Sonic
uint intr = 0;
bit s_flag = 0;

//-------------------------
uint i,j;
bit k = 0;
uchar temp;
uint Sonic = 30;
uchar chaoshengbo = 35;
Time2[]={23,23,23,0,0,0,0};

void main()
{

 	P2 = 0x80; P0 = 0xfe;
	P2 = 0xa0; P0 = 0x40;
	P2 = 0xc0; P0 = 0xff;
	P2 = 0xff; P0 = 0x00;
	Delay1000ms();
	IniAll();
	Timer1Init();
	Timer0Init();
	Sonic = EEPROM_Read(0x00);
	WriteTime();
	while(1)
	{
	 	chaoshengbo =  Read_Distance();
		 if(S7 == 0)
		 {
	 	 	ReadTime();
   	 		yi = Time[2]/10,er = Time[2]%10,san = 10,si = Time[1]/10,wu = Time[1]%10,liu = 10,qi = Time[0]/10,ba = Time[0]%10; 
   		 }
		  if(S7 == 1  )
		 {
		 		if(S6 == 0)
				{
			 	 yi = 10,er = 10,san = chaoshengbo/10;si = chaoshengbo%10;wu = 11;liu = 11;qi = 11;ba = 11;
				}
				else if(S6 == 1)
				{
				if(j %2 == 1){san = 11,si = 11;}
				else if(j %2 == 0){san = Sonic/10;si = Sonic%10;}
			  	}
		 
		 }
		  if(S6 == 1 && S7 != 1)
		 {
	 			if(j %2 == 1){yi = 11,er = 11;}
				else if(j %2 == 0){yi = Time[2]/10,er = Time[2]%10;}
		 }
		 else if(S6 == 2 )
		 {
	 			if(j %2 == 1){si = 11,wu = 11;}
				else if(j %2 == 0){si = Time[1]/10,wu = Time[1]%10;}
		 }
		 else if(S6 == 3 )
		 {
	 			if(j %2 == 1){qi = 11,ba = 11;}
				else if(j %2 == 0){qi = Time[0]/10,ba = Time[0]%10;}
		 }	
		  if(chaoshengbo > Sonic )
		  {
			  P2 = 0x80; P0 = 0xff;
		  }
		  else if(chaoshengbo < Sonic-15)
		  {
				P2 = 0xa0; P0 = 0x10;
		  }
		  else if(chaoshengbo < Sonic)
		  {
			  if(k == 1)
			  {
			   P2 = 0x80; P0 = 0xfe;
			  }
			  else if(k == 0)
			  {
			  	P2 = 0x80; P0 = 0xff;
			  }
			  
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
 
	 if(i >= 250)
	 {
	 	i = 0;
		j++;
		k = ~k;		

		if(j>= 10)
		j = 0;
	 }
	 if(++intr >= 100 )
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

void Timer1Init(void)
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
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
