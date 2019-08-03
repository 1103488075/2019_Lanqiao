#include "Key.h"
#include "Display.h"
#include "iic.h"
uchar S7 = 0,S6 = 0,S5 = 0,S4 = 0;
void ScanKey()
{
    if(P30 == 0)
    {
        Delay2ms();
        if (P30 == 0)  //led start and over key
        {
            if(S7 == 0)
			{
			 S7 = 1;
			}
			else if(S7 == 1)
			{
			S7 = 0;
			}
        }
        while(!P30);
    }
    else if(P31 == 0) //led seting interval interface 
    {
        Delay2ms();
        if (P31 == 0)
        {
            if(S6 == 0)
			{
			S6 = 1;		 //pattern interface
			}
			else if(S6 == 1)
			{
			 S6 = 2;	 // interval interface
			}
			else if(S6 == 2)
			{
			 S6 = 0;
		
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
				if(S5 == 0)
				{
				Pattern = Pattern + 1;
				if(Pattern > 4)
				Pattern = 4;
				}
			}
			else if(S6 == 2)
			{
				if(S5 == 0)
				{
				interval = interval + 100; 
				if(interval > 1200)
				interval = 1200;
				}
			}
        }
        while(!P32);
    }
     if(P33 == 0 && S6 != 0)  //seting status	
    {
        Delay2ms();
        if (P33 == 0 && S6 != 0)
        {
           	if(S6 == 1)
			{    
				if(S4 == 0)
				{
				Pattern = Pattern - 1;
				if(Pattern <= 1)
				Pattern = 1;
				}
			}
			else if(S6 == 2)
			{
				if(S4 == 0)
				{
				interval = interval - 100; 
				if(interval <= 400)
				interval = 400;
				}
			}
        }
        while(!P33);
    }									  
	else if(S6 == 0 && P33 == 0)   //not seting status display luminance
	{	
		Delay2ms();
		if(S6 == 0 && P33 == 0)
		{
		
			if(AdValue<64){yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = 10,ba = 1;}
			else if((AdValue>=64)&&(AdValue<128)){yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = 11,ba = 2;}
			else if((AdValue>=128)&&(AdValue<192)){yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = 10,ba = 3;}
			else if((AdValue>=192)&&(AdValue<256)){yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = 10,ba = 4;}
		}
		
	}
}