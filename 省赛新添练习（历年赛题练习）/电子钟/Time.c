#include "STC15F2K60S2.h"
#include "intrins.h"
#include "onewire.h"
#include "ds1302.h"

typedef unsigned char uchar;
typedef unsigned int uint;

uchar code duanxuan[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92,0x82, 0xf8, 0x80, 0x90, 0xbf, 0xff,0xc6};//0xc6 = C
uchar code DS_Write[] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90};//写进ds1302的时间地址
uchar code DS_Init_Time[] ={0x50, 0x59, 0x23, 10, 1, 16};

uchar yi = 2,er = 3,san = 10 ,si  = 5,wu = 9,liu = 10,qi = 5,ba = 0;
uchar S6 = 0 ,S7 = 0;//时钟设置单元、闹钟设置单元 
uchar S5, S4;//+、-
uchar add,minus;//加和减
uint value1;//记录中断值
uint LED_san1,LED_san2;//闹钟闪烁
uchar LED1,LED2;
uchar shijian[]={50,59,23};//从DS1302里获取的时间
uchar AlarmClock[] = {0,0,0};//设定的闹钟
uchar temperature = 23;

void Delay3ms();
void All_Init();
void key();
void display1(uchar yi,uchar er);
void display2(uchar san, uchar si);
void display3(uchar wu,uchar liu);
void display4(uchar qi, uchar ba);
void Time0Init(void);//定时1毫秒
uchar Read_temperature();
void DS1302_Init();


