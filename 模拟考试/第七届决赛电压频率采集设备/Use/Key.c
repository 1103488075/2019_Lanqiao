#include "Key.h"
#include "Display.h"
#include "ds1302.h"
#include "iic.h"
uchar value = 0;
uchar S5 = 0,S4 = 0; 
bit S7 = 0,S6 = 0,S9 = 0;
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
			   P3 = 0xf0; P42 = 1; P44 = 1;

			   if(P44 == 0)value += 0;while(P44 == 0);
			   if(P42 == 0)value += 1;while(P42 == 0);
			   if(P3 == 0xd0)value += 2;while(P3 == 0xd0);
			   if(P3 == 0xe0)value += 3;while(P3 == 0xe0);
 
			 
				 switch(value)
				 {
				  
					case(1): if(S7 == 0)S7 = 1; else if(S7 == 1)S7 = 0;break;	//S7 	Time display
					case(5): if(S6 == 0){S6 = 1;S7 = 0;} else if(S6 == 1){S6 = 0;EEPROM_Write(0x00,MAX);Delay2ms();EEPROM_Write(0x01,MIN);Delay2ms();}break; // S6	voltage display
					case(9): if(S5 == 0){S5 = 1;S6 = 0;} else if(S5 == 1) S5 = 0;break;	//S5 Khz
					case(13):if(S7 == 1)  //S4 time seting
							 {
								if(S4 == 0)
								S4 = 1;
								else if(S4 == 1)
								S4 = 2;
								else if(S4 == 2)
								S4 = 3;
								else if(S4 == 3)
								S4 = 0;
							 }
							 else if(S6 == 1)//voltage
							 {
							 	if(S4 == 0)
								S4 = 1;
								else if(S4 == 1)
								S4 = 2;
								else if(S4 == 2)
								S4 = 0;
							 }
							 else if(S5 == 1)
							 {
							 	if(S4 == 0)
								S4 = 1;
								else if(S4 == 1)
								S4 = 0;
							 }
							 else if(S9 == 1)
							 {
							 	if(S4 == 0)
								S4 = 1;
								else if(S4 == 1)
								S4 = 0;
							 };break;


				 	 	case(2):if(S7 == 1)//seting +++
								{
									if(S4 == 1)
									{Time[2]++;	if(Time[2] > 23)	Time[2] = 23;	Write_Time();}
									else if(S4 == 2)
									{Time[1]++;	if(Time[1] >= 59)	Time[1] = 59;	Write_Time();}
									else if(S4 == 3)
									{Time[0]++;	if(Time[0] >= 59)	Time[0] = 59;	Write_Time();}
								}
								else if(S6 == 1) //voltage interface
								{
									if(S4 == 1)
									{MAX = MAX +5;	if(MAX > 20)	MAX = 20;}
									else if(S4 == 2)
									{MIN = MIN +5;	if(MIN > 20)	MIN = 20;}
								 }
								;break;
						case(6):if(S7 == 1)	//seting --
								{
									if(S4 == 1)
									{Time[2]--;	if(Time[2] <= 0)	Time[2] = 0;	Write_Time();}
									else if(S4 == 2)
									{Time[1]--;	if(Time[1] <= 0)	Time[1] = 0;	Write_Time();}
									else if(S4 == 3)
									{Time[0]--;	if(Time[0] <= 0)	Time[0] = 0;	Write_Time();}
								}
								else if(S6 == 1)  //voltage interface
								{
									if(S4 == 1)
									{MAX = MAX - 5;	if(MAX < 0)	MAX = 0;}
									else if(S4 == 2)
									{MIN = MIN - 5;	if(MIN < 0)	MIN = 0;}
								 };break; 
						case(10):if(S9 == 1){S9 = 0;S5 = 0;} else if(S9 == 0)	S9 = 1;
						
						;break;
						case(14): yi = 7;break;
				 }
			}
	   }
}
 






