#include "STC15F2K60S2.h"
#include "intrins.h"
#include "iic.h"
typedef unsigned int uint;
typedef unsigned char uchar;

#define somenop {_nop_();_nop_();_nop_();_nop_();_nop_()}
#define SlaveAddrW 0xa0
#define SlaveAddrR  0xa1

sbit SDA = P2^1;
sbit SCL = P2^0;
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Ack(uchar ackbit);
void IIC_SenByte(uchar byt);
bit IIC_WaitAck(void);
uchar IIC_RecByte(void);

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