 #include "Head.h"
#include "Display.h"
#include "Key.h"
#include "ds1302.h"
#include "onewire.h"
#include "iic.h"

void InitAll();

 	uchar temp;
void main()
{

	 InitAll();
	 Write_Time();
//	 yi = 1,er = 2,san = 3,si = 4,wu = 5,liu = 6,qi = 7,ba = 8;
//	EEPROM_Write(0x00,23);
	 while(1)
	 {
		 // Read_Time();
	 temp = Read_AD(0x03);
	 yi = temp/100;er = temp/10%10;san = temp%10;
		  //yi = Time[0]/10;er = Time[0]%10;

		  //si = Time[1]/10;wu = Time[1]%10;
	 	
		   	Key16();
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