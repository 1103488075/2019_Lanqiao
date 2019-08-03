#include"STC15F2K60S2.h"
#include"allinit.h"
#include"smg.h"
#include"keypad.h"
#include"iic.c"

#define uchar unsigned char
#define uint unsigned int

uint WATER_PRICE = 0.5 * 100,TOTAL_PRICES = 0; //水价，总水量，总价
uint ADC_Value;

void main(void)
{
	allinit();
	smg_Timer0init();
	while(1)
	{
		key_down();
		ADC_Read(0x01,&ADC_Value);
		ADC_Value = fun(ADC_Value);
		if(ADC_Value > 125)  // 1.25
			LED1(0);
		else
			LED1(1);
		dspbuff[0] = 16; 
		dspbuff[1] = ADC_Value / 100 + 18; //小数点
		dspbuff[2] = ADC_Value / 10 % 10;
		dspbuff[3] = ADC_Value % 10;
		if(overflag == 0)
		{
			dspbuff[4] = WATER_TOTAL  / 1000;
			dspbuff[5] = WATER_TOTAL  % 1000 / 100 + 18;
			dspbuff[6] = WATER_TOTAL  % 100 / 10 ;
			dspbuff[7] = WATER_TOTAL  % 10;
		}
		if(key_value == 7)
		{	
			RELAY(1);	
			if(flag100ms == 1 && fallflag == 1)
			{
				flag100ms = 0;
				WATER_TOTAL++;
			}
		}
		if(key_value == 6 | WATER_TOTAL == 1099 )
		{
			fallflag = 0;
			overflag = 1;
			RELAY(0);
			TOTAL_PRICES =  WATER_PRICE *  WATER_TOTAL / 100;  // 实际 ( WATER_PRICE / 100 ) * ( WATER_TOTAL / 100 ) * 100
			dspbuff[4] = TOTAL_PRICES  / 1000;
			dspbuff[5] = TOTAL_PRICES  % 1000 / 100 + 18;
			dspbuff[6] = TOTAL_PRICES  % 100 / 10 ;
			dspbuff[7] = TOTAL_PRICES  % 10;
		}
	}
}