#include "STC15F2K60S2.H"
#include "intrins.h"
typedef unsigned int uint;
typedef unsigned char uchar;

uchar code SMG[]={0xc0,0xf9,0xa4,0xb0,
                  0x99,0x92,0x82,0xf8,
                  0x80,0x90,0xbf,0xff};
uchar yi = 8, er = 7, san = 6, si = 5, wu = 4;
uchar liu = 3, qi = 2, ba = 1;
sbit CE = P1^3;
sbit IO = P2^3;
sbit SCLK = P1^7;

uchar code ds[] = {55,59,23,10,10,1,16};
//秒  分钟  小时  日期  月份  星期 年份

uchar shijian[7];

void writebyte(uchar dat);
void write(uchar add,uchar dat);
void dsinit();
uchar read(uchar add);
uchar readbyte();
void readtime();

void Delay3ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 33;
	j = 66;
	do
	{
		while (--j);
	} while (--i);
}

void Init_All()
{
    P2 = 0xa0; P0 = 0x00;//buzz
    P2 = 0x80; P0 = 0xff;//LED
    P2 = 0xc0; P0 = 0xff;
    P2 = 0xff; P0 = 0xff;
}
void display1(uchar yi, uchar er)
{
    P2 = 0xc0; P0 = 0x01;
    P2 = 0xff; P0 = SMG[yi];
    Delay3ms();
    P2 = 0xc0; P0 = 0x02;
    P2 = 0xff; P0 = SMG[er];
    Delay3ms();
}
void display2(uchar san, uchar si)
{
    P2 = 0xc0; P0 = 0x04;
    P2 = 0xff; P0 = SMG[san];
    Delay3ms();
    P2 = 0xc0; P0 = 0x08;
    P2 = 0xff; P0 = SMG[si];
    Delay3ms();
}
void display3(uchar wu, uchar liu)
{
    P2 = 0xc0; P0 = 0x10;
    P2 = 0xff; P0 = SMG[wu];
    Delay3ms();
    P2 = 0xc0; P0 = 0x20;
    P2 = 0xff;P0 = SMG[liu];
    Delay3ms();
}
void display4(uchar qi,uchar ba)
{
    P2 = 0xc0; P0 = 0x40;
    P2 = 0xff; P0 = SMG[qi];
    Delay3ms();
    P2 = 0xc0; P0 = 0x80;
    P2 = 0xff; P0 = SMG[ba];
    Delay3ms();
}
void readtime()
{
    uchar i;
    uchar add = 0x81;
    write(0x8e,0x00);//写保护命令
    for(i = 0;i < 7;i++)
    {
        shijian[i] = read(add);
        add = add+2;
        
    } 
    write(0x8e, 0x80);
}
uchar read(uchar add)
{
    uchar i,temp;
    uchar dat1,dat2;
    CE = 0;
    SCLK = 0;
    CE = 1;
    writebyte(add);
    for(i = 0;i < 8;i++)
    {
        SCLK = 0;
        temp >>= 1;
        if(IO)
        {
            temp |=0x80;
        }
        SCLK = 1;
    }
    IO = 0;
    dat1 = temp/16;
    dat2 = temp%16;
    temp = dat1*10+dat2;
    return temp;
}
void writebyte(uchar dat)
{
    uchar i;
    for(i = 0;i < 8;i++)
    {
        SCLK = 0;
        IO = dat & 0x01;
        SCLK = 1;
        dat >>= 1;
    }
}
void write(uchar add,uchar dat)
{
    uchar num;
    CE = 0; SCLK = 0;   CE = 1;
    writebyte(add);
    num = (dat/10<<4)|(dat % 10);
    writebyte(num);
    CE = 0;  
}
void dsinit()//写入时间
{
    uchar i;
    uchar add = 0x80;
    write(0x8e,0x00);
    for(i = 0;i < 7;i++)
    {
        write(add,ds[i]);
        add = add+2;
    }
    write(0x8e, 0x80);
}


void main()
{
    Init_All();
    dsinit();
    while(1)
    {
     readtime();
      yi = shijian[2]/10;
      er = shijian[2]%10;
      san = shijian[11];
      si = shijian[1]/10;
     wu = shijian[1]%10;
      liu = shijian[11];
      qi = shijian[0]/10;
      ba = shijian[0]%10;
     display1(yi,er);
     display2(san,si);
     display3(wu,liu);
     display4(qi,ba);
    }
   
}