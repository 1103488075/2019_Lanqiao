#include "STC15F2K60S2.h"
#include "allinit.h"
#include "PWM.h"

#define uchar unsigned char
#define uint unsigned int

//sbit Output = P0^5;  //方波输出口

void main(void)
{
	allinit();
	Timer1_Init();
	P2=(P2&0x1f)|0x80;
	while(1);
	
//	//产生方波的部分
//	smg_Timer0init();
//	while(1)
//	{
//		P2 =(P2&0x1f)|0xA0;
//		if(cnt < 50)
//		Output = 1;
//		else
//		Output = 0;
//		P2 &= 0x1f;
//	}
	
}