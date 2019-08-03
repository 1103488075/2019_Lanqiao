#include "Sonic.h"

			  		
		
uint t = 0;
unsigned int SonicValue = 0;

unsigned int Read_Distance()
{
	
 	if(s_flag)
	{
		s_flag = 0;
		Send_Wave();
		TR1 = 1;
		while((RX ==1)&&(TF1 == 0));
		TR1 = 0;

		if(TF1 == 1)
		{
			TF1 = 0;
		   SonicValue = 999;
		}
		else 
		{
			t = TH1;
			t <<= 8;
			t |= TL1;
			SonicValue = (unsigned int)(t*0.017);
			SonicValue = SonicValue/12;
		}
		TH1 = 0;
		TL1 = 0;
	}
	return SonicValue;
}

void Send_Wave()
{
	  uchar i = 8;
	  do
	  {
	  	TX = 1;
		somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;
		TX = 0;
		somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;
	  }while(i--);

}