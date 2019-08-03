#include "ScanKey.h"
#include "Display.h"
#include "ds1302.h"
#include "iic.h"

uchar S7 = 0,S6 = 0,S5 = 0,S4 = 0;
 
void ScanKey()
{
	if(P30 == 0)
	{
		Delay2ms();
		if(P30 == 0)
		{
			if(status == 0)
			status = 1;
			else if(status == 1)
			status =  0;
		}
		while(!P30);
	}
	else if(P31 == 0)
	{
		Delay2ms();
		if(P31 == 0)
		{
			if(status == 0)
			{
				if(S6 == 0)
				{
				S6 = 1;
				}
				else if(S6 == 1)
				{
				S6 = 0;
				EEPROMWrite(0x00,fazhi);
				Delay2ms();
				}
			}
			else if(status == 1)
			{
				   	if(operation == 0)
					{
						operation = 1;
					
					}
					else if(operation == 1)
					{
						operation = 0;
					}

			}

		}
		while(!P31);
	}
	else if(P32 == 0)
	{
		Delay2ms();
		if(P32 == 0)
		{
			if(status == 0)
			{
				if(S6 == 1)
				{
					fazhi = fazhi+1;
				}
			}
			else if(status == 1)
			{
			   	if(S5 == 0)
				S5 = 1;
			 
			}
		}
		while(!P32);
	}
	else if(P33 == 0)
	{
		Delay2ms();
		if(P33 == 0)
		{
			if(status == 0)
			{
				if(S6 == 1)
				{
					fazhi = fazhi-1;
				}
			}
			else if(status == 1)
			{
				if(S5 == 1)
				S5 = 0;
			}
		}
		while(!P33);
	}
}
 