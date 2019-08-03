#include "ScanKey.h"
#include "Display.h"
#include "iic.h"
uchar S7 = 0,S6 = 0,S5 = 0,Start = 0;
uchar Value = 0;
void ScanKey()
{
	if(P30 == 0)
	{
		Delay2ms();
		if(P30 == 0)
		{
			if(Voltage < 1 )
			{
				if(S6 == 1)
				{
				Transfer1++;
				if(Transfer1 > 10)
				Transfer1 = 0;
					yi = 1,er = 11,san = 11,si = Transfer1/10,wu = Transfer1%10,liu = 11,qi = Transfer2/10,ba = Transfer2%10;
				}
				else if(S6 == 2)
				{
				Transfer2++;
				if(Transfer2 > 10)
				Transfer2 = 0;
				yi = 2,er = 11,san = 11,si = Transfer1/10,wu = Transfer1%10,liu = 11,qi = Transfer2/10,ba = Transfer2%10;
				}
			}
		}
		while(!P30);
	}
	else if(P31 == 0)
	{
		Delay2ms();
		if(P31 == 0)
		{
			if(Voltage < 1 )
			{
				if(S6 == 0)
				{
					S6 = 1;
				}
				else if(S6 == 1)
				{
					S6 = 2;
				}
				else if(S6 == 2)
				{
					S6 = 3; 
					yi = 3,er = 11,san = 11,si = Transfer1/10,wu = Transfer1%10,liu = 11,qi = Transfer2/10,ba = Transfer2%10;
				}
				else if(S6 == 3)
				{S6 = 0;
				yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = 11,ba = 11;
				EEPROMWrite(0x00,Transfer1);
				Delay2ms();
				EEPROMWrite(0x01,Transfer2);
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
			if(Voltage < 4 && Voltage >= 1)
			{
				if(Start == 1)
					Start = 2;
					else if(Start == 2)
					Start = 1;
			}
		}
		while(!P32);
	}
	else if(P33 == 0)
	{
		Delay2ms();
		if(P33 == 0)
		{
			if(Voltage < 4 && Voltage >= 1)
			{
				if(Start == 0)
					Start = 1;
			}
		}
		while(!P33);
	}
}

//void ScaKey16()
//{
//	 P42 = 0, P44 = 0;
//	 P3 = 0x0f;
//	 if(P3 != 0x0f)
//	 {
//	 	Delay2ms();
//		if(P3 != 0x0f)
//		{
//			P42 = 1, P44 = 1;
//			P3 = 0x03;
//
//			if((P3 ==0x03)&&(P42 == 1)&&(P44 == 0))
//				Value = 0;
//			else if((P3 ==0x03)&&(P42 == 0)&&(P44 == 1))
//				Value = 1;
//			else if((P3 ==0x01)&&(P42 == 1)&&(P44 == 0))
//				Value = 2;
//			else if((P3 ==0x02)&&(P42 == 1)&&(P44 == 0))
//				Value = 3;
//
//				P42 = 0; P44 = 0;
//				P3 == 0x0f;
//
//				switch(P3)
//				{
//					case (0x0e):Value += 0;break;
//					case (0x0d):Value += 4;break; 
//					case (0x0b):Value += 8;break;
//					case (0x07):Value += 12;break;
//				}
//
//
//				while(P3 != 0x0f);
//		}
//
//
//	 }
//
//}





