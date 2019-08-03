/*
  程序说明: 单总线驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台
  日    期: 2011-8-9
*/

#include "onewire.h"

//单总线延时函数
void Delay_OneWire(unsigned int t)
{
  unsigned char i;
  while(t--)
  {
	  for(i = 0;i < 12;i++);
  }
}
//===============修改为1t单片机延时函数


//DS18B20芯片初始化
bit Init_DS18B20(void)
{
	bit initflag = 0;
	DQ = 1;
	Delay_OneWire(12);
	DQ = 0;
	Delay_OneWire(80); 
	DQ = 1;
	Delay_OneWire(10); 
	initflag = DQ;    
	Delay_OneWire(5);
  
	return initflag;
}

//通过单总线向DS18B20写一个字节
void Write_DS18B20(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delay_OneWire(5);
		DQ = 1;
		dat >>= 1;
	}
	Delay_OneWire(5);
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
		Delay_OneWire(5);
	}
	return dat;
}
//====================需记熟
 uchar Get_Ds18B20()
 {
	 uchar temp; 
	 uchar TH,TL;//high four and low four
	 Init_DS18B20();
	 Write_DS18B20(0xcc);//rom order
	 Write_DS18B20(0x44);//switch order
	 Delay_OneWire(400);

	 Init_DS18B20();
	 Write_DS18B20(0xcc); //rom order
	 Write_DS18B20(0xbe); //write order
	TL = Read_DS18B20(); //low four in before
	TH = Read_DS18B20();
	temp = (TH<<4)|(TL>>4);
	return temp;
 }
