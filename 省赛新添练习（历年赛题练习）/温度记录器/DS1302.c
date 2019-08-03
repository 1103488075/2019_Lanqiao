#include "DS1302.h"

void Write_Ds1302_Byte(unsigned char dat)
{
    unsigned char i;
    SCK = 0;
    for(i = 0;i < 8;i++)
    {
        if (dat & 0x01)
        {
            SDA_SET;
        }
        else
        {
            SDA_CLR;
        }
        SCK_SET;
        SCK_CLR;
        dat = dat >> 1; 
    }
}
unsigned char Read_Ds1302_Byte(void)
{
    unsigned char i,dat = 0;
    for(i = 0;i < 8;i++)
    {
        dat =  dat >> 1;
        if (SDA_R)
        {
            dat |= 0x80;
        }
        else
        {
            dat &= 0x7f;
        }
        SCK_SET;
        SCK_CLR;
    }
    return dat;
}
unsigned char Ds1302_Single_Byte_Read(unsigned char addr)
{
    unsigned char temp;
    RST_CLR;
    SCK_CLR;

    RST_SET;//启动总线
    addr = addr | 0x01;
    Write_Ds1302_Byte(addr);//写进目标地址addr，保证是读操作
    temp = Read_Ds1302_Byte();//从ds1302中读出一个字节
    RST_CLR;//停止总线
    SDA_CLR;//电平置低
    return temp;
}
void Ds1302_Single_Byte_Write(unsigned char addr, unsigned char dat)
{
    RST_CLR;
    SCK_CLR;

    RST_SET;
    addr = addr & 0xfe;
    Write_Ds1302_Byte(addr);//写进目标地址addr，保证是写操作
    Write_Ds1302_Byte(dat);//写入数据dat
    RST_CLR;//停止总线
}
void Write_Time()
{
    Ds1302_Single_Byte_Write(0x8e,0x00);//23，59，50
    Ds1302_Single_Byte_Write(ds1302_sec_addr,0x50);//second
    Ds1302_Single_Byte_Write(ds1302_min_addr,0x59);//minute
    Ds1302_Single_Byte_Write(ds1302_hr_addr,0x23);//hr
    // Ds1302_Single_Byte_Write(ds1302_date_addr,0x12);//日期
    // Ds1302_Single_Byte_Write(ds1302_month_addr,0x12);//月份
    // Ds1302_Single_Byte_Write(ds1302_day_addr,0x15);//年
    // Ds1302_Single_Byte_Write(ds1302_year_addr,0x12);//几号
    Ds1302_Single_Byte_Write(0x8e, 0x80);//禁止写保护
}
