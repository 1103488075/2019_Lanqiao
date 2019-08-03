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
			if(S7 == 0)
			{
			S7 = 1;
		//	S4 = 4;
			}
			else if(S7 == 1)
			{
				S7 = 0;
			 
			}
		}
		while(!P30);
	}

	else if(P31 == 0)
	{
		Delay2ms();
		if(P31 == 0)
		{
			if(S7 == 0||S7 == 2)
			{
				if(S6 == 0)
				{
					S7 = 2;
					S6 = 1;
				}
				else if(S6 == 1)
				{
					S6 = 2;
				}
				else if(S6 == 2)
				{
					S6 = 3;
				}
				else if(S6 == 3)
				{
					S6 = 0;
					S7 = 0;
					WriteTime();
				}
			}
			else if(S7 == 1)
			{
				 
				  if(S6 == 0)
				  {
				  S6 = 1;
				  }
				  else if(S6 == 1)
				  {
				  	EEPROM_Write(0x00,Sonic);
				  S6 = 0;
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
			if(S7 == 0||S7 == 2)
			{
				if(S6 == 1  )
				{Time[2]++;}
				else if(S6 == 2)
				{Time[1]++;}
				else if(S6 == 3)
				{Time[0]++;}
			}
			else if(S7 == 1)
			{
				if(S6 == 1)
				{
					Sonic++;
				}
			}
		 
		}
		while(!P32);
	}
	else if(P33 == 0)
	{
		Delay2ms();
		if(P33 == 0)
		{
		 	 if(S7 == 0||S7 == 2)
			 {
				if(S6 == 1  )
				{Time[2]--;}
				else if(S6 == 2)
				{Time[1]--;}
				else if(S6 == 3)
				{Time[0]--;}
			}
			else if(S7 == 1)
			{
				if(S6 == 1)
				{
					Sonic--;
				}
			}
		}
		while(!P33);
	}
}
//void ScanKey16()
//{
//	P42 = 0; P44 = 0;P3 = 0x0f;
//	if(P3 != 0x0f)
//	{
//		Delay2m();
//		if(P3 != 0x0f)
//		{
//			P42 = 1;P44 = 1;P3 = 0x30;
//			if((P3 == 0x30)&&(P42 == 1)&&(P44 == 0))
//			KeyValue = 0;
//			else if((P3 == 0x30)&&(P42 == 0)&&(P44 == 1))
//			KeyValue = 1;
//			else if((P3 == 0x10)&&(P42 == 1)&&(P44 == 1))
//			KeyValue = 2;
//			else if((P3 == 0x20)&&(P42 == 1)&&(P44 == 1))
//			KeyValue = 3;
//
//			P42 = 0;P44 = 0; P3 = 0x0f;
//			
//			switch(P3)
//			{
//				case (0x0e): KeyValue +=0;break;
//				case (0x0d): KeyValue +=4;break;
//				case (0x0b): KeyValue +=8;break;
//				case (0x07): KeyValue +=12;break;
//			} 
//
//			switch(KeyValue)
//			{
//				
//				
//
//			}
//			   while(P3 != 0x0f);
//		}
//	}
//
//}





