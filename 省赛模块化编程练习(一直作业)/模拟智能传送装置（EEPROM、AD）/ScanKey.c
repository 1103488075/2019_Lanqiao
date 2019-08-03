#include "ScanKey.h"
#include "Display.h"
uchar direction = 0;
uchar S7 = 0,S5 = 0,S6 = 0, Start = 0;
 
void ScanKey()
{
	if(P30 == 0)
	{
		Delay2ms();
		if(P30 == 0)
		{
			 Start = 0;
		}
		while(!P30);
	}
	else if(P31 == 0)
	{
		Delay2ms();
		if(P31 == 0)
		{
			if(Start == 1)
			{
				EA = 1;
				ET0 = 1;
				direction = 2;
			}
		}
		while(!P31);
	}
	else if(P32 == 0)
	{
		Delay2ms();
		if(P32 == 0)
		{
			if(Start == 1)
			{
				EA = 1;
				ET0 = 1;
				direction = 1;
			}
		}
		while(!P32);
	}
	else if(P33 == 0)
	{
		Delay2ms();
		if(P33 == 0)
		{
	 						P2 = 0xa0; P0 = 0x10;
			Start = 1;
		}
		while(!P33);
	}
}
//void ScanKey16()
//{
//	P42 = 0, P44 = 0;
//	P3 = 0x0f;
//
//	if(P3 != 0x0f)
//	{
//		Delay2ms();
//		if(P3 != 0x0f)
//		{
//			P42 = 1, P44 = 1;
//			P3 = 0x30;
//			if((P30 == 0x30)&&(P42 == 1)&&(P44 == 0))
//			KeyValue = 0;
//			else if((P30 == 0x30)&&(P42 == 0)&&(P44 == 1))
//			KeyValue = 1;
//			else if((P30 == 0x10)&&(P42 == 1)&&(P44 == 1))
//			KeyValue = 2;
//			else if((P30 == 0x20)&&(P42 == 1)&&(P44 == 0))
//			KeyValue = 3;
//
//			P42 = 0; P44 = 0;
//			P3 = 0x0f;
//			switch(P3)
//			{
//				case(0x0e) KeyValue +=0;break;
//				case(0x0d) KeyValue +=4;break;
//				case(0x0b) KeyValue +=8;break;
//				case(0x07) KeyValue +=12;break;
//			}
//
//			switch(KeyValue)
//			{
//
//			}
//		   (P3 != 0x0f);
//		}
//	}
//}



