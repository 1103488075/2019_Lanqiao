//capacity transfer
#include "Hread.h"
#include "Display.h"
#include "Scan_Key.h"
#include "iic.h"

void Timer0_Init();
void All_Init();//tow ms interrupt

uint Ad_Value = 0;
uint iic_value;
uint timer_value;//timer0 value
uint timer_i;
uchar flag = 0;
uint iic_ad;


void main()
{
    All_Init();
    Timer0_Init();
	yi = 11,er = 11,san = 11,si = 11;
    wu = 11,liu = 11,qi = 11,ba = 11;
    iic_ad = 0x00;
    //EEPROM_Write(0x10, 23);
    Delay2ms();
    while(1)
    {
         Ad_Value = 3.92* AD_Read(0x03);
         liu = Ad_Value /100;
         qi = Ad_Value /10%10;
         ba = Ad_Value % 10;
        // iic_value =  EEPROM_Read(0x10);
        // Delay2ms();
        // yi = iic_value /10%10;
        // er = iic_value %10;
        if(Ad_Value >= 750)//overweight.closs timer and relay and buzz
        {
            ET0 = 0; EA = 0;      
            P2 = 0xa0; P0 = 0x00; 
            P2 = 0x80; P0 = 0xff;
            EEPROM_Write(iic_ad,Ad_Value);//save after overweight
            iic_ad = iic_ad + 1;
        }
        else if(Ad_Value < 750)
        {
       
            if(S4 == 1)//transfer start
            {
                P2 = 0xa0; P0 = 0x10; //open relay
                flag = 0;
            }
            if(S7 == 1)//transfer over
            {
                S4 = 0;
                P2 = 0xa0; P0 = 0x00;//closs relay
                ET0 = 0; EA = 0;//over timer
                P2 = 0x80; P0 = 0xff;//over LED 
                S7 = 0; //rest S7
        
                S5 = 0;//over front transfer
                S6 = 0;//over

            }
            if(S5 == 1 && S4 == 1)//front transfer
            {
                ET0 = 1;    EA = 1;      
            }
            if(S6 == 1 && S4 == 1)// reverse transfer
            {
                ET0 = 1;   EA = 1;
            }
        }

        Scan_Key();
        Display1(yi,er);
        Display2(san,si);
        Display3(wu,liu);
        Display4(qi,ba);
    }
}
void All_Init()
{
    P2 = 0xa0; P0 = 0x00;
    P2 = 0x80; P0 = 0xff;
    P2 = 0xc0; P0 = 0xff;
    P2 = 0xff; P0 = 0xff;
}
void Timer0_Init()//tow ms interrupt
{
    AUXR |= 0x80;
    TMOD &= 0xf0;
    TL0 = 0x9a;
    TH0 = 0xa9;
    TF0 = 0;
    TR0 = 1;
}
void Timer0()    interrupt 1
{
    timer_value++;
 
    if(timer_value >= 100)//tow hundred ms
    {
        timer_value = 0;
        if(S5 == 1)     //front transfer
        {
            P2 = 0x80; P0 = 0xfe;
            P0 = _crol_(P0,timer_i);
            timer_i++;
            if(timer_i >= 8)  timer_i = 0;
            if(P0 == 0xff)   P0 = 0xfe;
        }
        else if(S6 == 1)     //reverse transfer 
        {
            P2 = 0x80; P0 = 0x7f;
            P0 = _cror_(P0, timer_i);
            timer_i++;
            if(timer_i >= 8)    timer_i = 0;
            if(P0 == 0xff)     P0 = 0x7f;
        }
      
    }
  
 

}



