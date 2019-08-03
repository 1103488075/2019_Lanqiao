#include"STC15F2K60S2.h"
#include"allinit.h"
#include"smg.h"
#include"onewire.c"
#include"keypad.h"
#include"PWM.h"


#define uchar unsigned char
#define uint unsigned int



void main(void)
{
	uint temper = 0;//温度
	allinit();
	smg_Timer0init();
	Timer1_Init();
	while(1)
	{
		key_down();
		temper = Temper_Read();
		/*-----------------工作方式选择----------------------------*/
		switch(MODE)
		{
			case(1) : PWMConter = 20;LED1(1);break;
			case(2) : PWMConter = 30;LED2(1);break;
			case(3) : PWMConter = 70;LED3(1);break;
		}

		if(flag1s == 1 && PWMflag)
		{
			flag1s = 0;
			TIME--;
		}
		if(TIME == 0)
			PWMflag = 0;
		else
			PWMflag = 1;
		if(SetFlag7 == 0)
		{
			dspbuff[0] = 17;
			dspbuff[1] = MODE;
			dspbuff[2] = 17;
			dspbuff[3] = 16;
			dspbuff[4] = TIME / 1000;
			dspbuff[5] = TIME / 100 % 10;
			dspbuff[6] = TIME / 10 % 10;
			dspbuff[7] = TIME % 10;
		}
		else
		{
			dspbuff[0] = 17;
			dspbuff[1] = 4;
			dspbuff[2] = 17;
			dspbuff[3] = 16;
			dspbuff[4] = 16;
			dspbuff[5] = temper / 10;
			dspbuff[6] = temper % 10;
			dspbuff[7] = 12;
		}
	}
}