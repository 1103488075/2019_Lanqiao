#include"STC15F2K60S2.h"
#include"allinit.h"
#include"LED.c"
#define uchar unsigned char
#define uint  unsigned int

//º¯ÊıÉùÃ÷

void main()
{
	allinit();
	while(1)
	{
	if(P33==0)
	led_left();
	if(P32==0)
	led_right();	
  }
}

