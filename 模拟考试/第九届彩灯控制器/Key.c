#include "Key.h"
#include "Display.h"
#include "iic.h"
 uchar S6 = 0,S5 = 0,S4 = 0;
 bit S7 = 0;
void Key()
{
   if(P30 == 0)
    {
        Delay2ms();
        if (P30 == 0)   
        {
       		if(S7 == 0)
			{S7 = 1;}
			else if(S7 == 1)
			{S7 = 0;}
        }
        while(!P30);
    }
    else if(P31 == 0)  
    {
        Delay2ms();
        if (P31 == 0)
        {
      		if(S6 == 0)
			{S6 = 1;}
			else if(S6 == 1)
			{S6 = 2;}
			else if(S6 == 2)
			{S6 = 0;yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = 11,ba = 11;
			Delay2ms();
			Write_EEPROM(0x00,mode);
			Delay2ms();	
			num = Interval/10;
			Write_EEPROM(0x01,num);	
			}
        }
        while(!P31);
    }
    else if(P32 == 0)
    {
        Delay2ms();
        if (P32 == 0)
        {
		 	 if(S6 == 1)
			 {
			 	mode = mode + 1;
			 	if(mode >= 4){mode = 4;}
			 }
			 else if(S6 == 2)
			 {
			 	Interval = Interval + 100;
				if(Interval >= 1200){Interval = 1200;}
			 }
		 
        }
        while(!P32);
    }
     if(P33 == 0 && S6 != 0) 
    {
        Delay2ms();
        if (P33 == 0&& S6 != 0)
        {
       	    if(S6 == 1)
			 {
			 	mode = mode - 1;
			 	if(mode <= 1){mode = 1;}
			 }
			 else if(S6 == 2)
			 {
			 	Interval = Interval - 100;
				if(Interval <= 400){Interval = 400;}
			 }
        }
        while(!P33);
    }
	else  if(S6 == 0 && P33 == 0)
	{
		if(P33 == 0 && S6 == 0)
		{
			Delay2ms() ;
			if(P33 == 0 && S6 == 0)
			{
			if(luminance<64){yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=10;ba=1;}
			else if((luminance>=64)&&(luminance<128)){yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=10;ba=2;}
			else if((luminance>=128)&&(luminance<192)){yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=10;ba=3;}
			else if((luminance>=192)&&(luminance<256)){yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=10;ba=4;}
			}
		}
	}
	 
}	










								  
 
	
 