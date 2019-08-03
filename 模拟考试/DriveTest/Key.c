#include "Key.h"
#include "Display.h"

//uchar value = 0;
uchar flag = 0;
uchar s7_tt = 0;
uchar s6_tt = 0;
uchar S7 = 0,S6 = 0,S5 = 0,S4 = 0;
void Key()
{
	if(P30 == 0)
	{
		Delay2ms();
		Delay2ms();
		if(P30 == 0)
		{
		  flag = 1;
		   while(!P30)
		   {
		   	 Delay50ms();
			 
			 if(++s7_tt >= 16)
			 {
			 	flag = 0;
				s7_tt = 0;
				yi = 1,er = 1,san = 1,si =1,wu = 1,liu = 1,qi=  1,ba = 1;
			 
			 }

		   }
		    if(flag == 1)
		   {
		   	yi = 2,er = 2,san = 2,si = 2,wu = 2,liu = 2,qi = 2,ba = 2;
		   	flag = 0;s7_tt = 0;
		   }
		}
		while(!P30);
	}
	else if(P31 == 0)
	{
		Delay2ms();
		if(P31 == 0)
		{
			flag = 1;
			while(!P31)
			{
				Delay50ms();
				if(++s6_tt >= 8)
				{
				 	do
				 	{	 
					 	 Delay50ms();
						 temp = temp + 1;
					
				 	}while(!P31);
					s6_tt = 0;
					flag = 0;
					Display1(yi,er);
					Display2(san,si);
					Display3(wu,liu);
					Display4(qi,ba);
				}
			}
	
			if(flag == 1)
			{
				temp = temp+1;
				flag = 0;
			}
		}
		while(!P31);
	}
	else if(P32 == 0)
	{
		Delay2ms();
		if(P32 == 0)
		{
		yi = 2;	
		}
		while(!P32);
	}
	else if(P33 == 0)
	{
		Delay2ms();
		if(P33 == 0)
		{
			S4 = 0;	
		}
		while(!P33);
	}  	
}
void Delay50ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 3;
	j = 26;
	k = 223;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

  	
//void Key16()
//{
//	P42 = 0; P44 = 0; P3 = 0x0f;
//
//	if(P3 != 0x0f)
//	{
//		Delay2ms();
//		if(P3 != 0x0f)
//		{
//			switch(P3)
//			{
//				case 0x0e:value = 1;break;
//				case 0x0d:value = 5;break;
//				case 0x0b:value = 9;break;
//				case 0x07:value = 13;break;
//			}
//
//			P42 = 1; P44 = 1; P3 = 0xf0;
//			if(P44 == 0)value += 0;while(P44 == 0);
//			if(P42 == 0)value += 1;while(P42 == 0);
//			if(P3 == 0xd0)value +=2;while(P3 == 0xd0);
//			if(P3 == 0xe0)value +=3;while(P3 == 0xe0);
//
//			 switch(value)
//			{
//				case 1:yi = 1;break;
//				case 2:yi = 2;break;
//				case 3:yi = 3;break;
//				case 4:yi = 4;break;
//				case 5:yi = 5;break;
//				case 6:yi = 6;break;
//				case 7:yi = 7;break;
//				case 8:yi = 8;break;
//				case 9:yi = 9;break;
//			}
//						
//		}
//	}
//
//}