#include "Key.h"
#include "Display.h"
 

uchar S7 = 0,S6 = 0,S5 = 0,S4 = 0;

void Key()
{
	if(P30 == 0)
	{
		Delay2ms() ;
		if(P30 == 0)
		{
 			if(S7 == 0)
			{
				S7 = 1;
			}
			else if(S7 == 1)
			{S7 = 0;}
		}
		while(!P30);
	}
	else if(P31 == 0)
	{
		Delay2ms();
		if(P31 == 0)
		{
	 	   	ET1 = 0;
			ET0 = 0;
			JobTime = 0;
			P2 = 0x80; P0 = 0xff;
		}
		while(!P31);
	}
	else if(P32 == 0)
	{
		Delay2ms();
		if(P32 == 0)
		{
	 	   if(S5 == 0)
		   {S5 = 1;JobTime = 60;ET0 = 1;ET1 = 1;EA = 1;}
		   else if(S5 == 1)
		   {S5 = 2; JobTime = 120;}
		   else if(S5 == 2)
		   {S5 = 0; JobTime = 0;}
	 
		}
		while(!P32);
	}
	else if(P33 == 0)
	{
		Delay2ms();
		if(P33 == 0)
		{
		 	if(S4 == 0)
			{S4 = 1;PWM = 20;}
			else if(S4 ==1 )
			{S4 = 2;PWM = 30;}
			else if(S4 == 2)
			{S4 = 0;PWM = 70;}
		 

		}
		while(!P33);
	}

	
}
//uchar value = 0;
//
//void Key16()
//{
//	P42 = 0, P44 = 0, P3 = 0x0f;
//
//	if(P3 != 0x0f)
//	{
//		Delay2ms();
//		if(P3 != 0x0f)
//		{
//			 P42 = 1, P44 = 1, P3 = 0x30;
//
//			 if((P3 == 0x30)&&(P42 == 1)&&(P44 == 0))
//			 value = 0;
//			 if((P3 == 0x30)&&(P42 == 0)&&(P44 == 1))
//			 value = 1;
//			 if((P3 == 0x10)&&(P42 == 1)&&(P44 == 1))
//			 value = 2;
//			 if((P3 == 0x20)&&(P42 == 1)&&(P44 == 1))
//			 value = 3;
//
//			 P42 = 0, P44 = 0, P3 = 0x0f;
//
//			 switch(P3)
//			 {
//			 	case(0x0e):value += 0;break;
//			 	case(0x0d):value += 4;break;
//			 	case(0x0b):value += 8;break;
//			 	case(0x07):value += 12;break;
//			 }
//
//			 switch(value)
//			 {
//			 	case(0):yi = 0;break;
//			 	case(1):yi = 1;break;
//			 	case(2):yi = 2;break;
//			 	case(3):yi = 3;break;
//			 	case(4):yi = 4;break;
//			 	case(5):yi = 5;break;
//			 	case(6):yi = 6;break;
//			 	case(7):yi = 7;break;	
//				case(8):yi = 8;break;
//			 	case(9):yi = 9;break;
//			  
//			 }
//
//
//			 while(P3 != 0x0f);
//		}
//	}
//}

