#include"STC15F2K60S2.h"
#include"allinit.h"
#include"smg.h"
#include"onewire.c"
#include"iic.c"
#include"keypad.h"
//#include"keypad.c"

#define uchar unsigned char
#define uint unsigned int


//函数声明
void delayms(int ms);
void self_inspection();

void main(void)
{
	uint Temperature,Temperature_H; //温度
	self_inspection();
	allinit();
	smg_Timer0init();
	Write_AT24C02(0x00,0x00);
	while(1)
	{
		key_down();
		if(flag200ms == 1)
		{
			flag200ms = 0;
			Temperature = Temper_Read();
		}
		if(key_value == 4)
		{
			dspbuff[4] = 3;
			dspbuff[5] = 0;
			dspbuff[6] = 5;
			dspbuff[7] = 0;
		}
		if(key_value == 5)
		{
			if(SetFlag5 == 0)
			{
			 dspbuff[4] = Temperature/100;
		   dspbuff[5] = Temperature%100/10+18;
		   dspbuff[6] = Temperature%100%10;
		   dspbuff[7] = 12;
			}
			else
			{
			 Temperature_H=Temperature*1.8+32;
			
			 dspbuff[4] = Temperature_H/100;
		   dspbuff[5] = Temperature_H%100/10+18;
		   dspbuff[6] = Temperature_H%100%10; 
			 dspbuff[7] = 15;
			}
		}
		if(key_value == 6)
		{
			Write_AT24C02(0x00,Temperature);
		}
		if(key_value == 7)
		{
			if(SetFlag7 == 0)
			{
				Temperature = ReadByte_AT24C02(0x00);
				dspbuff[4] = Temperature/100;
				dspbuff[5] = Temperature%100/10+18;
				dspbuff[6] = Temperature%100%10;
				dspbuff[7] = 12;
			}
			else
			{
				Temperature = ReadByte_AT24C02(0x00);
				Temperature_H=Temperature*1.8+32;
				dspbuff[4] = Temperature_H/100;
				dspbuff[5] = Temperature_H%100/10+18;
				dspbuff[6] = Temperature_H%100%10;
				dspbuff[7] = 15;
			}
		}
			
	}
}


void self_inspection()
{
	
	P2=0x80;
	P0=0x00;//打开所有LED
	
	P2=0xC0;//打开U6
	P0=0xFF;
	P2=0xE0;//打开U7
	P0=0x00;//打开所有数码管
	
	delayms(3000);

	P2=0x80;
	P0=0xFF;//关闭所有LED
	
	P2=0xC0;
	P0=0xFF;
	P2=0xFF;
	P0=0xFF;//关闭所有数码管
	
	P2=0xA0;
	P0=0x40;
	delayms(200);
	P2=0xA0;
	P0=0x00;	
}
void delayms(int ms)// 任意ms延时 存在问题，从何而来 
{
	int i,j;
	for(i=ms;i>0;i--)
	{for(j=845;j>0;j--);}
}