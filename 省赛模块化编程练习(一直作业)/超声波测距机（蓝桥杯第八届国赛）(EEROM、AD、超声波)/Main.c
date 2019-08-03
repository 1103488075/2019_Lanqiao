#include "Hread.h"
#include "Display.h"
#include "ScanKey.h"
#include "iic.h"
#include "Wave.h"//ultrasonic  module

void InitAll();
void InitTimer0();  // 1ms enter into interrupt 
void InitTimer1();
uint value = 0;//read AD value
uint WaveValue = 0;
bit WaveFlag = 0; //wave sign
void main()
{
    InitAll();
    InitTimer0();
    InitTimer1();
  //  EEROPMWrite(0x00,23);
    while(1)
    {
        // yi = EEROPMRead(0x00)/10;
        // er = EEROPMRead(0x00)%10;

    //    value = GetAD(0x03);
    //   yi = value/100;er = value/10%10,san = value %10;

    if(WaveFlag == 1)//200ms update Wave
    {
        WaveFlag = 0;
        SendWave(); //send Wave
        TR1 = 1;//start timer1 
        while((RX == 1)&&(TF1 == 0))//over timer1
        {TR1 = 0;}

        if(TF1 == 1)
        {
            TF1 = 0;
            Distance = 9999	;
        }
        else
        {
            t = TH1;
            t <<= 8;
            t |= TL1;
            Distance = (uint)(t*0.017);//calculate distance
            Distance = Distance / 12;
        }
        TH1 = 0;
        TL1 = 0;
    }
    yi = Distance/100;
    er = Distance%100/10;
    san = Distance%10;
       Key();
       Display1(yi,er);
       Display2(san,si);
       Display3(wu,liu);
       Display4(qi,ba);
    }
    
}
void Timer0() interrupt 1
{
    if(++WaveValue >= 200)
    {
        WaveFlag = 1;
        WaveValue = 0;
    }
}
void InitAll()
{
    P2 = 0xa0; P0 = 0x00;
    P2 = 0x80; P0 = 0xff;
    P2 = 0xc0; P0 = 0xff;
    P2 = 0xff; P0 = 0xff;
}
void InitTimer0()
{
    AUXR |= 0x80;
    TMOD &= 0xf0;
    TL0  = 0xcd;
    TH0  = 0xd4;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;
    EA = 1;
}
void InitTimer1()
{
    AUXR |= 0x40;
    TMOD &= 0x0f;
}