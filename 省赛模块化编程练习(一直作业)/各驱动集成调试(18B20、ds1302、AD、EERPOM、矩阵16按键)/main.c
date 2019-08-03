#include "Hread.h"
#include "Display.h"
#include "Key16.h"
#include "onewire.h"
#include "ds1302.h"
#include "iic.h"
void InitAll();
uchar temperature = 0;
uint ADValue = 0;
uint iicvalue = 0;
void main()
{
    InitAll();
    WriteTime();
    EEPROMwrite(0x10,123);
    while(1)
    {

          temperature = Get18B20();
    //     ADValue = ReadAD(0x03);
        // yi = ADValue/100;er = ADValue%100/10;san = ADValue%100%10; 
        ReadTime();
    //    yi = shijian[2]/10;er = shijian[2]%10;
    //    si = shijian[1]/10;wu = shijian[1]%10;
   //     qi = shijian[0]/10;ba = shijian[0]%10;
       iicvalue = EEPROMread(0x10);
       yi = iicvalue/100;er = iicvalue%100/10;san = iicvalue%100%10;
        ScanKey16();
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