/*
  程序说明: IIC总线驱动程序（加注释版）
  软件环境: Keil uVision 5
  硬件环境: CT107单片机综合实训平台(12MHz)
  日    期: 2018-01-24
*/
#include<reg52.h>
#include "iic.h"

//总线启动条件	1
void IIC_Start(void)
{
	SDA = 1;
	SCL = 1;
	somenop;
	SDA = 0;
	somenop;
	SCL = 0;
}

//总线停止条件	2
void IIC_Stop(void)
{
	SDA = 0;
	SCL = 1;
	somenop;
	SDA = 1;
}

//主机应答位控制 3
/*主机做的都是编程控制，从机做的都是自主控制，也可以说是硬件控制，如主机给应答信号是编程控制，
  但是从机给应答信号是硬件控制，我们只需要在 WaitAck() 中检测SCL为高电平期间，SDA保持低电平一
  些时间，即可判定从机给了主机应答信号。
*/
void IIC_Ack(unsigned char ackbit)	 //1代表想继续接收
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

//等待应答	4
bit IIC_WaitAck(void) //返回一代表得到应答
{
    /*数据位有效性：SCL为高电平期间内，SDA必须先保持稳定，
	只有在时钟线为低电平期间，数据线的高电平或低电平状态才允许变化；*/
	SDA = 1;
	somenop;
	SCL = 1;
	somenop;
	if(SDA) //检测SDA数据线是否被拉低，若拉低返回 1，表示应答即继续接受数据；
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

//通过I2C总线发送数据	5
void IIC_SendByte(unsigned char byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(byte&0x80) //1000 0000
		{
			SDA = 1;
		}
		else
		{
			SDA = 0;
		}
		somenop;
		SCL = 1;
		somenop;
		SCL = 0;//IIC进行写操作时，时钟线SCL要拉低，数据线SDA才允许变化。
		byte <<= 1;//数据移位可放到最后？
	}
}

//从I2C总线上接收数据  6
unsigned char IIC_RecByte(void)
{
	unsigned char date;
	unsigned char i;

	for(i=0;i<8;i++)
	{
		SCL = 1;//IIC读取的时候，要拉高SCL保持数据稳定。
		somenop;
		date <<= 1;
		/* 如果数据线为高电平，说明有数据，或上0000 0001，取date的最后一位，
		而后date左移一位，向低位读*/
		if(SDA)
		date |= 0x01;
		SCL = 0;
		somenop;
	}
	return date;
}

//以下为自己需要写的程序部分

//向EEPROM里写入数据（地址+数据）
void Write_AT24C02(unsigned char add, unsigned char date)
{
    IIC_Start(); //发送起始位
    IIC_SendByte(0xa0);//  ,发送从设备的地址1010  000和读/写0选择位；
    /*释放总线，等到EEPROM拉低总线进行应答；如果EEPROM接收成功，则进行应答；
    若没有握手成功或者发送的数据错误时EEPROM不产生应答，此时要求重发或者终止*/
    IIC_WaitAck();
    IIC_SendByte(add);//发送想要写入的内部寄存器地址；
    IIC_WaitAck();//EEPROM对其发出应答；
    IIC_SendByte(date);//发送数据
    IIC_WaitAck();//EEPROM对其发出应答；
    IIC_Stop();//发送停止位
    delay10ms();
    /*EEPROM收到停止信号后，进入到一个内部的写入周期，大概需要10ms，此间任何操作都不会被EEPROM响应；
    (因此以这种方式的两次写入之间要插入一个延时，否则会导致失败*/
}

//从EEPROM里读数据（地址）
unsigned char ReadByte_AT24C02(unsigned char add)
{
    unsigned char date;
    IIC_Start();//发送起始位；
    IIC_SendByte(0xa0);// 1010  000 0激活该器件写操作，发送从机地址+读1/写0位
    IIC_WaitAck();
    IIC_SendByte(add);//发送内部寄存器地址；
    IIC_WaitAck();
    IIC_Start();//重新发送起始位，即restart；
    IIC_SendByte(0xa1);//1010 000 1，激活读操作,重新发送从机地址+读1/写0位；
    IIC_WaitAck();
    date=IIC_RecByte();//读取数据
    /* 主机接收器在接收到最后一个字节后，也不会发出ACK信号。
    于是，从机发送器释放SDA线，以允许主机发出 stop 信号结束传输。*/
    IIC_Ack(0);
    IIC_Stop();// 发送停止位?
}
