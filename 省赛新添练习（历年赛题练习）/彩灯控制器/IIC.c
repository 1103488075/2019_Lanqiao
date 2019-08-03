#include "STC15F2K60S2.h"
#include "intrins.h"
#include "iic.h"
typedef unsigned int uint;
typedef unsigned char uchar;

void IIC_Start()//开始
{
    SDA = 1;
    SCL = 1;
    somenop;
    SDA = 0;
    somenop;
    SCL = 0;
}
void IIC_Stop(void)//开始
{
    SDA = 0;
    SCL = 1;
    somenop;
    SDA = 1;
}
void IIC_Ack(uchar ackbit)//应答位控制
{
    
    if (ackbit) 
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
bit IIC_WaitAck(void)//等待应答
{
    SDA = 1;
    somenop;
    SCL = 1;
    somenop; 
    if (SDA)
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
void IIC_SenByte(uchar byt)//发送数据
{
    uchar i;
    for(i = 0;i < 8;i++)
    {
        if (byt & 0x80)
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
uchar IIC_RecByte(void)//接收数据
{
    uchar da;
    uchar i;
    
    for(i = 0;i < 8;i++)
    {
        SCL = 1;
        somenop;
        da <<= 1;
        if (SDA)
        {
            da |= 0x01;
        }
        SCL = 0;
        somenop;
    }
    return da;
}
uchar AD_read(uchar add)//写进数据，然后读取AD值
{
	float temp;
	//写地址器件操作
	IIC_Start();
	IIC_SenByte(0x90);//发送寻址
	IIC_WaitAck();
	IIC_SenByte(add);//发送0x03,器件地址
	IIC_WaitAck();
	IIC_Stop();
	
	//读取操作
	IIC_Start();
	IIC_SenByte(0x91);//发送寻址
	IIC_WaitAck();
	IIC_SenByte(add);
	IIC_WaitAck();
	temp = IIC_RecByte();
	IIC_Stop();
	
	return temp;
}
uchar EEPROM_read(uchar add)//写进地址
{
	uint temp;
	IIC_Start();
	IIC_SenByte(0xa0);
	IIC_WaitAck();
	IIC_SenByte(add);
	IIC_WaitAck();
	IIC_Stop();
	
	IIC_Start();
	IIC_SenByte(0xa1);//IIC的读命令操作
	IIC_WaitAck();
	temp = IIC_RecByte();
	IIC_Stop();
	
	return temp;
}
void EEPROM_write(uchar add, uchar dat)//写进EEPROM需要分别写进地址和数据
{
	IIC_Start();
	IIC_SenByte(0xa0);//IIC的写命令操作
	IIC_WaitAck();
	IIC_SenByte(add);
	IIC_WaitAck();
	IIC_SenByte(dat);
	IIC_WaitAck();
	IIC_Stop();
}