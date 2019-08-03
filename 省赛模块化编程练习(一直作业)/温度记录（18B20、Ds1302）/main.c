#include "Hread.h"
#include "Display.h"
#include "Key.h"
#include "onewire.h"
#include "ds1302.h"

void InitAll();
void InitTime();

uint tt;
bit LED_shan,fla;
uchar Save[10],Save_n = 0;
uchar wendu = 0;//gather temperature
void main()
{
    InitAll();
    WriteTime();
    InitTime();
    while(1)
    {
        wendu = Get_18B20();
       if(Cai_Start == 0)//perameter setting interface
       {
        yi = 11,er = 11,san = 11,si = 11,wu = 11;
        liu = 10,qi = Timec/10,ba = Timec%10;
       }
       else if(Cai_Start == 1)  //time display interface
       {
	   	    ReadTime(); //get time the array
           yi = InitDs[2]/10,er = InitDs[2]%10,san = 10;
           si = InitDs[1]/10,wu = InitDs[1]%10,liu = 10;
           qi = InitDs[0]/10,ba = InitDs[0]%10;

            if(InitDs[0]%2 == 0){san = 10,liu = 10;}//‘-’flicker function
            else {san = 11;liu = 11;}
           
       }
        ScanKey();
        Display1(yi,er);
        Display2(san,si);
        Display3(wu,liu);
        Display4(qi,ba);
    }
}
void InitAll()
{
    P2 = 0xa0; P0 = 0x00;
    P2 = 0x80; P0 = 0xff;
    P2 = 0xc0; P0 = 0xff;
    P2 = 0xff; P0 = 0xff;
}
void InitTime()
{
    AUXR |= 0x80;
    TMOD &= 0xf0;
    TL0 = 0x00;
    TH0 = 0x28;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;
    EA = 1;
}
void Time0() interrupt 1
{
    tt++;
 
    if((Cai_Start == 1)&&(tt >= Timec* 200))//allow gather
    {
        tt = 0;
        Save[Save_n] = wendu;
        Save_n++;
        if(Save_n >= 10) //gather accomplish. return allow gather
        {
            Save_n = 0;//reset array
            LED_shan = 1;   //LED slicker
            Cai_Start = 2;
            yi = 10,er = 0,san = 0,si = 11,wu =11;
            liu = 10, qi = Save[0]/10,ba = Save[0]%10;
        }
    }
    if((Cai_Start == 2) && (tt ==200))//gather accomplish interface
    {
        tt = 0;
        if(LED_shan == 1)//  LED fliker
        {
            if(fla == 0){fla = 1;P2 = 0x80; P0 = 0xfe;}
            else if(fla == 1){fla = 0;P2 = 0x80; P0 = 0xff;}
        }
        else if(LED_shan == 0)//S6.LED closs and display temperature
        {
            yi = 10,er = Save_n/10,san = Save_n%10;
            si = 11,wu = 11,liu = 10;
            qi = Save[Save_n]/10,ba = Save[Save_n]%10;
            Save_n++;
            if(Save_n >= 10)
            {
                Save_n = 0;
                Cai_Start = 3;
            }
        }
    }
}