#include"STC15F2K60S2.h"
#include"allinit.h"
#include"smg.h"
#include"keypad.h"

#define uchar unsigned char
#define uint unsigned int

void main()
{
	allinit();
	smg_Timerinit();
	while(1)
	{
		key_down();
	  dspbuff[0]=key_value;
	}
}