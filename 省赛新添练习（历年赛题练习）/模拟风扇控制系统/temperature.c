#include "STC15F2K60S2.h"
#include "temperatrue.h"

void Delay_OneWire(uint t)
{
    uchar i;
    while(t--)
    {
        for(i = 0; i < 12; i++);
    }
}
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
void Write_DS18B20(uchar dat)
{
    uchar i;
    for(i = 0;i < 8;i++)
    {
        DQ = 0;
        DQ = dat & 0x01;
        Delay_OneWire(5);
        DQ = 1;
        dat >>= 1;
    }
    Delay_OneWire(5);
}
uchar Read_DS18B20(void)
{
    uchar i;
    uchar dat;
    for(i = 0;i < 8;i++)
    {
        DQ = 0;
        dat >>= 1;
        DQ = 1;
        if(DQ)
            dat |= 0x80;
        Delay_OneWire(5);
    }
    return dat;
}
uchar Use_DS18B20()
{
    uchar TH,TL,temp;
    Init_DS18B20();
    Write_DS18B20(0xcc);//忽略rom
    Write_DS18B20(0x44);//转换指令
    Delay_OneWire(200);//200us
    
    Init_DS18B20();
    Write_DS18B20(0xcc);
    Write_DS18B20(0xbe);//读数据指令
    TL = Read_DS18B20();
    TH = Read_DS18B20();
    temp = (TH<<4)|(TL>>4);
    return temp;
}






