#include "Sonic.h"
 
uchar t = 0;
uchar Distance = 0;

uchar ReadDistance()
{
	if(s_flag)
	{
		s_flag = 0;
		Send_wave();
		TR1 = 1;
		while((RX == 1)&&(TF1 == 0));
		TR1 = 0;

		if(TF1 == 1)
		{
			TF1 = 0;
			Distance = 99;
		}
		else 
		{
			t = TH1;
			t <<= 8;
			t |= TL1;
			Distance = (uint)(t*0.017);
			Distance = Distance/12;
		}
		TH1 = 0;
		TL1 = 0;

	}
	return Distance;
}

void Send_wave()
{
	uchar i ;
	do
	{
		TX = 1;
		somenop1;somenop1;somenop1;somenop1;somenop1;somenop1;somenop1;somenop1;somenop1;somenop1;
		TX = 0;
		somenop1;somenop1;somenop1;somenop1;somenop1;somenop1;somenop1;somenop1;somenop1;somenop1;
	}while(i--);
}