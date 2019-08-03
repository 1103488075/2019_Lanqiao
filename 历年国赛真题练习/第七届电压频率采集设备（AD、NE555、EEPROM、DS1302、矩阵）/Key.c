#include "Key.h"
#include "Display.h"
#include "ds1302.h"

uchar value = 0;
uchar S5 = 0,S4 = 0;
bit S7 = 0,S6 = 0;

void Key16()
{
	P42 = 0; P44 = 0; P3 = 0x0f;

	if(P3 != 0x0f)
	{
		Delay2ms();
		if(P3 != 0x0f)
		{
			
			P42 = 1; P44 = 1; P3 = 0x30;

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
				case(0): 	
				if(S7 == 0){S7 = 1;}else if(S7 == 1){S7 = 0;}break;
				case(4):
				if(S6 == 0){S6 = 1;}else if(S6 == 1){S6 = 0;};break;
				case(8):S5 = 4;break;

				case(12): //seting interface
					if(S7 == 1)
					{
						if(S4 == 0)
						{S4 = 1;}
						else if(S4 == 1)
						S4 = 2;
						else if(S4 == 2)
						S4 = 3;
						else if(S4 == 3)
						{S4 = 0;}
					}
					else if(S6 == 1)
					{
						if(S4 == 0)
						{S4 = 1;}
						else if(S4 == 1)
						S4 = 2;
						else if(S4 == 2)
						S4 = 1;	
					}
					
					
				;break;

				case(1):	//key ++
				if(S7 == 1)
				{
					if(S4 == 1)
					{
						Time[2]++;
						Write_Time(); 
					}
					else if(S4 == 2)
					{
						Time[1]++;
						Write_Time();
					 
					}
					else if(S4 == 3)
					{
					Time[0]++;
					Write_Time();
					}
				}
				else if(S6 == 1)
				{
					if(S4 == 1)
					{
						VMAX = VMAX + 5;	
					}
					else if(S4 == 2)
					{
						VMIN = VMIN + 5;
					}
				}
				;break;
							
				case(5):  //key --
				if(S7 == 1)
				{
					if(S4 == 1)
					{
						Time[2]--;
						Write_Time(); 
					}
					else if(S4 == 2)
					{
						Time[1]--;
						Write_Time();
					 
					}
					else if(S4 == 3)
					{
					Time[0]--;
					Write_Time();
					}
				}
				else if(S6 == 1)
				{
					if(S4 == 1)
					{
						VMAX = VMAX - 5;	
					}
					else if(S4 == 2)
					{
						VMIN = VMIN - 5;
					}
				};break;
//				case(9):key = 5;break;
//				case(13):key = 7;break;
			}
	 
		 	 
			 
			
			 while(P3 != 0x0f);
		}
	}
}