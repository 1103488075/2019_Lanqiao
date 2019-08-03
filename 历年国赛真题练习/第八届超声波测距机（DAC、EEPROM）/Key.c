#include "Key.h"

void Key16()
{
	P42 = 0; P44 = 0; P3 = 0x0f;
	if(P3 != 0x0f)
	{
		Delay2ms();
		if(P3 != 0x0f)
		{
			

			switch(P3)
			{
				case 0x0e:value = 1;break;
				case 0x0d:value = 5;break;
				case 0x0b:value = 9;break;
				case 0x07:value = 13;break;
			}

			P42 = 1; P44 = 1; P3 = 0xf0;

			if(P44 == 0)value +=0;while(P44 == 0);
			if(P42 == 0)value +=1;while(P42 == 0);
			if(P3 == 0xd0)value +=2while(P3 == 0xd0);
			if(P3 == 0xe0)value +=3;while(P3 == 0xe0);

		}
	}
}