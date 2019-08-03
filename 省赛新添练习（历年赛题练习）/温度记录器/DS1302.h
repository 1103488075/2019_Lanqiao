#include "STC15F2K60S2.h"
//typedef unsigned char uchar;
//typedef unsigned int uint;
sbit SCK = P1^7;
sbit SD = P2^3;
sbit RST = P1^3;

#define RST_CLR     RST = 0//电平置低
#define RST_SET     RST = 1//电平置高
#define SDA_CLR     SD = 0
#define SDA_SET     SD = 1
#define SDA_R       SD

//时钟信号
#define SCK_CLR     SCK = 0//时钟信号
#define SCK_SET     SCK = 1//电平置高

//时钟地址
#define ds1302_sec_addr     0x80
#define ds1302_min_addr     0x82
#define ds1302_hr_addr      0x84
#define ds1302_date_addr    0x86
#define ds1302_month_addr   0x88
#define ds1302_day_addr     0x8a
#define ds1302_year_addr    0x8c    
#define ds1302_control_addr 0x8ee   //写保护命令
#define ds1302_charger_addr 0x90    //涓电流充电命令
#define ds1302_clkburst_addr 0xbe   //日历、时钟突发模式命令

extern void Write_Ds1302_Byte(unsigned char dat);//单字节写入一字节数据
extern unsigned char Read_Ds1302_Byte(void);//读出一字节
extern void Ds1302_Single_Byte_Write(unsigned char addr,unsigned char dat);//写进一字节
extern unsigned char Ds1302_Single_Byte_Read(unsigned char addr);//读出一字节
extern void Write_Time();
extern void Read_Time();