void main()
{
    All_Init();
    Time0Init();
    DS1302_Init();
    // yi = shijian[2]/10;  er = shijian[2]%10; san = 10;
    // si = shijian[1]/10;  wu = shijian[1]/10; liu = 10;
    // qi = shijian[0]/10;  ba = shijian[0]%10;
    temperature = Read_temperature();
    while(1)
    {
        key();
        if(S7 == 0 && S6 == 0 && S4 == 0)//激活设置单元/时钟显示状态
        {
            // yi = Ds1302_Single_Byte_Read(ds1302_hr_addr)/16;
            // er = Ds1302_Single_Byte_Read(ds1302_hr_addr)%16;
            // san = 10;
            // si = Ds1302_Single_Byte_Read(ds1302_min_addr)/16;
            // wu = Ds1302_Single_Byte_Read(ds1302_min_addr)%16;
            // liu = 10;
            // qi = Ds1302_Single_Byte_Read(ds1302_sec_addr)/16;
            // ba = Ds1302_Single_Byte_Read(ds1302_sec_addr)%16;

                 yi = shijian[2]/10; er = shijian[2]%10;san = 10;
                 si = shijian[1]/10; wu = shijian[1]%10;liu = 10;
                 qi = shijian[0]/10; ba = shijian[0]%10;
        }
        else if(S7 == 0 && S6 == 0 && S4 == 1)//切换温度显示界面
        {
            temperature = Read_temperature();
 
                S4 = 0;
                yi = 11; er = 11; san = 11; si = 11;
                wu = 11; liu = temperature /10; qi = temperature%10; ba = 12;//12是C
        }
        if(S4 == 2)//从温度界面切换
        S4 = 0;

        if(S7 == 1 && S6 == 0)//选择小时单元闪烁
        {  
            if(shijian[0] % 2 == 1)//用递增的秒数模2，偶数为0，基数为1，写成选中一秒闪烁
            {
                san = 10; liu = 10;
                yi = shijian[2]/10; er = shijian[2]%10;//hour
                si = shijian[1]/10; wu = shijian[1]%10;//minute
                qi = shijian[0]/10; ba = shijian[0]%10;//second
            }
            else
            {

                san = 10; liu = 10;
                yi = 11; er = 11; 
                si = shijian[1]/10; wu = shijian[1]%10;
                qi = shijian[0]/10; ba = shijian[0]%10;
            }
        }
        if(S7 == 2 && S6 == 0)//分钟单元闪烁
        {

            if(shijian[0] % 2 == 1)
            {   
                san = 10; liu = 10;
                yi = shijian[2]/10; er = shijian[2]%10;
                si = shijian[1]/10; wu = shijian[1]%10;
                qi = shijian[0]/10; ba = shijian[0]%10;
            }
            else
            {
                san = 10; liu = 10;
                yi = shijian[2]/10; er = shijian[2]%10;
                si = 11; wu = 11;
                qi = shijian[0]/10; ba = shijian[0]%10;
            }
        }
        if(S7 == 3 && S6 == 0)//秒单元闪烁
        {
            if(shijian[0]%2 == 1)
            {
                san = 10; liu = 10;
                yi = shijian[2]/10; er = shijian[2]%10;
                si = shijian[1]/10; wu = shijian[1]%10;
                qi = shijian[0]/10; ba = shijian[0]%10;  
            }
            else
            {
                san = 10; liu = 10;
                yi = shijian[2]/10; er = shijian[2]%10;
                si = shijian[1]/10; wu = shijian[1]%10;
                qi = 11; ba = 11;    
            }
        }
        if(S7 == 4 && S6 == 0)//重置选择设置键
            S7 = 0;

        if(S6 == 1)//闹钟小时单元
        {
            yi = AlarmClock[0]/10,er = AlarmClock[0]%10;
            san = 11,si = 11,wu = 11,liu = 11,qi = 11,ba = 11;
            if(S6 == 1 && S5 == 1)//按键设置闹钟
            {
                AlarmClock[0]++;
                S5 = 0;
            }
            if(S6 == 1 && minus == 1)
            {
                AlarmClock[0]--;
                minus = 0;
            }
        }
        if(S6 == 2)//闹钟分钟单元
        {
             yi = 11,er = 11,san = 11;
             si =AlarmClock[1]/10 ,wu = AlarmClock[1]%10,liu = 11,qi = 11,ba = 11;
             if(S6 == 2 && S5 == 1)//设置时钟
             {
                 AlarmClock[1]++;
                 S5 = 0;
             }
             if(S6 == 2 && minus == 1)
             {
                 AlarmClock[1]--;
                 minus = 0;
             }
        }
        if(S6 == 3)//闹秒单元设置
        {
            yi = 11; er = 11; san = 11; si = 11; wu = 11; liu = 11; 
            qi = AlarmClock[2]/10; ba = AlarmClock[2]%10;
            if(S6 == 3 && S5 == 1)
            {
                AlarmClock[2]++;
                S5 = 0;
            }   
            if(S6 == 3 && minus == 1)
            {
                AlarmClock[2]--;
                minus = 0;
            }
        }
        if(S6 >= 4)//退出闹钟设置界面
            S6 = 0;

         P2 = 0x80 ; P0 = 0xff;//此处将LED关闭，否则有余晖与干扰到数码管
           display1(yi,er);
           display2(san,si);
           display3(wu,liu);
           display4(qi,ba);
    }
}
void key()
{
    if(P30 == 0)//S7    时钟设置按钮,调整时分秒
    {
        Delay3ms();
        if(P30 == 0)
        {
            S7++;//S7为0，激活时钟设置，S7为1，间隔闪烁时单元,2间隔闪烁分单元,3间隔闪烁秒单元
        }
        while(!P30);
    }
    if(P31 == 0)//S6    进入闹钟设置界面——1为小时单元——2为分钟单元——3为秒钟单元
    {
        Delay3ms();
        if(P31 == 0)
        {
            S6++;
        }
        while(!P31);
    }
    if(P32 == 0)//S5 闹钟++
    {
        Delay3ms();
        if(P32 == 0)
        {
           S5 = 1;
        }
        while(!P32);
    }
    if(P33 == 0 && S6 == 0)//进入该循环表示切换温度界面
    {  
        Delay3ms();
        if(P33 == 0 && S6 == 0)
        {
            S4 = 1;
        }
 
    }
    if(P33 == 0 &&  S6 != 0 )//条件限制，正常做减法
    {
        Delay3ms();
        if(P33 == 0 && S6 != 0)
        {
            minus = 1;
        }
        while(!P33);
    }
}
void Time0Init(void)//定时1毫秒中断
{
    AUXR |= 0x80;
    TMOD &= 0xf0;
    TL0 = 0xcd;
    TH0 = 0xd4;
    TF0 = 0;
    TR0 = 1;//定时器零开始计时
    ET0 = 1;
    EA = 1; 
}
void Delay3ms()
{
    uchar i,j;
     _nop_(); _nop_();
    i = 33; j = 66;
    do
    {
        while(--j);
    } while(--i);
}
void All_Init()
{
    P2 = 0x80; P0 = 0xff;//LED
    P2 = 0xa0; P0 = 0x00;//buzz
    P2 = 0xc0; P0 = 0xff;//weixuan
    P2 = 0xff; P0 = 0xff;//duanxuan
}
void display1(uchar yi,uchar er)
{
    P2 = 0xc0; P0 = 0x01;
    P2 = 0xff; P0 = duanxuan[yi];
    Delay3ms();
    P2 = 0xc0 ; P0 = 0x02;
    P2 = 0xff; P0 = duanxuan[er];
    Delay3ms();
}
void display2(uchar san, uchar si)
{
    P2 = 0xc0; P0 = 0x04;
    P2 = 0xff; P0 = duanxuan[san];
    Delay3ms();
    P2 = 0xc0; P0 = 0x08;
    P2 = 0xff; P0 = duanxuan[si];
    Delay3ms();
}
void display3(uchar wu,uchar liu)
{
    P2 = 0xc0; P0 = 0x10;
    P2 = 0xff; P0 = duanxuan[wu];
    Delay3ms();
    P2 = 0xc0; P0 = 0x20;
    P2 = 0xff; P0 = duanxuan[liu];
    Delay3ms();
}
void display4(uchar qi, uchar ba)
{
    P2 = 0xc0; P0 = 0x40;
    P2 = 0xff; P0 = duanxuan[qi];
    Delay3ms();
    P2 = 0xc0; P0 = 0x80;
    P2 = 0xff; P0 = duanxuan[ba];
    Delay3ms();
}
uchar Read_temperature()
{
    uchar L,H;//读温度的低八位和高八位
    uchar temp;
    Init_DS18B20();
    Write_DS18B20(0xcc);//忽略rom指令
    Write_DS18B20(0x44);//发送温度转换指令
    Delay_OneWire(400);
    
    Init_DS18B20();
    Write_DS18B20(0xcc);//忽略rom
    Write_DS18B20(0xbe);//读DS18B20指令、
    L = Read_DS18B20();
    H = Read_DS18B20();
    temp = (H<<4)|(L>>4);
    return temp;
}
void DS1302_Init()
{
    uchar i;
    Ds1302_Single_Byte_Write(0x8e, 0x00);//关闭写保护
    for(i = 0;i < 7;i++)
    {
        Ds1302_Single_Byte_Write(DS_Write[i],DS_Init_Time[i]);//写进地址和要写进去的时间
    }
		Ds1302_Single_Byte_Write(0x8e, 0x80);
}
    
void time0()    interrupt 1     //定时器0模式0为自动重装
{   
    value1++;
    if(LED1 == 1)//设置闹钟，激活闹钟闪烁条件
    {
    LED_san1++;//200毫秒闪烁
    LED_san2++;//5秒计时
    }
    if(value1 == 1000)
    {
        value1 = 0;
        shijian[0]++;
         if(shijian[0] == 60)
             LED1 = 1;

        if(shijian[0] == 61)
          shijian[0] = 50;
    }

    if(LED_san1 >= 200 && LED_san2 <= 5000)//200毫秒闪烁,5秒后关闭
    {
            P2 = 0x80; P0 = 0xfe;
             LED_san1 = 0;
    }   
  
}