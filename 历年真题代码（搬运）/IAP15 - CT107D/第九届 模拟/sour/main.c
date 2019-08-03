#include"includes.h"

extern char dspbuff[8],ch,RxdByte;
extern bit flag1s;
extern bit  Send_Flag,Rec_Flag;
extern uchar num;
//全局变量
uchar sec = 0,min = 0,hour = 0;
uint sec_BCD,min_BCD,hour_BCD;

void main()
{
	allinit();
	smg_Timer0init();
	UartInit();
	sys_test();
	allinit();
	//开机显示 00-00-00
	dspbuff[7] = sec % 10;
	dspbuff[6] = sec / 10;
  dspbuff[5] = 17;
	dspbuff[4] = min % 10;
	dspbuff[3] = min / 10;
	dspbuff[2] = 17;
	dspbuff[1] = hour % 10;
	dspbuff[0] = hour / 10;
	while(1)
	{
		Timer0();
		key_down();
//		if(Send_Flag )     //只有标志位允许单片机才能发送给电脑
//		{
//	    Uart_TX(ch);   //单片机执行发送
//		}
		switch(RxdByte)
		{
			case(0xa0) : P2=(P2&0x1f)|0x80;P0=~(0x00);P2&=0x1f;break;
			case(0xa8) : P2=(P2&0x1f)|0x80;P0=~(0x08);P2&=0x1f;break;
			case(0xa4) : P2=(P2&0x1f)|0x80;P0=~(0x04);P2&=0x1f;break;
			case(0xac) : P2=(P2&0x1f)|0x80;P0=~(0x0c);P2&=0x1f;break;
			case(0xa2) : P2=(P2&0x1f)|0x80;P0=~(0x02);P2&=0x1f;break;
			case(0xaa) : P2=(P2&0x1f)|0x80;P0=~(0x0a);P2&=0x1f;break;
			case(0xa6) : P2=(P2&0x1f)|0x80;P0=~(0x06);P2&=0x1f;break;
			case(0xae) : P2=(P2&0x1f)|0x80;P0=~(0x0e);P2&=0x1f;break;
			case(0xa1) : P2=(P2&0x1f)|0x80;P0=~(0x01);P2&=0x1f;break;
			case(0xa9) : P2=(P2&0x1f)|0x80;P0=~(0x09);P2&=0x1f;break;
			case(0xa5) : P2=(P2&0x1f)|0x80;P0=~(0x05);P2&=0x1f;break;
			case(0xad) : P2=(P2&0x1f)|0x80;P0=~(0x0d);P2&=0x1f;break;
			case(0xa3) : P2=(P2&0x1f)|0x80;P0=~(0x03);P2&=0x1f;break;
			case(0xab) : P2=(P2&0x1f)|0x80;P0=~(0x0b);P2&=0x1f;break;
			case(0xa7) : P2=(P2&0x1f)|0x80;P0=~(0x07);P2&=0x1f;break;
			case(0xaf) : P2=(P2&0x1f)|0x80;P0=~(0x0f);P2&=0x1f;break;
			case(0xb0) : Rec_Flag = 1;break;
		}
		if(Rec_Flag)
		{
			ES=0;
			TI=1;
			printf("0x%2x,0x%2x,0x%2x\n",hour_BCD,min_BCD,sec_BCD);
			while(!TI);
			TI=0;
			ES=1;		
			Rec_Flag = 0;
		}
	}
}

void sys_test()
{
	static uchar i;
	for(i = 0;i < 8;i++)
	{
		P2 = (P2&0x1f) | 0x80;
		P0 = 0xFE<<i;
		Delay500ms();
		P2 &= 0x1f;	
	}
	for(i = 0;i < 8;i++)
	{
		P2 = (P2&0x1f) | 0x80;
		P0 = ~(0xfe<<i);
		Delay500ms();
		P2 &= 0x1f;	
	}
	for(i = 0;i < 8;i++)
	{
		dspbuff[i] = 26;
		Delay500ms();
	}
  for(i = 0;i < 8;i++)
	{
		dspbuff[i] = 16;
		Delay500ms();
	}
}

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Timer0()
{
	if(flag1s == 1)
	{
		flag1s = 0;
		sec++;
	}
	if(sec < 60)
	{
		dspbuff[6] = sec / 10;
		dspbuff[7] = sec % 10;
	}
	if(sec == 60)
	{
		sec = 0;
		min++;
		dspbuff[6] = sec / 10;
		dspbuff[7] = sec % 10;
		dspbuff[3] = min / 10;
		dspbuff[4] = min % 10;
		if(min == 60)
		{
			min = 0;
			hour++;
			dspbuff[3] = 0;
			dspbuff[4] = 0;
			dspbuff[6] = min / 10;
		  dspbuff[7] = min % 10;
			if(hour == 24)
				hour = 0;
		}
	}
	sec_BCD = (sec / 10)*16 + sec % 10;
  min_BCD = (min / 10)*16 + min % 10;
  hour_BCD = (hour / 10)*16 + hour % 10;	
}
