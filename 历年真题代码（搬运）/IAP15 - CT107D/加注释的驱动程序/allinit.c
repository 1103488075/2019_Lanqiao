#include"includes.h"


void allinit()
{
	P2=(P2&0x1f)|0x80;
	P0=0xff;
	P2&=0x1f;

	P2=(P2&0x1f)|0xA0;
	P04=0;
	P06=0;
	P2&=0x1f;

	P2=(P2&0x1f)|0xc0;
	P0=0xff;
	P2&=0x1f;
	P2=(P2&0x1f)|0xe0;
	P0=0xFF;
	P2&=0x1f;
}
/*===============================================
 指示部分
===================================================*/
//void RELAY(bit i)  //1 开
//{
//	if(i)
//	{
//	  P2 = (P2&0x1f)|0xA0;
//    P0 = 0x10;
//	  P2 &=0x1f;
//	}
//	else
//	{
//		P2 = (P2&0x1f)|0xA0;
//    P0 = 0x00;
//	  P2 &=0x1f;
//	}
//}

//void BUZZ(bit i)  //1 开
//{
//	if(i)
//	{
//	  P2 = (P2&0x1f)|0xA0;
//    P0 = 0x40;
//	  P2 &=0x1f;
//	}
//	else
//	{
//		P2 = (P2&0x1f)|0xA0;
//    P0 = 0x00;
//	  P2 &=0x1f;
//	}
//}

//void LED1(bit i)  //1 开
//{
//	if(i)
//	{
//	  P2 = (P2&0x1f)|0x80;
//    P0 = 0xfe;
//	  P2 &=0x1f;
//	}
//	else
//	{
//	  P2 = (P2&0x1f)|0x80;
//    P0 = 0xff;
//	  P2 &=0x1f;
//	}
//}

//void LED2(bit i)  //1 开
//{
//	if(i)
//	{
//	  P2 = (P2&0x1f)|0x80;
//    P0 = 0xfd;
//	  P2 &=0x1f;
//	}
//	else
//	{
//	  P2 = (P2&0x1f)|0x80;
//    P0 = 0xff;
//	  P2 &=0x1f;
//	}
//}
//void LED3(bit i)  //1 开
//{
//	if(i)
//	{
//	  P2 = (P2&0x1f)|0x80;
//    P0 = 0xfb;
//	  P2 &=0x1f;
//	}
//	else
//	{
//	  P2 = (P2&0x1f)|0x80;
//    P0 = 0xff;
//	  P2 &=0x1f;
//	}
//}
//void LED4(bit i)  //1 开
//{
//	if(i)
//	{
//	  P2 = (P2&0x1f)|0x80;
//    P0 = 0xf7;
//	  P2 &=0x1f;
//	}
//	else
//	{
//	  P2 = (P2&0x1f)|0x80;
//    P0 = 0xff;
//	  P2 &=0x1f;
//	}
//}
void LED7(bit i)  //1 开
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
void LED8(bit i)  //1 开
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

