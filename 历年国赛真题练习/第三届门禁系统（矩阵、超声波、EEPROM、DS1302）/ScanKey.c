#include "Key.h"
#include "Display.h"

uchar value = 0;
uchar num = 0;
uchar Password = 0;
bit flag1 = 0,affirm = 0;
uchar flag2 = 0;
void Key16()
{
	 P42 = 0,P44 = 0, P3 = 0x0f;
	if(P3 != 0x0f)
	{
		Delay2ms();
		if(P3 != 0x0f)
		{
			 flag1 = 1;
			P42 = 1, P44 = 1,P3 = 0x30;
			if((P3 == 0x30)&&(P42 == 1)&&(P44 == 0))
			value = 0;
			else if((P3 == 0x30)&&(P42 == 0)&&(P44 == 1))
			value = 1;
			else if((P3 == 0x10)&&(P42 == 1)&&(P44 == 1))
			value = 2;
			else if((P3 == 0x20)&&(P42 == 1)&&(P44 == 1))
			value = 3;

			P42 = 0; P44 = 0; P3 = 0x0f;

			switch(P3)
			{
					case(0x0e):value += 0;break;
					case(0x0d):value += 4;break;
					case(0x0b):value += 8;break;
					case(0x07):value += 12;break;
			}

			switch(value)
			{
				case(0):Password = 0,num = 1;break;
				case(1):Password = 1,num = 1;break;
				case(2):Password = 2,num = 1;break;
				case(3):Password = 3,num = 1;break;
				case(4):Password = 4,num = 1;break;
				case(5):Password = 5,num = 1;break;
				case(6):Password = 6,num = 1;break;
				case(7):Password = 7,num = 1;break;
				case(8):Password = 8,num = 1;break;
				case(9):Password = 9,num = 1;break;
				case(10): flag2 = 1;break; //seting key
				case(11):yi = 1,er = 1;break; //return key
				case(14):yi = 1,er = 4;break; //affirm key
				case(15):yi = 1,er = 5;break; //closs key
			}

			  while(P3 != 0x0f);
		}
	}
}