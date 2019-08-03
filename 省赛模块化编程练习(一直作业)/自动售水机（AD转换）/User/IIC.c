#include "IIC.h"


void IIC_Start(void)
{
     SDA = 1;
     SCL = 1;
     somenop;
     SDA = 0;
     somenop;
     SCL = 0;
}
void IIC_Stop(void)
{
    SDA = 0;
    SCL = 1;
    somenop;
    SDA = 1;
}
void IIC_Ack(uchar ackbit)
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
void IIC_SenByte(uchar byt)
{
    uchar i;
    for(i = 0;i < 8;i++)
    {
        if(byt & 0x80)
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
uchar IIC_RecByte(void)
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
//=================AD read,need remember
uchar AD_Read(uchar add)
{
    float temp;
    IIC_Start();
    IIC_SenByte(0x90);//Send addressing
    IIC_WaitAck();  //wait answer
    IIC_SenByte(add);//0x03,control byte
    IIC_WaitAck();
    IIC_Stop();
    //===========AD read
    IIC_Start();
    IIC_SenByte(0x91);//read address
    IIC_WaitAck();  //wait answer
    temp = IIC_RecByte();//read byte
   // IIC_WaitAck();		 //No wait answer
    IIC_Stop();
    return temp;
}





