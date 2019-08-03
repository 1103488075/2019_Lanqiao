
#include "Hread.h"
#include "ds1302.h"
#include "Display.h"
#include "Key.h"
#include "onewire.h"

void Init_All();//init function
uchar temperature = 0;  //resolve temperature
uchar Alarm_clock[3]={0,0,0};
void main()
{
    Init_All();	   
    Init_Time();//from Time[] array init Ds1302
     
    while(1)
    {      
        Get_Time(); 		//get time to array
     
        if(wendu == 0)
        {
        if(S7 == 0)
        {
            yi = Time[2]/10; er = Time[2]%10;//get huor
            san = 10;  
            si = Time[1]/10; wu = Time[1]%10; //get minute
            liu = 10;
            qi = Time[0] /10; ba = Time[0] % 10	;//get second
        }
        else if(S7 == 1)
        {
            if(Time[0]%2 == 0)
            {
                yi = Time[2]/10;er = Time[2]%10;san = 10;si = Time[1]/10;
                wu = Time[1]%10;liu = 10;qi = Time[0]/10;ba = Time[0]%10;
            }
            else
            {
                yi = 11;er = 11;san = 10;si = Time[1]/10;
                wu = Time[1]%10;liu = 10;qi = Time[0]/10;ba = Time[0]%10;
            }
        }
        else if(S7 == 2)
        {
            if(Time[0]%2 == 0)
            {
                yi = Time[2]/10;er = Time[2]%10;san = 10;si = Time[1]/10;
                wu = Time[1]%10;liu = 10;qi = Time[0]/10;ba = Time[0]%10;
            }
            else
            {
                yi = Time[2]/10;er = Time[2]%10;san = 10;si = 11;
                wu = 11;liu = 10;qi = Time[0]/10;ba = Time[0]%10;
            }
        }
         else if(S7 == 3)
        {
            if(Time[0]%2 == 0)
            {
                yi = Time[2]/10;er = Time[2]%10;san = 10;si = Time[1]/10;
                wu = Time[1]%10;liu = 10;qi = Time[0]/10;ba = Time[0]%10;
            }
            else
            {
                yi = Time[2]/10;er = Time[2]%10;san = 10;si = Time[1]/10;
                wu = Time[1]%10;liu = 10;qi = 11;ba = 11;
            }
        }
        }
        else if(wendu == 1)
        {
            yi = 11,er = 11, san = 11, si = 11, wu = 11, liu = Get_Ds18B20()/10;qi = Get_Ds18B20()%10;ba = 10;
        }




        Scan_Key(); 	//input key function
        Display1(yi, er);  //display
        Display2(san, si);
        Display3(wu, liu);
        Display4(qi, ba);
    }
}
void Init_All()
{
    P2 = 0xa0; P0 = 0x00;
    P2 = 0x80; P0 = 0xff;
    P2 = 0xc0; P0 = 0xff;
    P2 = 0xff; P0 = 0xff; 
}


