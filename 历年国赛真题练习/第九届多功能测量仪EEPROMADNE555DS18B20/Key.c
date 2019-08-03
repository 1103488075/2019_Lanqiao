#include "Key.h"
#include "Display.h" 
#include "iic.h"

uchar S7 = 0,S6 = 0,S5 = 0,S4 = 0;
 
void key()
{
	if(P30 == 0)
	{
		Delay2ms();
		if(P30 == 0)
		{
		   if(S7 == 0)
		   {S7 = 1;	}
		   else if(S7 == 1)
		   {S7 = 0;S4 = 1;}
		}
		while(!P30);
	}
	else if(P31 == 0)
	{
		Delay2ms();
		if(P31 == 0)
		{
			if(S7 == 0)
			{
				 	 if(S6 == 0)
					{
						S6 = 1;		// temperature
						sum1 = Erprom_Read(0x00);//int
						sum2 = Erprom_Read(0x01);	//float
						yi = 16;er = 15;san = 11;si = 11;
						wu = sum1 / 10; liu = sum1 % 10; 
						qi = (uint)sum2 / 10; ba = (uint)sum2 % 10;
						jiu = 12; addr = 0x20;
					}
					else if(S6 == 1)
					{
						S6 = 2;	//voltage
						Voltage = Erprom_Read(0x03);
					 	yi = 16;er = 13;san = 11;si = 11;wu = 11;
						liu = 11; qi = (uint)Voltage/10;ba = (uint)Voltage%10;jiu = 12;addr = 0x40;
					}
					else if(S6 == 2)
					{
						S6 = 3;			 //khz
						Khz = Erprom_Read(0x04);
						yi = 16;er = 14;san = 11;si = Khz/10;wu = Khz%10;
						liu = 0; qi = 0;ba = 0;jiu = 11;addr = 0xff;
					}
					else if(S6 == 3)	//not display
					{S6 = 0;yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = 11,ba = 11,jiu = 11;}
			}
			else if(S7 == 1)
			{
	 
				fazhi = fazhi + 1;
				if(fazhi > 50)
				fazhi = 1;	
			}
		}
		while(!P31);
	}
	else if(P32 == 0)
	{
		Delay2ms();
		if(P32 == 0)
		{
		   Eeprom_Write(0x00,sum1);
		   	Delay2ms();
			Delay2ms();
		   Eeprom_Write(0x01,sum2);
		   	Delay2ms();
			Delay2ms();
		   Eeprom_Write(0x03,Voltage);
			Delay2ms();
			Delay2ms();
		   Eeprom_Write(0x04,Khz);
		   	Delay2ms();
			Delay2ms();
		   Eeprom_Write(0x05,fazhi);
		}
		while(!P32);
	}
	else if(P33 == 0)
	{
		Delay2ms();
		if(P33 == 0)
		{
		 	if(S4 == 0)
			{S4 = 1;}
			else if(S4 == 1)
			{S4 =2 ;}
			else if(S4 == 2)
			{S4 = 3;}
			else if(S4 == 3)
			{S4 = 0;yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = 11,ba = 11,jiu = 11;}
		}
		while(!P33);
	}
}
