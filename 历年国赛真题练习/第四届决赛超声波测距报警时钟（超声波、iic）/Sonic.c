#include "Sonic.h"
#include "Head.h" 
 
unsigned char Distance = 0;
uint t = 0;

unsigned char Read_Distance()
{
 
	if(s_flag)
	{
		s_flag = 0;
		send_wave();  //send sonic
		TR1 =  1;	 //start time
		while((RX == 1)&&(TF1 == 0));  //wait pulse
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
			Distance = (unsigned int)(t * 0.017);
			Distance = Distance /12;
		}
		TH1 = 0;
		TL1 = 0;
	}	
	return Distance;
}



void send_wave()
{
	uchar i = 8;
	do
	{
		TX = 1;
		somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;
		TX = 0;
		somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;

	}while(i--);

}