//========模拟风扇控制系统
#include "STC15F2K60S2.h"
#include "intrins.h"
#include "temperatrue.h"
 
void Init_All();
void Delay3ms();
void Display1(uchar yi,uchar er);
void Display2(uchar san,uchar si);
void Display3(uchar wu,uchar liu);
void Display4(uchar qi,uchar ba);
void KeyScan();
void Init_Time0();
void Init_Time1();
//sbit  PWM = P3^4;//输出脉宽
uchar code duanxuan[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xbf, 0xff,0xc6};//oxc6 = c
uchar yi, er, san, si, wu, liu, qi, ba;
uchar S6,S5,S4;//按键
bit S7;//布尔值
uchar pattern = 0;  //模式1-3：睡眠风1、自然风2、常风3、室温4
uint i;     //定时器0中断里的变量
int Job_Time = 10; //风扇工作时间倒计时、用有符号整型可减到负数
uchar temperature = 18;//室温
uchar Add_Time = 0; //增加时间功能
uint value1 = 0;//定时器1中断内的值
uchar pluse = 0;//定时1中的调制脉宽值

void main()
{
    Init_All();
    Init_Time0();//1毫秒定时器
    Init_Time1();//10微秒
    temperature = Use_DS18B20();
    yi = 10,er = pattern, san = 10, si = 11, wu = 0, liu = Job_Time/100%10, qi = Job_Time/10%10, ba = Job_Time%10;
    while(1)
    {
        if(S7 == 1)//温度界面
        {
            pattern = 4; er = pattern;
            san = 10,wu = 11,liu = temperature/10%10,qi = temperature%10, ba =  12;
        }
        else if(S7 == 0)//工作模式和剩余时间界面
        {
        yi = 10,er = pattern, san = 10, si = pluse/10%10, wu = pluse%10, liu = Job_Time/100%10, qi = Job_Time/10%10, ba = Job_Time%10;
        }
        if(S6 == 1)//停止、清零、PWM信号停止输出
        {
            Job_Time = 0;
            P2 = 0x80; P0 = 0xff;//停止led常亮
        }
        if(S5 == 1)//定时加一分钟、设定剩余工作时间为当前定时时间、重新开始倒计时
        {
            S6 = 0;//启动工作时间
            S5 = 0;//重置S5按键        
            Job_Time = 0;//0minute
            Add_Time++;
            if(Add_Time == 2)//1minute
                Job_Time = 60;
            if(Add_Time == 3)//2minute
            {
                    Job_Time = 120;
                    Add_Time = 0;
            }
        } 
        if(S4 == 1)//优先级比停止按键低
            pattern = 1;//睡眠风.led1常亮
        if(S4 == 2 )
            pattern = 2;//自然风      
        if(S4 == 3 )
        {
            S4 = 0;
            pattern = 3;//常风   
        }
        if(pattern == 1 && S6 == 0)//led1常亮
        {
            pluse = 20;
            P2 = 0x80; P0 = 0xfe;
        }
        if(pattern == 2 && S6 == 0)//led2常亮
        {
            pluse = 30;
            P2 = 0x80; P0 = 0xfd;
        }
        if(pattern == 3 && S6 == 0)//led3常亮
        {
            pluse = 70;
            P2 = 0x80; P0 = 0xfb;
        }
        if(Job_Time <= 0)//关闭led提示灯
        {
            P2 = 0x80; P0 = 0xff;
        }
        
		KeyScan();
        Display1(yi,er);
        Display2(san,si);
        Display3(wu,liu);
        Display4(qi,ba);
    }
}
void KeyScan()
{
    if(P30 == 0)//显示室温
    {
        Delay3ms();
        if(P30 == 0)
        {
        S7 = ~S7;
        }
        while(!P30);
    }
    if(P31 == 0)//停止按键、清零工作时间、PWM停止输出
    {
        Delay3ms();
        if(P31 == 0)
        {
            S6 = 1;
        }
        while(!P31);
    }
    if(P32 == 0)//启动按键、按下一次增加一分钟
    {
        Delay3ms();
        if(P32 == 0)
        {
            S5++;
        }
        while(!P32);
    }
  
    if(P33 == 0)//按键切换睡眠风、自然风、常风
    {
        Delay3ms();
        if(P33 == 0)
        {
            S4 ++;
        }
        while(!P33);
    }
}
void Init_Time1()//定时10微秒中断一次
{
    AUXR |= 0x40;//1t
    TMOD &= 0x0f;
    TL1 = 0x91;
    TH1 = 0xff;
    TF1 = 0;
    TR1 = 1;
    EA = 1;
    ET1 = 1; 
}
void Init_Time0()
{
    AUXR |= 0x80;//1t
    TMOD &= 0xf0;
    TL0 = 0xc0;
    TH0 = 0xd4;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;//中断零允许
    EA = 1;//中断总开关
}
void Time0()  interrupt 1   //模式1自动重装
{
    i++;
    if(i >= 1000 && S6 == 0)//50秒倒计时工作时间
    {
        i = 0;
        Job_Time--;
         if(Job_Time <= 0)
         {
             Job_Time = 0;
         }
    }
}
void Time1() interrupt 3    //定时器1、10微秒中断一次
{
    value1++;
    if(value1 >= 100)//10微秒中断100次为1毫秒 = 1KHz
    {
            value1 = 0;
            P34 = 0;
    }
    if(value1 < pluse)//pluse为脉宽值 20% 30% 70%
    {
        P34 = 1;//输出脉宽
    }
    else
    {
        P34 = 0;
    }
}
void Init_All()
{
    P2 = 0xa0; P0 = 0x00;//buzz,moto;
    P2 = 0x80; P0 = 0xff;
    P2 = 0xc0; P0 = 0xff;
    P2 = 0xff; P0 = 0xff;
}
void Delay3ms()
{
    uchar i,j;
    _nop_(); _nop_();_nop_();
    i = 11; j = 190;
    do
    {
        while(--j);
    }while(--i);
}
void Display1(uchar yi,uchar er)
{
    P2 = 0xc0; P0 = 0x01;
    P2 = 0xff; P0 = duanxuan[yi];
    Delay3ms();
    P2 = 0xc0; P0 = 0x02;
    P2 = 0xff; P0 = duanxuan[er];
    Delay3ms();
}
void Display2(uchar san,uchar si)
{
    P2 = 0xc0;  P0 = 0x04;
    P2 = 0xff;  P0 = duanxuan[san];
    Delay3ms();
    P2 = 0xc0; P0 = 0x08;
    P2 = 0xff; P0 = duanxuan[si];
    Delay3ms();
}
void Display3(uchar wu,uchar liu)
{
    P2 = 0xc0; P0 =0x10;
    P2 = 0xff; P0 = duanxuan[wu];
    Delay3ms();
    P2 = 0xc0; P0 = 0x20;
    P2 = 0xff; P0 = duanxuan[liu];
    Delay3ms();
}
void Display4(uchar qi,uchar ba)
{
    P2 = 0xc0; P0 = 0x40;
    P2 = 0xff; P0 = duanxuan[qi];
    Delay3ms();
    P2 = 0xc0; P0 = 0x80;
    P2 = 0xff; P0 = duanxuan[ba];
    Delay3ms();
}













