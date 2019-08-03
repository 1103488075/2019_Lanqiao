/*******************************************************************************  
* 文件名称：蓝桥杯单片机第六届省赛-温度记录器
* 实验目的：温度记录器 
* 程序说明：如需了解有关本程序配套视频讲解，及比赛经验分享\
*					 欢迎访问淘宝店铺网址：shop117015787.taobao.com
* 日期版本：2017-12/V1.0
*******************************************************************************/


#include<STC15F2K60S2.H>
#include "DEPUTY.H"
#include <intrins.h>

sbit SCK=P1^7;		
sbit SDA=P2^3;		
sbit RST = P1^3;   // DS1302复位	

sbit DQ = P1^4;  //单总线接口

unsigned char shijian[]={50,59,23,0,0,0,0};

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
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 	SCK=0;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 	RST=1;	
  _nop_(); _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); 
 	Write_Ds1302_Byte(address);	
 	Write_Ds1302_Byte((dat/10<<4)|(dat%10));	/////////////////////////////////////////////////	
 	RST=0; 
}

unsigned char Read_Ds1302 ( unsigned char address )
{
 	unsigned char i,temp=0x00,dat1,dat2;/////////////////////////////////////
 	RST=0;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 	SCK=0;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 	RST=1;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
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
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 	RST=0;
	SCK=0;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	SCK=1;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	SDA=0;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	SDA=1;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	
	dat1=temp/16;
	dat2=temp%16;
	temp=dat1*10+dat2;/////////////////////////////////////////////////////////////////
	
	return (temp);			
}

void DS_init(void)
{
	unsigned char i,add;
	add=0x80;
	Write_Ds1302(0x8e,0x00);
	for(i=0;i<7;i++)
	{
		Write_Ds1302(add,shijian[i]);
		add=add+2;
	}
	Write_Ds1302(0x8e,0x80);
}


void DS_get(void)
{
	unsigned char i,add;
	add=0x81;
	Write_Ds1302(0x8e,0x00);
	for(i=0;i<7;i++)
	{
		shijian[i]=Read_Ds1302(add);
		add=add+2;
	}
	Write_Ds1302(0x8e,0x80);
}

/**************************************DS18B20驱动***********************************************************/

//单总线延时函数
void Delay_OneWire(unsigned int t)  
{
	while(t--);
}

//通过单总线向DS18B20写一个字节
void Write_DS18B20(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delay_OneWire(50);
		DQ = 1;
		dat >>= 1;
	}
	Delay_OneWire(50);
}

//从DS18B20读取一个字节
unsigned char Read_DS18B20(void)
{
	unsigned char i;
	unsigned char dat;
  
	for(i=0;i<8;i++)
	{
		DQ = 0;
		dat >>= 1;
		DQ = 1;
		if(DQ)
		{
			dat |= 0x80;
		}	    
		Delay_OneWire(50);
	}
	return dat;
}

//DS18B20设备初始化
bit init_ds18b20(void)
{
  	bit initflag = 0;
  	
  	DQ = 1;
  	Delay_OneWire(120);
  	DQ = 0;
  	Delay_OneWire(800);
  	DQ = 1;
  	Delay_OneWire(100); 
    initflag = DQ;     
  	Delay_OneWire(50);
  
  	return initflag;
}

unsigned char Tempget(void)
{
	unsigned char low,high,temp;
	init_ds18b20();
	Write_DS18B20(0XCC);
	Write_DS18B20(0X44);
	Delay_OneWire(200); 
	
	init_ds18b20();
	Write_DS18B20(0XCC);
	Write_DS18B20(0XBE);

	low=Read_DS18B20();
	high=Read_DS18B20();
	
	temp=high<<4;
	temp|=(low>>4);
	
	return temp;
}










