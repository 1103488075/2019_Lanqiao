/*
  程序说明: IIC总线驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台(12MHz)
  日    期: 2011-8-9
*/

#include "iic.h"

//总线启动条件
void IIC_Start(void)
{
	SDA = 1;
	SCL = 1;
	somenop;
	SDA = 0;
	somenop;
	SCL = 0;	
}

//总线停止条件
void IIC_Stop(void)
{
	SDA = 0;
	SCL = 1;
	somenop;
	SDA = 1;
}
//应答位控制
void IIC_Ack(unsigned char ackbit)
{
	if(ackbit) 
	{	
		SDA = 0;
	}
	else 
	{
		SDA = 1;
	}
	somenop;
	SCL = 1;
	somenop;
	SCL = 0;
	SDA = 1; 
	somenop;
}
//等待应答
bit IIC_WaitAck(void)
{
	SDA = 1;
	somenop;
	SCL = 1;
	somenop;
	if(SDA)    
	{   
		SCL = 0;
		IIC_Stop();
		return 0;
	}
	else  
	{ 
		SCL = 0;
		return 1;
	}
}
//通过I2C总线发送数据
void IIC_SendByte(unsigned char byt)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{   
		if(byt&0x80) 
		{	
			SDA = 1;
		}
		else 
		{
			SDA = 0;
		}
		somenop;
		SCL = 1;
		byt <<= 1;
		somenop;
		SCL = 0;
	}
}
//从I2C总线上接收数据
unsigned char IIC_RecByte(void)
{
	unsigned char da;
	unsigned char i;
	
	for(i=0;i<8;i++)
	{   
		SCL = 1;
		somenop;
		da <<= 1;
		if(SDA) 
		da |= 0x01;
		SCL = 0;
		somenop;
	}
	return da;
}



//====================以下需要自己写，务必熟记
unsigned char AD_Read(unsigned char add)//AD转换
{
	float temp;
	IIC_Start();
	IIC_SendByte(0x90);//发送寻址
	IIC_WaitAck();
	IIC_SendByte(add);//控制字节(0x03);
	IIC_WaitAck();
	IIC_Stop();
	//===========AD读取
	IIC_Start();
	IIC_SendByte(0x91);//读取位
	IIC_WaitAck();
	temp = IIC_RecByte();
	IIC_Stop();
	return temp;
}
void EEPROM_Write(unsigned char add,unsigned char dat)//写进AT24C02
{
	IIC_Start();
	IIC_SendByte(0xa0);//0xa0是写操作
	IIC_WaitAck();
	IIC_SendByte(add);//写进地址控制0x01
	IIC_WaitAck();
	IIC_SendByte(dat);//发送数据4
	IIC_WaitAck();
	IIC_Stop();
}
unsigned char  EEPROM_Read(unsigned char add)//读操作
{
	unsigned char temp;
	IIC_Start();
	IIC_SendByte(0xa0);//发送写操作地址a0写操作
	IIC_WaitAck();
	IIC_SendByte(add);//发送控制地址
	IIC_WaitAck();//等待答应
	IIC_Stop();

	IIC_Start();
	IIC_SendByte(0xa1);//a1读操作后调用IIC_recbyte
	IIC_WaitAck();
	temp = IIC_RecByte();
	IIC_Stop();
	return temp;
}