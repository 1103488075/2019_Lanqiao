#include "ScanKey.h"
#include "Display.h"

uchar KeyValue = 0;
uint Value = 0;
uchar set = 0;
uchar number = 0,k = 0;
uchar num = 0;
bit a = 0;
void ScanKey16()
{
    P42 = 0; P44 = 0;
    P3 = 0x0f;  

    if(P3 != 0x0f)
    {
        Delay2ms();
        if(P3 != 0x0f)
        {
            P42 = 1, P44 = 1;   P3 = 0x30;
           
            if((P3 == 0x30)&&(P44 == 0)&&(P42 == 1))
                KeyValue = 0;
            else if((P3 == 0x30)&&(P44 == 1)&&(P42 == 0))
                KeyValue = 1;
            else if((P3 == 0x10)&&(P44 == 1)&&(P42 == 1))
                KeyValue = 2;
            else if((P3 == 0x20)&&(P44 == 1)&&(P42 == 1))
                KeyValue = 3;
			    
            P42  = 0; P44 = 0; P3 = 0x0f;    
            switch(P3)
            {
                case (0x0e):KeyValue += 0;break;
                case (0x0d):KeyValue += 4;break;
                case (0x0b):KeyValue += 8;break;
                case (0x07):KeyValue +=12;break;
            }
 				if(set == 1)
				{
                  switch (KeyValue)
	                {
	                    case  (0): Value = 0 ,num =1; break;
	                    case  (1): Value = 1 ,num = 1; break;
	                    case  (2): Value = 2,num = 1; break;
	                    //case  (3): yi = 3; break;            
	                    case  (4): Value = 3,num = 1; break;
	                    case  (5): Value = 4,num = 1; break;
	                    case  (6): Value = 5,num = 1; break;
	                   // case  (7): yi = 7; break;
	                    case  (8): Value = 6,num = 1; break;
	                    case  (9): Value = 7,num = 1; break;
	                    case  (10):Value = 8,num = 1; break;
	                    case  (11): Value = 9,num = 1; break;
	                    case  (14): a = ~a	; break;
					//	case  (14): yi = 1,er = 4; break;
				 
					}
				}
 
			 	
				if(KeyValue == 13)
				{
				 
					if(set == 0)
					{	set = 1;
					 yi = 10,er = 11 ,san = 11,si = 11,wu = 11,liu = 10,qi = 11,ba = 11;
					}
					else if(set == 1)
					set = 0;
				}
//				if(KeyValue == 14)
//				{
////					a = ~a;
////					if(a == 1)
////					{
//					TMIN = 0;
//					TMAX = 0;
////					yi = 10,er = TMAX/10 ,san = TMAX%10,si = 11,wu = 11;
////					liu = 10,qi = TMIN/10,ba = TMIN%10;
////					}
//				 
//				}
            while(P3 != 0x0f);
        }
		
    }
}

















