#include "STC15F2K60S2.h"
#include "onewire.h"
#include "intrins.h"
typedef unsigned int uint;
typedef unsigned char uchar;


void Delay_OneWire(unsigned int t)
{
    //1T单片机延时1us时需多加12个时钟周期
    unsigned char i;
    while(t--)
    {
        for(i = 0;i < 12;i++);
    }
}
bit Init_DS18B20(void)//初始化单总线
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
void Write_DS18B20(unsigned char dat)//写进命令
{
    unsigned char i;
    for(i = 0; i < 8; i++)
    {
        DQ = 0;
        _nop_();
        DQ = dat&0x01;
        Delay_OneWire(5);
        DQ = 1;
        dat >>= 1;
    }
    Delay_OneWire(5);
}
unsigned char Read_DS18B20(void)
{
    unsigned char i;
    unsigned char dat;
    for(i = 0; i < 8;i++)
    {
        DQ = 0;
        _nop_();
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
