#include "STC15F2K60S2.h"
#include "intrins.h"
typedef unsigned int uint;
typedef unsigned char uchar;
sbit scl = P2^0;
sbit sda = P2^1;

uchar code SMG[]= {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92,
                    0x82, 0xf8, 0x80,0x90, 0xbf, 0xff
                    };
uchar yi=11, er=11, san=11, si=11, wu=11, liu=11, qi=11, ba=1;
void all_init()
{
    P2 = 0xa0; P0 = 0x00;//蜂鸣器继电器
    P2 = 0x80; P0 = 0xff;//LED
    P2 = 0xff; P0 = 0xff;//段选
    P2 = 0xc0; P0 = 0xff;//位选
}
void DelayMS(uchar i)
{
    uint j,k;
    for(j = i; j>0; j--)
    for(k = 846; k>0; k--);
}
void dispaly1(uchar yi, uchar er)
{  
    P2 = 0xc0; P0 = 0x01;
    P2 = 0xff; P0 = SMG[yi];
    DelayMS(2);
    P2 = 0xc0; P0 = 0x02;
    P2 = 0xff; P0 = SMG[er];
    DelayMS(2);
}
void dispaly2(uchar san,uchar si)
{
    P2 = 0xc0; P0 = 0x04;
    P2 = 0xff; P0 = SMG[san];
    DelayMS(2); 
    P2 = 0xc0; P0 = 0x08;
    P2 = 0xff; P0 = SMG[si];
    DelayMS(2);
}
void dispaly3(uchar wu,uchar liu)
{
    P2 = 0xc0; P0 = 0x10;
    P2 = 0xff; P0 = SMG[wu];
    DelayMS(2);
    P2 = 0xc0; P0 = 0x20;
    P2 = 0xff; P0 = SMG[liu];
}
void dispaly4(uchar qi,uchar ba)
{
    P2 = 0xc0; P0 = 0x40;
    P2 = 0xff; P0 = SMG[qi];
    DelayMS(2);
    P2 = 0xc0; P0 = 0x80;
    P2 = 0xff; P0 = SMG[ba];
    DelayMS(2);
}
void write_byte(uchar dat)//写字节
{
    uchar i;
    for(i = 0;i<8; i++)
    {//每写一位字节，拉低一次时钟线
        scl = 0;
        sda = dat&0x80;
        scl = 1;
        dat <<= 1;
        //写进8位字节，位移8位
    }
    scl = 0;//返回信号
}

void IIC_start()//开始信号
{
    sda = 1; _nop_();//数据线拉低
    scl = 1; _nop_();//时钟线为高
    sda = 0; _nop_();
    scl = 0; _nop_();//时钟线拉低，为数据稳定
}
void IIC_stop()//停止信号
{
    sda = 0; _nop_();//数据线拉高
    scl = 1; _nop_();//时钟线保持不变
    sda = 1; _nop_();
}

uchar ack()//返回信号
{
    scl = 1;
    _nop_();
    if(sda == 1)
    {
        scl = 0;//返回0，通讯失败
        IIC_stop();//停止
        return 0;
    }
    else
    {
        scl = 0;
        return 1;//返回1，通讯成功
    }
}
void IIC_write(uchar add, uchar dat)//写操作
{
    IIC_start();
    write_byte(0x90);
    ack();
    write_byte(add);
    ack();
    write_byte(dat);
    ack();
    IIC_stop();//一个写周期完成
}
uchar IIC_readbyte()//读字节
{
    uchar dat; uchar i;
    for(i = 0; i<8; i++)
    {
        scl = 1;//拉高时钟线，传输数据
        _nop_();_nop_();_nop_();_nop_();_nop_();//五个机械周期的延时
        dat <<= 1;
        if(sda)
        {
            dat |= 0x01;//计算
        }
        scl = 0;
    }
    return dat;//返回值
}
uchar IIC_read(uchar add)//读操作
{
	uchar temp;
    IIC_start();
    write_byte(0x90);
    ack();//答应信号返回0，不往下走，返回1，继续
    write_byte(add);
    ack();
    IIC_stop();

    IIC_start();
    write_byte(0x91);
    ack();
    temp = IIC_readbyte();
    IIC_stop();
   // temp = 0.39*temp;//显示0-100
    return temp;
}
void main()
{
    uchar num;
    //uchar temp = 123;
    //all_init();
    //IIC_write(0x00,0);//初始化程序，不屏蔽每次上电都为零
    //num = IIC_read(0x00);//init program
    //IIC_write(0x00,num+1);
    while(1)
    {
        num = IIC_read(0x03);//初始化
        yi = num/100;
        er = num%100/10;
        san = num%10;
        dispaly1(yi,er);//显示函数
        dispaly2(san,si);
    }
}