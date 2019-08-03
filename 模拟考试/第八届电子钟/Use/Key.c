#include "Key.h"
#include "Display.h"
#include "ds1302.h"


uchar S7 = 0,S6 = 0,S5 = 0,S4 = 0;
void Key()
{
	if(P30 == 0)
	{
		Delay2ms() ;
		if(P30 == 0)
		{
			if(S7 == 0){S7 = 1;}
			else if(S7 == 1){S7 = 2;}
			else if(S7 == 2){S7 = 3;}
			else if(S7 == 3){S7 = 4;}
			else if(S7 == 4){S7 = 1;}
	
		}
		while(!P30);
	}
	else if(P31 == 0)
	{
		Delay2ms();
		if(P31 == 0)
		{
			if(S6 == 0){S6 = 1;}
			else if(S6 == 1){S6 = 2;}
			else if(S6 == 2){S6 = 3;}
			else if(S6 == 3){S6 = 4;}
			else if(S6 == 4){S6 = 0;S7 = 1;}
		}
		while(!P31);
	}
	else if(P32 == 0)
	{
		Delay2ms();
		if(P32 == 0)
		{
			if(S7 == 2)
			{
				Time[2]++;
				if(Time[2] >= 23)
				Time[2] = 23;
				Write_Time();
			}
			else if(S7 == 3)
			{	
				Time[1]++;
				if(Time[1] >= 60)
				Time[1] = 59;
				Write_Time();
			}
			else if(S7 == 4)
			{
				Time[0]++;
				if(Time[0] >= 60)
				Time[0] = 59;
				Write_Time();
			}  

			if(S6 == 2)
	 		{Timer[2]++;}
			else if(S6 == 3)
			{Timer[1]++;}
			else if(S6 == 4)
			{Timer[0]++;}
		}
		while(!P32);
	}
	else if(P33 == 0)
	{
		Delay2ms();
		if(P33 == 0)
		{
			if(S7 == 2)
			{
				Time[2]--;
				if(Time[2]<=0)
				Time[2] = 0;
				Write_Time();
			}
			else if(S7 == 3)
			{
			Time[1]--;
			if(Time[1]<=0)
			Time[1] = 0;
			Write_Time();
			}
			else if(S7 == 4)
			{
			Time[0]--;
			if(Time[0]<=0)
			Time[0] = 0;
			Write_Time();
			}  

			if(S6 == 2)
	 		{Timer[2]--;}
			else if(S6 == 3)
			{Timer[1]--;}
			else if(S6 == 4)
			{Timer[0]--;}
		}
		while(!P33);
	}

	
}
