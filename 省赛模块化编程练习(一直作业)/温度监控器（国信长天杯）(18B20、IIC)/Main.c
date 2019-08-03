//monitoring temperatrue

#include "Hread.h"
#include "Display.h"
#include "Scan_Key.h"
#include "onewire.h"
#include "iic.h"

void All_Init();
void Time0Init();
 

uchar temp;
char Max = 0,Min = 0;
uint tt;
void main()
{
   	 All_Init();
    Time0Init();
	yi = 11,er = 11,san = 11,si = 11;
    wu = 11,liu = 11,qi = 11,ba = 11;
    
    Max = EEPROM_Read(0x00);
	 
        Min = EEPROM_Read(0x01);
    while(1)
    {
       EEPROM_Write(0x00,Max);
	Delay2ms();
	EEPROM_Write(0x01,Min);
        temp = Get18B20();
        yi = Max/10,er = Max%10,san = Min/10,si = Min%10;
        wu = 11,liu = 11,qi = temp/10,ba = temp%10;
       
        if(temp > Max)
        {
            ET0 = 1;EA = 1;
        }
        else if(temp < Min)//open relay
        {
            P2 = 0xa0; P0 = 0x10;
        }
        

        if(Min <= 0)//section 0-99
        {Min = 0;}
        else if(Min >= 99)
        { Min = 99;}

         if(Max <= 0)
        { Max = 0;}
         else if(Max >= 99)
        { Max = 99;}

        if(Min > Max)//not allow Min > Max
        {
            Min = 0;
        }
       // else
       // {
            Scan_Key();  
        //}   
        Display1(yi,er);
        Display2(san,si);
        Display3(wu,liu);
        Display4(qi,ba);
    }
}
void Time0()    interrupt 1
{
    tt++;
    if(tt >= 200)//1 ms
    {
        tt = 0;
        P34 = 0;//PWM
    }
    if(tt < 60)
        P34 = 1;
    else
        P34 = 0;
}
void All_Init()
{
    P2 = 0xa0; P0 = 0x00;
    P2 = 0x80; P0 = 0xff;
    P2 = 0xc0; P0 = 0xff;
    P2 = 0xff; P0 = 0xff;
}
void Time0Init()
{
    AUXR |= 0x80;
    TMOD &= 0xf0;
    TL0 = 0xc9;
    TH0 = 0xff;
    TR0 = 1;
    TF0 = 0;
}
 



