#include"intrins.h"

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

void led_left()
{
	static unsigned char ledchar=0xfe; //1111 1110
 	Delay100ms();                      
	if(P33==0)
	{
	  P2=(P2&0x1F)|0x80;
	  P0=ledchar;
	  P2=P2&0x1f;
		ledchar=_crol_(ledchar,1);
	}
}
void led_right()
{
	static unsigned char ledchar=0x7f; //0111 1111
	Delay100ms();
	if(P32==0)
	{
	  P2=(P2&0x1F)|0x80;
	  P0=ledchar;
	  P2=P2&0x1f;
		ledchar=_cror_(ledchar,1);
	}
}