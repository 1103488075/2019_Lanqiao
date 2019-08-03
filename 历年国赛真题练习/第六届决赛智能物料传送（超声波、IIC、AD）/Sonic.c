#include  "Sonic.h"

unsigned int t = 0;
uint Distance = 0;


uint ReadDistance()
{
	 if(s_flag)	  //200ms update data
	 {
		s_flag = 0;
		send_wave();  //send sonic
		TR1 = 1;	//open counter
		while((RX == 1)&&(TF1 == 0));
		TR1 = 0;   //close counter

		if(TF1 == 1) //happen overflow
		{
			TF1 = 0;
			Distance = 99;//not retrun 
		}
		else 
		{
			t = TH1;
			t <<= 8;
			t |= TL1;
			Distance = (unsigned int)(t * 0.017) ;
			Distance = Distance / 12;
		}
		TH1 = 0;
		TL1 = 0;
	 }
	return Distance;
}

void send_wave(void)
{
	uchar i = 8;
	do
	{
		TX =  1;
		somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;
		TX = 0;
		somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;somenop2;

	}while(i--);

}
//void Timer1Init()
//{
//	AUXR |= 0x40;
//	TMOD &= 0x0f;
//}
