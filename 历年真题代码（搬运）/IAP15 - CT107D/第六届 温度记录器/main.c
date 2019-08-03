#include"STC15F2K60S2.h"
#include"allinit.h"
#include"smg.h"
#include"onewire.c"
#include"ds1302.c"
#include"keypad.h"

#define uchar unsigned char
#define uint unsigned int



void main(void)
{
	allinit();
	smg_Timer0init();
	while(1)
	{
		key_down();
		/*-----------------------------按键 S4------------------------------------------------------------------*/
		if(key_value == 4)
		{
			switch(i4)
			{
				case(1) : TIME_INTERVAL = 1;break;
				case(2) : TIME_INTERVAL = 5;break;
				case(3) : TIME_INTERVAL = 30;break;
				case(4) : TIME_INTERVAL = 60;break;
			}
			
		}
		/*---------------------------------数码管显示模块--------------------------------------------*/
		if(Init_Flag == 1)
		{
			dspbuff[0] = 16;
			dspbuff[1] = 16;
			dspbuff[2] = 16;
			dspbuff[3] = 16;
			dspbuff[4] = 16;
			dspbuff[5] = 17;
			dspbuff[6] = TIME_INTERVAL / 10;
			dspbuff[7] = TIME_INTERVAL % 10;
		}
		if(TIME_Dis_Flag == 1)
		{
			dspbuff[0] = Ds1302_Single_Byte_Read(ds1302_hr_addr) / 16;
			dspbuff[1] = Ds1302_Single_Byte_Read(ds1302_hr_addr) % 16;
			
			dspbuff[3] = Ds1302_Single_Byte_Read(ds1302_min_addr) / 16;
			dspbuff[4] = Ds1302_Single_Byte_Read(ds1302_min_addr) % 16;
			
			dspbuff[6] = Ds1302_Single_Byte_Read(ds1302_sec_addr) / 16;
			dspbuff[7] = Ds1302_Single_Byte_Read(ds1302_sec_addr) % 16;
			if(Ds1302_Single_Byte_Read(ds1302_sec_addr) % 2 == 0)
			{
				dspbuff[5] = SEC % 10;
			  dspbuff[2] = SEC / 10;
			}
			else
			{
				dspbuff[5] = 17;
			  dspbuff[2] = 17;
			}
		}

		/*----------------------------温度采集--------------------------------------------------------------------------------*/
		if(TEMPER_Read_Flag == 1)
		{
			if(SEC == TIME_INTERVAL)
			{
				SEC = 0;
        TEMPERATURES[index] = Temper_Read();
				index++;
		  }
		}
		if(index == 10)
		{
			TEMPER_Read_Flag = 0;
			Init_Flag = 0;
			TIME_Dis_Flag = 0;
			TEMPER_Dis_Flag = 1;
			if(TWINKLE)
			LED1(STAR);
		}
		/*---------------------------显示采集温度-----------------------------------------------------------------------------*/
		if(TEMPER_Dis_Flag == 1)
		{
			switch(i6)
			{
				case(0): TEMPERATURE = TEMPERATURES[0];break;
				case(1): TEMPERATURE = TEMPERATURES[1];break;
				case(2): TEMPERATURE = TEMPERATURES[2];break;
				case(3): TEMPERATURE = TEMPERATURES[3];break;
				case(4): TEMPERATURE = TEMPERATURES[4];break;
				case(5): TEMPERATURE = TEMPERATURES[5];break;
				case(6): TEMPERATURE = TEMPERATURES[6];break;
				case(7): TEMPERATURE = TEMPERATURES[7];break;
				case(8): TEMPERATURE = TEMPERATURES[8];break;
				case(9): TEMPERATURE = TEMPERATURES[9];break;
			}
			dspbuff[0] = 17;
			dspbuff[1] = i6 / 10;
			dspbuff[2] = i6 % 10;
			dspbuff[3] = 16;
			dspbuff[4] = 16;
			dspbuff[5] = 17;
			dspbuff[6] = TEMPERATURE / 10;
			dspbuff[7] = TEMPERATURE % 10;
		}
		/*----------------------由 DS1302 定时 1s---------------------------------------------------------------------*/
		if(flag500ms == 1 && key_value == 5)
		{
			flag500ms = 0;
			 SECNOW = Ds1302_Single_Byte_Read(ds1302_sec_addr);
			 if(SECNOW != SECTEMP)
			 {
				 SECTEMP = SECNOW;
				 SEC++;
			 }
		}
		/*---------------------------------------------------------------------------------*/
		if(flag1s == 1 && TWINKLE == 1)
		{
			flag1s = 0;
			STAR = ~STAR;
		}
	} // while(1)
}