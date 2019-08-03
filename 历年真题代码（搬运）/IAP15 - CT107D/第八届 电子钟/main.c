#include"STC15F2K60S2.h"
#include"allinit.h"
#include"smg.h"
#include"keypad.h"
#include"onewire.c"
#include"ds1302.c"

#define uchar unsigned char
#define uint unsigned int

uchar Hour_Now,Min_Now,Sec_Now; //实时时间



void main(void)
{
	allinit();
	smg_Timer0init();
	DS1302_Init();
	//开始读取时间，防止时间一开始读不到为 00-00-00 ，触发闹钟提醒
	Hour_Now = Ds1302_Single_Byte_Read(ds1302_hr_addr);
	Min_Now = Ds1302_Single_Byte_Read(ds1302_min_addr);
	Sec_Now = Ds1302_Single_Byte_Read(ds1302_sec_addr);
	Secbuff = Sec_Now;
	Minbuff = Min_Now;
	Hourbuff = Hour_Now;
	while(1)
	{
		key_down();
		LED1(STAR);
		//时间读取
		if(flag200ms == 1)
		{
			flag200ms = 0;
			if(STAR_Flag == 1)
			  STAR = ~STAR;
			Temper = Temper_Read();
		  Hour_Now = Ds1302_Single_Byte_Read(ds1302_hr_addr);
		  Min_Now = Ds1302_Single_Byte_Read(ds1302_min_addr);
		  Sec_Now = Ds1302_Single_Byte_Read(ds1302_sec_addr);
			if(Secbuff != Sec_Now  && setnum7 == 0)
			{
				Secbuff = Sec_Now;
				Minbuff = Min_Now;
				Hourbuff = Hour_Now;
			}
		}
		/*------------------------默认显示--------------------------------------*/
		if(TIME_NOW_FLAG == 0 && TIME_BUZZ_FLAG == 0)
		{
			//闹钟判断
			if((Secbuff / 16) * 10 + Secbuff % 16 == Sec_Flag && (Minbuff / 16) * 10 + Minbuff % 16 == Min_Flag && (Hourbuff / 16) * 10 + Hourbuff %10 == Hour_Flag)
			{
				STAR_Flag = 1;
			}
			// 5S 后关闭
			if(flag5s == 1)
			{
				flag5s = 0;
				LED2(1);
				STAR = 0;
				STAR_Flag = 0;
			}
			if(dspbuff[2] != 16)
			{
			  dspbuff[0] = Hourbuff / 16; 
		    dspbuff[1] = Hourbuff % 16;
			  dspbuff[2] = 17;
		  	dspbuff[3] = Minbuff / 16;
		    dspbuff[4] = Minbuff % 16;
		  	dspbuff[5] = 17;
		  	dspbuff[6] = Secbuff / 16;
		    dspbuff[7] = Secbuff % 16;
			}
			
		}
		/*-------------------------S7 按键-------------------------------------*/
		if(Sec_Now % 2 == 0 && setnum7 == 1 && TIME_NOW_FLAG == 1 && TIME_BUZZ_FLAG == 0)
		{
			dspbuff[0] = 16;
		  dspbuff[1] = 16;
		}
		else if(Sec_Now % 2 != 0 &&  TIME_NOW_FLAG == 1 && TIME_BUZZ_FLAG == 0)
		{
		  dspbuff[0] = Hourbuff / 16; 
		  dspbuff[1] = Hourbuff % 16;
		}
		dspbuff[2] = 17;
		if(Sec_Now % 2 == 0 && setnum7 == 2 && TIME_NOW_FLAG == 1 && TIME_BUZZ_FLAG == 0)
		{
			dspbuff[3] = 16;
		  dspbuff[4] = 16;
		}
		else if(Sec_Now % 2 != 0  && TIME_NOW_FLAG == 1 && TIME_BUZZ_FLAG == 0)
		{
		  dspbuff[3] = Minbuff / 16;
		  dspbuff[4] = Minbuff % 16;
		}
		dspbuff[5] = 17;
		if(Sec_Now % 2 == 0 && setnum7 == 3 && TIME_NOW_FLAG == 1 && TIME_BUZZ_FLAG == 0)
		{
			dspbuff[6] = 16;
		  dspbuff[7] = 16;
		}
		else if(Sec_Now % 2 != 0 &&  TIME_NOW_FLAG == 1 && TIME_BUZZ_FLAG == 0)
		{
			dspbuff[6] = Secbuff / 16;
		  dspbuff[7] = Secbuff % 16;
		}
				/*-------------------------S6 按键-------------------------------------*/
		if(Sec_Now % 2 == 0 && setnum6 == 1 && (TIME_NOW_FLAG == 0 && TIME_BUZZ_FLAG == 1))
		{
			dspbuff[0] = 16;
		  dspbuff[1] = 16;
		}
		else if(Sec_Now % 2 != 0 &&  (TIME_NOW_FLAG == 0 && TIME_BUZZ_FLAG == 1))
		{
		  dspbuff[0] = Hour_Flag / 10; 
		  dspbuff[1] = Hour_Flag % 10;
		}
		dspbuff[2] = 17;
		if(Sec_Now % 2 == 0 && setnum6 == 2 && (TIME_NOW_FLAG == 0 && TIME_BUZZ_FLAG == 1))
		{
			dspbuff[3] = 16;
		  dspbuff[4] = 16;
		}
		else if(Sec_Now % 2 != 0 &&  (TIME_NOW_FLAG == 0 && TIME_BUZZ_FLAG == 1))
		{
		  dspbuff[3] = Min_Flag / 10;
		  dspbuff[4] = Min_Flag % 10;
		}
		dspbuff[5] = 17;
		if(Sec_Now % 2 == 0 && setnum6 == 3 && (TIME_NOW_FLAG == 0 && TIME_BUZZ_FLAG == 1))
		{
			dspbuff[6] = 16;
		  dspbuff[7] = 16;
		}
		else if(Sec_Now % 2 != 0 &&  (TIME_NOW_FLAG == 0 && TIME_BUZZ_FLAG == 1))
		{
			dspbuff[6] = Sec_Flag / 10;
		  dspbuff[7] = Sec_Flag % 10;
		}
	}
}