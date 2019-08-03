#include "Head.h"
#include "Display.h"
#include "Key.h"
#include "ds1302.h"
#include "iic.h"
#include "onewire.h"

void InitAll();
uchar temp ;

void main()
{
	InitAll();
	Write_Time();

//	Write_EEPROM(0x00,24);
	while(1)
	{
//		Read_Time();
// 		temp = Read_18B20();
		yi = temp/100;er = temp/10%10;san = temp%10;
	 
		Key();
		Display1(yi,er);
		Display2(san,si);
		Display3(wu,liu);
		Display4(qi,ba);	
	}
	
}
void InitAll()
{
	P2 = 0xa0; P0 = 0x00;
	P2 = 0x80; P0 = 0xff;
	P2 = 0xc0; P0 = 0xff;
	P2 = 0xff; P0 = 0xff;
}