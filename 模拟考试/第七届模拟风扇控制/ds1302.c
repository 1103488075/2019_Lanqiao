/*
  程序说明: DS1302驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台 8051，12MHz
  日    期: 2011-8-9
*/

#include "ds1302.h"

sbit SCK=P1^7;		
sbit SDA=P2^3;		
sbit RST = P1^3;   // DS1302复位

uchar Time[]={50,50,23,0,0,0,0};												

void Write_Ds1302_Byte(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		SDA=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

void Write_Ds1302( unsigned char address,unsigned char dat )     
{
 	RST=0;
	_nop_();
 	SCK=0;
	_nop_();
 	RST=1;	
   	_nop_();  
 	Write_Ds1302_Byte(address);	
 	Write_Ds1302_Byte((dat%10<<4)|(dat/10));		
 	RST=0; 
}

unsigned char Read_Ds1302 ( unsigned char address )
{
 	unsigned char i,temp=0x00;
	uchar dat1,dat2;
 	RST=0;
	_nop_();
 	SCK=0;
	_nop_();
 	RST=1;
	_nop_();
 	Write_Ds1302_Byte(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;
	_nop_();
 	RST=0;
	SCK=0;
	_nop_();
	SCK=1;
	_nop_();
	SDA=0;
	_nop_();
	SDA=1;
	_nop_();
	dat1 = temp/16;
	dat2 = temp%16;
	temp = dat1*10+dat2;
	return (temp);			
}
void Write_Time()
{
	uchar temp = 0x80;
	uchar i;
	Write_Ds1302(0x8e,0x00)	;
	for(i = 0; i< 7; i++)
	{
		  Write_Ds1302(temp,Time[i]);
		  temp = temp+2;
	}
	Write_Ds1302(0x8e,0x80);
}
void Read_Time()
{
	uchar temp = 0x81;
	uchar i;
	Write_Ds1302(0x8e,0x00);
	for(i = 0; i< 7; i++)
	{
		  Time[i] = Read_Ds1302(temp);
		  temp = temp+2;
	}
	Write_Ds1302(0x8e,0x80);
}





