#include "Key16.h"
#include "Display.h"

uchar KeyValue = 0;
void ScanKey16()
{
    P42 = 0;P44 = 0;//P42 = P36  P44 = P37
    P3 = 0x0f;//0000 1111
    if(P3 != 0x0f)
    {
        Delay2ms();
        if(P3 != 0x0f)//is scan list
        {
            P42 = 1; P44 = 1; P3 = 0x30;//1111 0000
            if((P3 == 0x30)&&(P44 == 0)&&(P42 == 1))//0111 0000
                KeyValue = 0;
            else if((P3 == 0x30)&&(P44 == 1)&&(P42 == 0))//1011 0000
                KeyValue = 1;
            else if((P3 == 0x10)&&(P44 == 1)&&(P42 == 1))//1101 0000
                KeyValue = 2;
            else if((P3 == 0x20)&&(P44 == 1)&&(P42 == 1))//1110 0000
                KeyValue = 3;
        }
        P42 = 0; P44 = 0; P3 = 0x0f;//0000 1111
        switch(P3)//is line scan
        {
            //case is 0000 1111
            case(0x0e):KeyValue+=0;break;
            case(0x0d):KeyValue+=4;break;
            case(0x0b):KeyValue+=8;break;
            case(0x07):KeyValue+=12;break;
        }
        switch (KeyValue)
        {
            case(0):yi = 0; break;
            case(1):yi = 1; break;
            case(2):yi = 2; break;
            case(3):yi = 3; break;
            case(4):yi = 4; break;
            case(5):yi = 5; break;
            case(6):yi = 6; break;
            case(7):yi = 7; break;
            case(8):yi = 8; break;
            case(9):yi = 9; break;
            case(10):yi = 1,er = 0; break;
            case(11):yi = 1,er = 1; break;
            case(12):yi = 1,er = 2; break;
            case(13):yi = 1,er = 3; break;
            case(14):yi = 1,er = 4; break;
        }
        while(P3 != 0x0f);
    }
    
}