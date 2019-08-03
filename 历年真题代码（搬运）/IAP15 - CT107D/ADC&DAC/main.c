#include"STC15F2K60S2.h"
#include"allinit.h"
#include"smg.h"
#include"iic.c"


#define  uchar unsigned char 
#define  uint  unsigned int 

/*===============================================
 指示部分
===================================================*/
void BUZZ(uchar i)  //1 开
{
	if(i)
	{
	  P2 = (P2&0x1f)|0xA0;
    P0 = 0x40;
	  P2 &=0x1f;
	}
	else
	{
		P2 = (P2&0x1f)|0xA0;
    P0 = 0x00;
	  P2 &=0x1f;
	}
}

void LED1(uchar i)  //1 开
{
	if(i)
	{
	  P2 = (P2&0x1f)|0x80;
    P0 = 0x7f;
	  P2 &=0x1f;
	}
	else
	{
	  P2 = (P2&0x1f)|0x80;
    P0 = 0xff;
	  P2 &=0x1f;
	}
}

void LED2(uchar i)  //1 开
{
	if(i)
	{
	  P2 = (P2&0x1f)|0x80;
    P0 = 0xbf;
	  P2 &=0x1f;
	}
	else
	{
	  P2 = (P2&0x1f)|0x80;
    P0 = 0xff;
	  P2 &=0x1f;
	}
}
/*==================================================*/
void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void main(void)
{
	uint ADC_Value;
	allinit();
	smg_Timerinit();
//	ADC_Init(0x01); //1 为光敏， 3  为Rb2电位器
	while(1)
	{
		//读取通道3 AD 模数转换的值，单端输入
		if(ADC_Read(0x03,&ADC_Value)) LED1(1); else  LED1(0);
		//把 AD 模数转换得到的数值再送给PCF8591 经过DA数模转换转换为模拟量控制模拟量输出口的小灯 
		if(DAC_Out(ADC_Value)) LED2(1); else LED2(0);  //为什么把这一行注释掉，第一个小灯常亮？
		//显示
		ADC_Value = fun(ADC_Value);
		dspbuff[0]=ADC_Value/100+17;
		dspbuff[1]=ADC_Value%100/10;
		dspbuff[2]=ADC_Value%100%10;
		if(ADC_Value > 150)   BUZZ(1); else BUZZ(0);
		Delay100ms();
	}
	
}