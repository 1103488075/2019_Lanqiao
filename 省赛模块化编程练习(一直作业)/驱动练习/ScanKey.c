#include "ScanKey.h"
#include "Display.h"
uchar S7 = 0,S6 = 0,S5 = 0,S4 = 0;

uchar KeyValue = 0;
void ScanKey()
{
	if(P30 == 0)
	{
		Delay2ms();
		if(P30 == 0)
		{
	 		S7 = 1;
		}
		while(!P30);
	}
	else if(P31 == 0)
	{
		Delay2ms();
		if(P31 == 0)
		{
	 		S6 = 1;
		}
		while(!P31);
	}
	 else if(P32 == 0)
	{
		Delay2ms();
		if(P32 == 0)
		{
	 		S5 = 1;
		}
		while(!P32);
	}
	else if(P33 == 0)
	{
		Delay2ms();
		if(P33 == 0)
		{
	 		S4 = 1;
		}
		while(!P33);
	}
}

//void ScanKey16()
//{
//	P3 = 0x0f;
//	P42 = 0; P44 = 0;
//	if(P3 != 0x0f)
//	{
//		Delay2ms();
//		if(P3 != 0x0f)
//		{
//			P3 = 0x03;
//			P42 = 1; P44 = 1;
//			
//			 if((P3 == 0x03)&&(P42 == 1)&&(P44 == 0))
//			 KeyValue = 0;
//			 else if((P3 == 0x03)&&(P42 == 0)&&(P44 == 1))
//			 KeyValue = 1;
//			 else if((P3 == 0x01)&&(P42 == 1)&&(P44 == 1))
//			 KeyValue = 2;
//			 else if((P3 == 0x02)&&(P42 == 1)&&(P44 == 1))
//			 KeyValue = 3;
//
//			 P3 = 0x0f;
//			 P42 = 0; P44 = 0;
//
//			switch(P3)	
//			{
//				case(0x0e): KeyValue += 0;break;
//				case(0x0d): KeyValue += 4;break;
//				case(0x0b): KeyValue += 8;break;
//				case(0x07): KeyValue += 12;break;				
//			}
//			while(P3 != 0x0f);
//		}
//	}		
//}




