#include "Hread.h"
#include "Display.h"
#include "Key16.h"
#include "ds1302.h"
#include "iic.h"
void InitAll();
 uchar value = 0;
 uchar pattern = 1;
 uchar i;
void main()
{
    InitAll();
   InitTime();
   //EEPROMWrite(0x00,19);
    while(1)
    {
        if(Seting == 0)
        {
            if(Pasworld == 1)
            {
                
                yi = 10,er = 10;
                san = InputPsworld[0],si =InputPsworld[1];
                wu =InputPsworld[2],liu =InputPsworld[3];
                qi = InputPsworld[4],ba = InputPsworld[5];
                    
            }
            else if(Pasworld == 0)
            {
                ReadTime();
                yi = Time[2]/10;er = Time[2]%10;san = 10;
                si = Time[1]/10;wu = Time[1]%10;liu = 10;
                qi = Time[0]/10;ba = Time[0]%10;
            }
        }
        else if(Seting == 1)
        {
            yi = 11,er = 10,san = 11,si = 11;
            wu = 11,liu = 11,qi = 11,ba = 11;
        }
         
        // value = EEPROMRead(0x00);
        // yi = value/10;er = value%10;
        // ReadTime();
        // yi = Time[2]/10;er = Time[2]%10;san = 10;
        // si = Time[1]/10;wu = Time[1]%10;liu = 10;
        // qi = Time[0]/10;ba = Time[0]%10;

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