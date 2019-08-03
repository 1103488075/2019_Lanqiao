#include"STC15F2K60S2.h"
#include"allinit.h"
#include"smg.h"
#include"ds1302.c"

#define uchar unsigned char
#define uint unsigned int

void main(void)
{
	uchar i,j,k;
	allinit();
	smg_Timerinit();
	DS1302_Init(); 
	while(1)
	{
		dspbuff[2]=17;
		dspbuff[5]=17;
		i=Ds1302_Single_Byte_Read(ds1302_hr_addr);
		dspbuff[0]=i/16;
		dspbuff[1]=i%16;
		j=Ds1302_Single_Byte_Read(ds1302_min_addr);
		dspbuff[3]=j/16;
		dspbuff[4]=j%16;
		k=Ds1302_Single_Byte_Read(ds1302_sec_addr);
		dspbuff[6]=k/16;
		dspbuff[7]=k%16;
	}
	
}