#include "STC15F2K60S2.h"
#include "intrins.h"
#include "ds1302.h"
typedef unsigned char uchar;
typedef unsigned int uint;
/*
sbit SCK = P1^7;//时钟线
sbit SD = P2^3;//数据线
sbit RST = P1^3;//复位
#define RST_CLR     RST = 0     //拉低复位线
#define RST_SET     RST = 1     //拉高复位线
//双向数据
#define SDA_CLR     SD = 0
#define SDA_SET     SD = 1
#define SDA_R       SD
//时钟信号
#define SCK_CLR     SCK = 0
#define SCK_SET     SCK = 1

//时钟数据地址
#define ds1302_sec_addr     0x80
#define ds1302_min_addr     0x82
#define ds1302_hr_addr      0x84
#define ds1302_date_addr    0x86    //日地址
#define ds1302_month_addr   0x88    //月地址
#define ds1302_day_addr     0x8a    //星期几地址
#define ds1302_year_addr    0x8c    //年
#define ds1302_control_addr 0x8e   //写保护地址
#define ds1302_charger_addr 0x90    //电流充电命令
#define ds1302_clkburst_addr 0xbe       

void Write_Ds1302_Byte(uchar dat);//写一个字节数据
uchar Read_Ds1302_Byte(void);//读一个字节数据
//写入一字节
void Ds_1302_Single_Byte_Write(uchar addr,uchar dat);
//读出一字节
uchar Ds1302_Single_Byte_Read(uchar addr);
*/



void Write_Ds1302_Byte(uchar dat)//写入一个字节
{
    uchar i;
    SCK = 0;
    for(i = 0;i < 8;i++)
    {
        if (dat & 0x01)
            SDA_SET;    //SDA = 1;
        else
            SDA_CLR;    //SDA = 0;

        SCK_SET;
        SCK_CLR;
        dat = dat >> 1;        
    }
}
uchar Read_Ds1302_Byte(void)//读出一个字节
{
    uchar i,dat = 0;
    for(i = 0;i < 8;i++)
    {
        dat = dat >> 1;
        if (SDA_R) // 等价于if（SDA_R == 1）
            dat |= 0x80;
        else
            dat &= 0x7f;

        SCK_SET;//拉高时钟线
        SCK_CLR; //拉低时钟线
    }
    return dat;
}
//写入一个字节数据
void Ds1302_Single_Byte_Write(uchar addr,uchar dat)
{
    RST_CLR;//拉低复位线 
    SCK_CLR;//拉低时钟线    //实现初始化

    RST_SET;//启动ds1302， 复位置高
    addr = addr & 0xfe;
    Write_Ds1302_Byte(addr);//写入目标地址，保证是写操作
    Write_Ds1302_Byte(dat);//写入数据
    RST_CLR;
}
//单字节读出一字节数据
uchar Ds1302_Single_Byte_Read(uchar addr)
{
    uchar temp;
    RST_CLR;    //拉低RST，实现DS1302的初始化
    SCK_CLR;    //SCK拉低，实现DS1302的初始化

    RST_SET;    //启动DS1302总线，RST置高
    addr = addr | 0x01;
    Write_Ds1302_Byte(addr);//写入目标地址，保证是读操作
    temp = Read_Ds1302_Byte();//从ds1302中读出一个字节数据
    RST_CLR;    //停止总线
    return temp;
}

//Ds1302_Single_Byte_Write(0x8e, 0x80);

/*void DS1302_Read()
{
    uchar i;
    for(i = 0;i < 3;i++)
    {
        shijian[i] = Ds1302_Single_Byte_Read(DS_Write[i]);
    }
}*/
















































