#include "Hread.h"
#include "Display.h"
#include "ScanKey.h"
#include "ds1302.h"
#include "iic.h"

void InitAll();
uchar temp;
uchar status = 0;//automation
uchar humidity = 0;
uchar operation = 0;
uchar fazhi = 50;
void main()
{
	InitAll();
	Write_Time();

	humidity = EEPROMRead(0x00);
	Delay2ms();

 	while(1)
 	{
		humidity = GetAD(0x03);
	 
		Read_Time();
 		if(S6 == 0)//clok and humidity display interface
		{
			Read_Time();
 			yi = Time[2]/10;er = Time[2]%10;san = 10;si = Time[1]/10;wu = Time[1]%10;
 			liu = 11;qi = humidity/10;ba = humidity %10;
		}
		else if(S6 == 1)//humidity seting interface
		{
		yi = 10,er = 11,san = 11,si = 11,wu = 11;
		liu = 11,qi = fazhi/10;ba = fazhi%10;
		}
  
		if(status == 0)//automation
		{
			 if(humidity > fazhi)
			 {
			 	P2 = 0xa0; P0 = 0x10;  //relay		buzz is 0x40
				P2 = 0x80; P0 = 0xfe;
			 }
			else if(humidity <= fazhi)
			{
				P2 = 0xa0; P0 = 0x00;
				P2 = 0x80; P0 = 0xff;
			}

		}
		else if(status == 1) 
		{
			if(operation == 0)
			{
				if(humidity < fazhi)
				{
					P2 = 0xa0; P0 = 0x40;
					P2 = 0x80; P0 = 0xfd;//open led2
				}
			}
			else if(operation == 1)
			{
				P2 = 0xa0; P0 = 0x00;
			}
			if(S5 == 1)
			{
					P2 = 0xa0; P0 = 0x10;
			}
			else if(S5 == 0)
			{
				P2 = 0xa0; P04 = 0;
			}
		
		}	                                  
		ScanKey();
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