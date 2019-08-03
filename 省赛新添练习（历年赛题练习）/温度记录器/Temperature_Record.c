//===============温度记录器
#include "STC15F2K60S2.h"
#include "intrins.h"
#include "DS18B20.h"
#include "DS1302.h"
//typedef unsigned char uchar;
//typedef unsigned int uint;
void Delay2ms();
void Display1(uchar yi,uchar er);
void Display2(uchar san,uchar si);
void Display3(uchar wu, uchar liu);             
void Display4(uchar qi,uchar ba);
void ScanKey();
void Init_Time0();
void Init_All();
uchar code duanxuan[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xbf, 0xff};
uchar yi,er,san,si,wu,liu,qi,ba;
uchar S4,S5,S6,S7;
uchar second = 1;//采集时间、默认1秒采集一次
uint i,j,k,tem,value;//记录中断的值
uchar Time[] = {0,0,0};//时分秒
uchar temprature[10] = {0,0,0,0,0,0,0,0,0,0};//采集的温度
uchar Temprature_Dspaly;//温度采集显示界面
uchar temp;//这个区间里温度数组的里的位置

void main()
{
   
    Init_All();
	Init_Time0();
    Write_Time();
	yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 10,qi = second/10%10,ba = second%10;
    while(1)
    {
       // Read_Time();
        ScanKey();
        if(S4 == 1 && S5 == 0)//1second
        second = 1;
        if(S4 == 2)//5second
        second = 5;
        if(S4 == 3)//30second
        second = 30;
        if(S4 == 4)//60second
        second = 60;
        if(S4 == 5)
        S4 = 1;

        if(S5 == 1 && S6 == 0)//时钟显示界面、并开始采集温度
        {
             Read_Time();
            S4 = 0;//S4按键复位
            yi = Time[1]/10%10,er = Time[1]%10;//minutes
            si = Time[2]/10%10;wu = Time[2]%10;//second
            qi = second/10%10,ba = second % 10;//采集间隔时间
            if(j % 2 == 1)//提示符间隔1s闪烁
            {
                san = 11;
                liu = 11;
            }
            if(j % 2 == 0)//间隔闪烁
            {
                san = 10;
                liu = 10;
            }
        }
		if(S4 > 0 && S5 == 0)//参数设置界面&&S5 == 0
		{
		yi = 11,er = 11,san = 11,si = 11,wu = 11;
        liu = 10,qi = second/10%10,ba = second%10;
        }
        if(Temprature_Dspaly >= 1)//温度采集显示界面、亮起L1
        {
            yi = 10,er = 0,san = 0,si = 11;
            wu = 11,liu = 10,qi = temprature[temp]/10%10;
            ba = temprature[temp]%10;
            P2 = 0x80; P0 = 0xfe;
        }
        if(S6 == 1 && S4 == 0 )//查看储存的温度数据
        {
            S5 = 0;//降低时钟显示界面的优先级
            S6 = 0;
            Temprature_Dspaly = 0;//降低温度采集界面的优先级
            S6 = 0;
            P2 = 0x80; P0 = 0xff;//关闭L1
            er = temp/10%10;san = temp%10;
            si = 11, wu = 11, liu = 10;
            qi = temprature[temp]/10%10;ba = temprature[temp]%10;
            temp++;
            if(temp > 9)//限制数据边界属性
                temp = 0;
        }
		Display1(yi,er);
        Display2(san,si);
        Display3(wu,liu);
        Display4(qi,ba);
    }
}
void ScanKey()
{
    if(P30 == 0)
    {
        Delay2ms();
        if (P30 == 0)//重新进入参数设置界面
        {
            S4++;//重置参数、为下一次温度采集做准备
            tem = 0;  //重置参数
            value = 0; //重置参数
        }
        while(!P30);
    }
    if(P31 == 0)
    {
        Delay2ms();
        if(P31 == 0)
        {
            S6 = 1;
        }
        while(!P31);
    }
    if(P32 == 0)
    {
        Delay2ms();
        if(P32 == 0)
        {
            S5 = 1;
        }
        while(!P32);
    }
    if(P33 == 0)
    {
        Delay2ms();
        if(P33 == 0)
        {
            S4++;//参数设置界面
        }
        while(!P33);
    }
}
void Init_Time0()//2毫秒中断
{
    AUXR |= 0x80;
    TMOD &= 0xf0;//模式0
    TL0 = 0x9a;
    TH0 = 0xa9;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;
    EA = 1;
}
void Time0() interrupt 1    //2毫秒中断一次
{
    i++;
    k++;
    if(i >= 500)
    {
        i = 0;
        j++;
     //   Time[2]--;//模拟RTC 
        if(j >= 10)//提示符间隔一秒闪烁递增的值
            j = 0;
     //   if(Time[2] == 0)
      //  Time[2] = 59;
    }
    if(S5 == 1)//采集温度
    {
        if(k >= 500)
        {
            k = 0;
            value++;//每秒递增
            if(value == second && tem <= 9)//value每秒递增一次、与second相同时获取温度值
            {
                value = 0;
                temprature[tem] = Use_DS18B20();//tem是温度数组里的值
                tem++;
            }
            if(tem >= 10)
                Temprature_Dspaly = 1;
        }
    }
}
void Read_Time()
{
    Time[2] = Ds1302_Single_Byte_Read(0x81);//second
    Time[1] = Ds1302_Single_Byte_Read(0x83);//minute
    Time[0] = Ds1302_Single_Byte_Read(0x85);//hr
    Time[2] =Time[2] /16 *10+Time[2]%16;//读取到的PCD码转换为10进制然后显示
    Time[1] = Time[1] /16 *10+Time[1]%16;//或者
    Time[0] = Time[0] /16 *10+Time[0]%16;
}
void Delay2ms()//2ms
{
    uchar i,j;
    _nop_(); _nop_();
    i = 22; j = 128;
    do
    {
        while(--j);
    } while(--i);
}
void Init_All()
{
    P2 = 0x80; P0 = 0xff;
    P2 = 0xa0; P0 = 0x00;//buzz
    P2 = 0xc0; P0 = 0xff;
    P2 = 0xff; P0 = 0xff;
}
void Display1(uchar yi,uchar er)
{
    P2 = 0xc0; P0 = 0x01;
    P2 = 0xff; P0 = duanxuan[yi];
    Delay2ms();
    P2 = 0xc0; P0 = 0x02;
    P2 = 0xff; P0 = duanxuan[er];
    Delay2ms();
}
void Display2(uchar san,uchar si)
{
    P2 = 0xc0; P0 = 0x04;
    P2 = 0xff; P0 = duanxuan[san];
    Delay2ms();
    P2 = 0xc0; P0 = 0x08;
    P2 = 0xff; P0 = duanxuan[si];
    Delay2ms();
}
void Display3(uchar wu,uchar liu)
{
    P2 = 0xc0; P0 = 0x10;
    P2 = 0xff; P0 = duanxuan[wu];
    Delay2ms();
    P2 = 0xc0; P0 = 0x20;
    P2 = 0xff; P0 = duanxuan[liu];
    Delay2ms();
}
void Display4(uchar qi,uchar ba)
{
    P2 = 0xc0; P0 = 0x40;
    P2 = 0xff; P0 = duanxuan[qi];
    Delay2ms();
    P2 = 0xc0; P0 = 0x80;
    P2 = 0xff; P0 = duanxuan[ba];
    Delay2ms();
}