#include "Hread.h"
#include "Key.h"
#include "Display.h"
#include "iic.h"
uint AdValue = 0,ADtt = 0;//ad switch
uint temp = 0; // eeprom save read
uint interval = 400;//led interval 400 - 1200
uint i = 0,j = 0,k = 0;// interrupt value
uchar Pattern = 1;
uchar t1,t2;//interval value
uchar pulse = 30;
uint flicker = 0;//seting pattern interval flicker
uchar luminance = 1,Light = 0;
void InitAll();
void Timer0Init(void);
void Timer1Init(void);
void main()
{
    InitAll();
    Timer0Init();
    Timer1Init();
	P2 = 0x80; P0 = 0xff;
	P2 = 0xc0; P0 = 0xff;
    interval =  EEPROMRead(0x00);
	interval = interval *10;
    while(1)
    {
		if(S6 == 0)
		{
		 EEPROMWrite(0x00,interval/10);
		 Delay2ms();
		 Delay2ms();
		 yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = 11,ba = 11;
		}
		else if(S6 == 1)
		{

				if(flicker %2 == 0)
				{
					yi = 11,er = 11,san = 11;
				}
				else if(flicker %2 == 1)
				{
				yi = 10,er = Pattern,san = 10;
				}
				if(interval >= 1000)
				{
					si = 11,wu = interval / 1000,liu = interval/100%10,qi = interval/10%10,ba = interval%10;
				}
				else if(interval < 1000)
				{
					si = 11,wu = 11,liu = interval/100%10,qi = interval/10%10,ba = interval%10;
				}			
		}
		else if(S6 == 2)
		{
			if(flicker %2 == 0)
			{
			liu = 11,qi = 11,ba = 11,wu = 11;
		
			}
			else if(flicker %2 == 1)
			{
				if(interval >= 1000)
				{
				wu = interval /1000,liu = interval/100%10,qi = interval/10%10,ba = interval%10;
				}
				else if(interval < 1000)
				{
				wu = 11,liu = interval/100%10,qi = interval/10%10,ba = interval%10;
				}
			}
			yi = 10,er = Pattern,san = 10,si = 11;
		}

 		ScanKey();
        Display1(yi,er);
        Display2(san,si);
        Display3(wu,liu);
        Display4(qi,ba);
    }
}
void Time0() interrupt 1	//tow ms interrupt once
{
    i++;
	k++;
	ADtt++;
	if(k >= 400)
	{
		k = 0;
		flicker++;
		if(flicker >= 10)
		flicker = 0;
	}
    if((i >=interval)&&(S7 == 1)) //i>= interval/2
    {
        i = 0;
        if(Pattern == 1)
        {
            P2 = 0x80; P0 = 0xfe;
            P0 = _crol_(P0, j);
            j++;
            if(j >= 8) j = 0;
            else if(P0 == 0xff) P0 = 0xfe;
        }
        else if(Pattern == 2)
        {
            P2 = 0x80; P0 = 0x7f;
            P0 = _cror_(P0, j);
            j++;
            if(j >= 8) j = 0;
             else if(P0 == 0xff) P0 = 0x7f;
        }
        else if(Pattern == 3)
        { 
          P2 = 0x80; t1 = 0x7f;t2 = 0xfe;
          P0 = _crol_(t1, j)&_cror_(t2, j);
          j++;
          if(j >= 5) j = 0;
          else if(P0 == 0xff){t1 = 0x7f; t2 = 0xfe;}
        }
        else if(Pattern == 4)
        {
            P2 = 0x80; t1 = 0xef; t2 = 0xf7;
            P0 = _crol_(t1, j)&_cror_(t2, j);
            j++;
            if(j >= 5) j = 0;
            else if(P0 == 0xff)
			{t1 = 0xef; t2 = 0xf7;}	
        }
    }
	else if(i == Light)
	{
		P2 = 0x80; P0 = 0xff;
	}
	if(ADtt >= 100)
	{
		ADtt = 0;
		AdValue = GetAD(0x03);
		if(AdValue<64)Light = 2;
		else if((AdValue>= 64)&&(AdValue<128))Light = 5;
		else if((AdValue >= 128)&&(AdValue<192))Light = 10;
		else if((AdValue>= 192)&&(AdValue <256))Light = 19;
	}


}
void Time1() interrupt 3
{
 
}
void InitAll()
{
    P2 = 0xa0; P0 = 0x00;
    P2 = 0x80; P0 = 0xff;
    P2 = 0xc0; P0 = 0xff;
    P2 = 0xff; P0 = 0xff; 
}
void Timer0Init(void)		//2 ms interrupt once�秒@11.0592MHz
{
	AUXR |= 0x80;		 
	TMOD &= 0xF0;		 
	TL0 = 0x9A;		 
	TH0 = 0xA9;	 
	TF0 = 0;	 
	TR0 = 1;	 
    ET0 = 1;
    EA = 1;
}
void Timer1Init(void)		//10微秒@11.0592MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x91;		//设置定时初值
	TH1 = 0xFF;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
   // ET1 = 1;
  //  EA = 1;
}
