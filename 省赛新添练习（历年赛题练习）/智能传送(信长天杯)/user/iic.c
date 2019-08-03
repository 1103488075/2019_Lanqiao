 

#include "iic.h"

//iic start
void IIC_Start(void)
{
	SDA = 1;
	SCL = 1;
	somenop;
	SDA = 0;
	somenop;
	SCL = 0;	
}

//iic stop
void IIC_Stop(void)
{
	SDA = 0;
	SCL = 1;
	somenop;
	SDA = 1;
}
//answer control
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
//wait answer
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
//pass iic send data
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
//from iic receptions date
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
 uchar AD_Read(uchar add)//read AD value
 {
	 	uchar temp;
		IIC_Start();
		IIC_SendByte(0x90);//write adress
		IIC_WaitAck();
		IIC_SendByte(add);//write RB2 adress is 0x03
		IIC_WaitAck();
		IIC_Stop();

		IIC_Start();
		IIC_SendByte(0x91);
		IIC_WaitAck();
		temp = IIC_RecByte();
 
		IIC_Stop();
		return  temp; 
}
void EEPROM_Write(uchar add, uchar dat)
{
	IIC_Start();
	IIC_SendByte(0xa0);//write operation
	IIC_WaitAck();
	IIC_SendByte(add);// need to wirte the address
	IIC_WaitAck();
	IIC_SendByte(dat);//need to wirte the date
	IIC_WaitAck();
	IIC_Stop();
}
uchar EEPROM_Read(uchar add)
{
	uchar temp;
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_WaitAck();
	IIC_SendByte(add);//need to read the address 
	IIC_WaitAck();
	IIC_Stop();

	IIC_Start();
	IIC_SendByte(0xa1);//read operation
	IIC_WaitAck();
	temp = IIC_RecByte();
	IIC_WaitAck();
	IIC_Stop();
	return temp;
}