#include "Key.h"
#include "Display.h"
uchar KeyValue = 0;
bit shezhi,qingchu;
void ScanKey16()
{
    P42 = 0; P44 = 0;
    P3 = 0x0f;  //low four is seting one

    if(P3 != 0x0f)
    {
        Delay2ms();
        if(P3 != 0x0f)
        {
            P42 = 1, P44 = 1;   P3 = 0x30;
            //high fuor is Scan list 
            if((P3 == 0x30)&&(P44 == 0)&&(P42 == 1))
                KeyValue = 0;
            if((P3 == 0x30)&&(P44 == 1)&&(P42 == 0))
                KeyValue = 1;
            if((P3 == 0x10)&&(P44 == 1)&&(P42 == 1))
                KeyValue = 2;
            if((P3 == 0x20)&&(P44 == 1)&&(P42 == 1))
                KeyValue = 3;

            //========low four is line scan
            P42  = 0; P44 = 0; P3 = 0x0f;   //0000 1111
            switch(P3)
            {
                case (0x0e):KeyValue += 0;break;
                case (0x0d):KeyValue += 4;break;
                case (0x0b):KeyValue += 8;break;
                case (0x07):KeyValue +=12;break;
            }

            if(KeyValue == 13)//Go seting interface
            {  
                if(shezhi == 0){shezhi = 1;}
                else if(shezhi == 1){shezhi = 0; P2 = 0x80; P0 = 0xff; P2 = 0xa0; P0 = 0x00;}
            }   
                  switch (KeyValue)
                {
                    case  (0): yi = 0; break;
                    case  (1): yi = 1; break;
                    case  (2): yi = 2; break;
                    //case  (3): yi = 3; break;            
                    case  (4): yi = 4; break;
                    case  (5): yi = 5; break;
                    case  (6): yi = 6; break;
                   // case  (7): yi = 7; break;
                    case  (8): yi = 8; break;
                    case  (9): yi = 9; break;
                    case  (10): yi = 1,er = 0; break;
                   // case  (11): yi = 1,er = 1; break;
                    case  (12): yi = 1,er = 2; break;
					case  (13): yi = 1,er = 3; break;
					case  (14): yi = 1,er = 4; break;
					//case  (15): yi = 1,er = 5; break;
					//case  (16): yi = 1,er = 6; break;
                }
        
            while(P3 != 0x0f);
        }
		
    }
}