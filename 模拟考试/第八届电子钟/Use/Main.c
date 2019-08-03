#include "Head.h"
#include "Display.h"
#include "Key.h"
#include "ds1302.h"
#include "onewire.h"


void InitAll();

uchar temp;

char Timer[]={0,0,0,0};
void main()
{
 	InitAll();
 	Write_Time();
	while(1)
	{  
		Read_Time();

		 	// clock interface
		
		 if(S7 == 1)
		{
		   yi = Time[2]/10,er = Time[2]%10,san = 10,si = Time[1]/10,wu = Time[1]%10,liu = 10,qi = Time[0]/10,ba = Time[0]%10;
		}
		else if(S7 == 2)
		{
			if(Time[0]% 2 == 1)
			{yi = Time[2]/10,er = Time[2]%10,san = 10,si = Time[1]/10,wu = Time[1]%10,liu = 10,qi = Time[0]/10,ba = Time[0]%10;}
			else if(Time[0]% 2 == 0)
			{yi = 11,er = 11,san = 10,si = Time[1]/10,wu = Time[1]%10,liu = 10,qi = Time[0]/10,ba = Time[0]%10;}
		}
		else if(S7 == 3)
		{
			if(Time[0]%2 == 1)
			{yi = Time[2]/10,er = Time[2]%10,san = 10,si = Time[1]/10,wu = Time[1]%10,liu = 10,qi = Time[0]/10,ba = Time[0]%10;}
			else if(Time[0]%2 == 0)
			{yi = Time[2]/10,er = Time[2]%10,san = 10,si = 11,wu = 11,liu = 10,qi = Time[0]/10,ba = Time[0]%10;}
		}
		else if(S7 == 4)
		{
		  	 if(Time[0]%2 == 1)
			{yi = Time[2]/10,er = Time[2]%10,san = 10,si = Time[1]/10,wu = Time[1]%10,liu = 10,qi = Time[0]/10,ba = Time[0]%10;}
			else if(Time[0]%2 == 0)
			{yi = Time[2]/10,er = Time[2]%10,san = 10,si = Time[1]/10,wu = Time[1]%10,liu = 10,qi = 11,ba = 11;}			

		}


		  if(S6 == 1)
		{
			yi = Timer[2]/10,er = Timer[2]%10,san = 10,si = Timer[1]/10,wu = Timer[1]%10,liu = 10,qi = Timer[0]/10,ba = Timer[0]%10;
		}
		else if(S6 == 2)
		{
			if(Time[0]% 2 == 1)
			{yi = Timer[2]/10,er = Timer[2]%10,san = 10,si = Timer[1]/10,wu = Timer[1]%10,liu = 10,qi = Timer[0]/10,ba = Timer[0]%10;}
			else if(Time[0]% 2 == 0)
			{yi = 11,er = 11,san = 10,si = Timer[1]/10,wu = Timer[1]%10,liu = 10,qi = Timer[0]/10,ba = Timer[0]%10;}
		}
		else if(S6 == 3)
		{
			if(Time[0]%2 == 1)
			{yi = Timer[2]/10,er = Timer[2]%10,san = 10,si = Timer[1]/10,wu = Timer[1]%10,liu = 10,qi = Timer[0]/10,ba = Timer[0]%10;}
			else if(Time[0]%2 == 0)
			{yi = Timer[2]/10,er = Timer[2]%10,san = 10,si = 11,wu = 11,liu = 10,qi = Timer[0]/10,ba = Timer[0]%10;}
		}
		else if(S6 == 4)
		{
		  	 if(Time[0]%2 == 1)
			{yi = Timer[2]/10,er = Timer[2]%10,san = 10,si = Timer[1]/10,wu = Timer[1]%10,liu = 10,qi = Timer[0]/10,ba = Timer[0]%10;}
			else if(Time[0]%2 == 0)
			{yi = Timer[2]/10,er = Timer[2]%10,san = 10,si = Timer[1]/10,wu = Timer[1]%10,liu = 10,qi = 11,ba = 11;}			

		}
		if(Timer[2] > 23)
		{Timer[2] = 23;}
		else if(Timer[2] <= 0)
		{Timer[2] = 0;}

		else if(Timer[1] > 60)
		{Timer[1] = 59;}
		else if(Timer[1] <= 0)
		{Timer[1] = 0;}

		if(Timer[0] > 60)
		{Timer[0] = 59;}
		else if(Timer[0] <= 0)
		{Timer[0] = 0;}

//		if(Time[2] >= 23)
//		{Time[2] = 23;}
//		else if(Time[2] <= 0)
//		{Time[2] = 0;}
//		else if(Time[1] >= 60)
//		{Time[1] = 60;}
//		else if(Time[1] <= 0)
//		{Time[1] = 0;}
//		else if(Time[0] >= 60)
//		{Time[0] = 60;}
//		else if(Time[0] <= 0)
//		{Time[0] = 0;}

		Key();
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