//=======================Automation water

//#include "typedef.h"
#include "Display.h"
#include "ScanKey.h"
#include "Delay.h"
#include "Time.h"
#include "IIC.h"

void Init_All();


uint Cost = 0.5*10;//cost *10 split display
uint WaterGross = 1*10;//water gross * 10 split display
uint TotalPrice = 0.5*10;//total price s *10 split display
uchar ADvalue;
void main()
{

    yi = 11,er = 11, san = 11, si = 11, wu = 11, liu = 11, qi = 11, ba = 11, jiu = 11, shi = 11;
    Init_All();
    Init_Time0();
    while(1)
    {
		ADvalue = AD_Read(0x03);
		yi = ADvalue /100%10;er = ADvalue/10%10;	san = ADvalue%10;

	    ScanKey();
        Init_Time0();//time0 interrup tow ms once
        if(S7 == 1)//key control and nixietube display
        {
            	 

			yi = 11; er = Cost/10%10; san = Cost%10; si = 0;// display cost
			wu = WaterGross/100%10; liu = WaterGross/10%10; qi = WaterGross%10; ba = 0;   //display water gross //and total price s
			jiu = 12; shi = 12;		//decimal point display
            
            P2 = 0xa0; P0 = 0x10; //open relay
            P2 = 0x80; P0 = 0x7f;   //open led
        }
        if(S6 == 1)//diplay cost and total price s
        {
            S7 = 0;
            S6 = 0;
            P2 = 0xa0; P0 = 0x00;//close
            P2 = 0x80; P0 = 0xff;//close
            wu = TotalPrice/100%10; liu = TotalPrice/10%10; qi = TotalPrice%10; ba = 0; //display total price s
            shi = 12;   //  decimal poinit
        }
        if(WaterGross >= 999)//water gross greater than value
        {
            P2 = 0xa0; P0 = 0x00;//relay close
        }
        Display1(yi, er);
        Display2(san, si);
        Display3(wu, liu);
        Display4(qi, ba);
		Display5(jiu,shi);	//jiu,shi is decimal point 
    }
}

void Init_All()//all init
{
    P2 = 0x80; P0 = 0xff;//led
    P2 = 0xa0; P0 = 0x00;//buzz
    P2 = 0xc0; P0 = 0xff;//weixuan
    P2 = 0xff; P0 = 0xff;
}
