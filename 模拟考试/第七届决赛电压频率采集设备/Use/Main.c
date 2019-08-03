 #include "Head.h"
 #include "Display.h"
 #include "Key.h"
 #include "ds1302.h"
 #include "iic.h"

 void InitAll();

 float AD = 0;
 char MAX = 20;
 char MIN = 10;
 uchar Khz = 10;
 uchar matter = 0;
void main()
{
	InitAll();
	Write_Time();
	MAX = EEPROM_Read(0x00);
	Delay2ms();
	MIN = EEPROM_Read(0x01);
	Delay2ms();
	while(1)
	{	  
		Read_Time();
		if(S7 == 1)
		{
			if(S4 == 0)
			{yi = Time[2]/10,er = Time[2]%10,san = 10,si = Time[1]/10,wu = Time[1]%10,liu = 10,qi = Time[0]/10,ba = Time[0]%10;	}
			else if(S4 == 1)
			{
				if(Time[0]%2 == 1)
				{yi = Time[2]/10,er = Time[2]%10,san = 10,si = Time[1]/10,wu = Time[1]%10,liu = 10,qi = Time[0]/10,ba = Time[0]%10;}
				else if(Time[0]%2 == 0)
				{yi = 11,er = 11,san = 10,si = Time[1]/10,wu = Time[1]%10,liu = 10,qi = Time[0]/10,ba = Time[0]%10;}		
			}
			else if(S4 == 2)
			{
				if(Time[0]%2 == 1)
				{yi = Time[2]/10,er = Time[2]%10,san = 10,si = Time[1]/10,wu = Time[1]%10,liu = 10,qi = Time[0]/10,ba = Time[0]%10;}
				else if(Time[0]%2 == 0)
				{yi = Time[2]/10,er = Time[2]%10,san = 10,si = 11,wu = 11,liu = 10,qi = Time[0]/10,ba = Time[0]%10;}		
			}
			else if(S4 == 3)
			{
				if(Time[0]%2 == 1)
				{yi = Time[2]/10,er = Time[2]%10,san = 10,si = Time[1]/10,wu = Time[1]%10,liu = 10,qi = Time[0]/10,ba = Time[0]%10;}
				else if(Time[0]%2 == 0)
				{yi = Time[2]/10,er = Time[2]%10,san = 10,si = Time[1]/10,wu = Time[1]%10,liu = 10,qi = 11,ba = 11;}		
			}
		}
		if(S6 == 1)
		{
			if(S4 == 0)
			{
			AD = Read_AD(0x03)*10;
			yi = 10,er = 1,san = 10,si = 11,wu = (int)AD/10,liu = (int)AD%10,qi = 0,ba = 0;
			}
			else if(S4 == 1)
			{
				if(Time[0]%2 == 1)
				{yi = MAX/10%10,er = MAX%10,san = 0,si = 0,wu = MIN/10%10,liu = MIN%10,qi = 0,ba = 0; }
				else if(Time[0]%2 == 0)
				{yi = 11,er = 11,san = 11,si = 11,wu = MIN/10%10,liu = MIN%10,qi = 0,ba = 0;}
			}
			else if(S4 == 2)
			{
				if(Time[0]%2 == 1)
				{yi = MAX/10%10,er = MAX%10,san = 0,si = 0,wu = MIN/10%10,liu = MIN%10,qi = 0,ba = 0; }
				else if(Time[0]%2 == 0)
				{yi = MAX/10%10,er = MAX%10,san = 0,si = 0,wu = 11,liu = 11,qi = 11,ba = 11;}
			}
		}
		if(S5 == 1)
		{
			if(S4 == 0)//khz display
			{	yi = 10,er = 2,san = 10,si = 0,wu = Khz/10%10,liu = Khz%10,qi = 0,ba = 0;  }
			else if(S4 == 1) //us display 
			{	yi = 10,er = 2,san = 10,si = 0,wu = 0,liu = 0,qi = 0,ba = 1;}
		}
		if(S9 == 1)
		{
			if(S4 == 0)
			{
				yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = matter/10%10,ba = matter%10;
			}
			else if(S4 == 1)
			{
				 yi = 0,er = 0,san = 10,si = 0,wu = 0,liu = 10,qi = 0,ba = 0;
			}
		}

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
