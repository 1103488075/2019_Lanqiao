#include "STC15F2K60S2.h"
#include "intrins.h"
#include "iic.h"
typedef unsigned char uchar;
typedef unsigned int uint;

uchar code duanxuan [] ={0xc0, 0xf9, 0xa4, 0xb0,
                        0x99, 0x92, 0x82, 0xf8,
                        0x80, 0x90, 0xbf, 0xff};
uchar yi = 11,er = 11 ,san = 11,si = 11,wu = 11,liu = 11,qi = 11,ba = 11;
uchar pattern = 4;//LED灯模式选择1-4
uchar S6,S5,S4,S3;//scanf key
bit S7;
uint LED_value,t1,t2,LED_value2;//定时器0中断里的值
uint tim,ttt,AD_value;//定时器1中断里的值,
uchar flash;//流转间隔闪烁值
uchar i;//LED灯位移位
uchar luminance;//亮度控制数值 1-4
uint jiange_value = 400;

void key();
void led_1();
void led_2();
void led_3();
void Delay400ms();
void Delay3ms();
void Init_All();
void dispaly1(uchar yi,uchar er);
void dispaly2(uchar san,uchar si);
void dispaly3(uchar wu,uchar liu);
void dispaly4(uchar qi,uchar ba);
void Init_time0();//定时器零
void Init_time1();//定时器1
void luminance_adjust();
void ROM_Write();

void main()
{
    Init_All();
	Init_time1();
    Init_time0();
  
    while(1)
    {
        key();
        if(S6 == 1)//设置界面一，选中流转间隔（闪烁0.8）
        {
            if(flash % 2 == 1)//单数亮
            {
            yi = 10; er = pattern; san = 10; si = 11;
            wu = 11; liu = jiange_value /100%10; qi = jiange_value /10%10; ba = jiange_value %10;
            }
            else if(flash % 2 == 0)//双数灭
            {
                wu = 11; liu = 11; qi = 11; ba = 11;
            }
            if(S5 == 1 && S6 == 1)//控制间隔的值加减
            {
                S5 = 0;
                jiange_value = (jiange_value / 100 + 1)*100;
                if(jiange_value >= 1200 && S6 == 1)
                    jiange_value = 1200;
            }
            if(jiange_value >= 1000)//把流转间隔闪烁扩大到千位（闪烁0.8）
            {
                wu = jiange_value/100/10;
            }
            if(S4 == 1 && S6 == 1)
            {
                S4 = 0;
                jiange_value  = (jiange_value /100 - 1)*100;
                if(jiange_value <= 400)
                    jiange_value = 400;
            }
        }
        if(S6 == 2)//设置界面二，选中运行模式（闪烁0.8）
        {
            if(flash %2 == 1)
            {
                yi = 10; er = pattern; san = 10; si = 11;
                wu = 11; liu = jiange_value /100%10; qi = jiange_value /10%10; ba = jiange_value % 10;
            }
            else if(flash %2 == 0)
            {
                yi = 11; er =  11; san = 11; si = 11;
            }
            if(jiange_value >= 1000)
                wu = jiange_value /100/10;
            if(S5 == 1 && S6 == 2)//控制运行模式的加减
            {
                S5 = 0;
                pattern++;
                if(pattern >= 4 && S6 == 2)
                    pattern = 4;
                
            }
            if(S4 == 1 && S6 == 2)
            {
                S4 = 0;
                pattern--; 
                if(pattern <= 1 && S6 == 2)
                    pattern = 1;
            }
        }
        if(S3 == 1 && S6 == 0)//亮度显示单元
        {
            luminance_adjust();
            S3 = 0;
            yi = 11; er = 11; san = 11; si = 11; 
            wu = 11; liu = 11; qi = 10; ba = luminance;
        }
        else if(S3 == 0 && S6 == 0)//按键松手便关闭亮度显示单元
        {
            yi = 11; er = 11; san = 11; si = 11;
            wu = 11; liu = 11; qi = 11; ba = 11;
        }
        if(S6 == 3)//退出设置界面
        {
            S6 = 0;
            yi = 11,er = 11 ,san = 11,si = 11,wu = 11,liu = 11,qi = 11,ba = 11;
        }    
       //luminance_adjust();//亮度调节,从AD_read里获取ADvalue
       dispaly1(yi, er);
       dispaly2(san, si);
       dispaly3(wu, liu);
       dispaly4(qi, ba);
    }
}
void key()
{
    if(P30 == 0)//启动/停止键，控制LED流转
    {
        Delay3ms();
        if(P30 == 0)
        {
            S7 = ~S7;//S7 = 1 触发中断
        
        }
        while(!P30);
    }
    if(P31 == 0)//S6设置键，进入设置界面／非设置界面
    {
        Delay3ms();
        if(P31 == 0)
        {
            S6++;
        }
        while(!P31);
    }
    if(P32 == 0)//设置界面：选择运行模式按下按钮则模式编号+1，选择流转间隔按下流转间隔-100ms
    {
        Delay3ms();
        if(P32 == 0)
        {
            S5 = 1;
        }
        while(!P32);
    }
    if(P33 == 0 && S6 == 0)//进入LED当前亮度显示单元
    {
		Delay3ms();
        if(P33 == 0 && S6 == 0)
        { 
                S3 = 1;
        }
        //while(!P33);
    }
    if(P33 == 0 && S6 != 0)//设置界面下：运行模式下-1，流转间隔下+100
    {
        Delay3ms();
        if(P33 == 0)
        {
            S4 = 1; 
        }
        while(!P33);
    }
 
}
void ROM_Write()
{
    EEPROM_write(0x01, 4);
    Delay3ms();
    EEPROM_write(0x02, 5);
    Delay3ms();
    EEPROM_write(0x03, 6);
    Delay3ms();
    EEPROM_write(0x04, 8);
    Delay3ms();
}
void Init_time0()//2毫秒中断
{
    AUXR |= 0x80;
    TMOD &= 0xf0;
    TL0 = 0x9a;
    TH0 = 0Xa9;
    TF0 = 0;//清除
    TR0 = 1;//TF0清除标志
    ET0 = 1;//定时器零
    EA = 1;//总中断开关
}
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
    P2 = 0x80; P0 = 0xff;//led
    P2 = 0xc0; P0 = 0xff;//段选
    P2 = 0xff; P0 = 0xff;//位选
}
void dispaly1(uchar yi,uchar er)
{
    P2 = 0xc0; P0 = 0x01;
    P2 = 0xff; P0 = duanxuan[yi];
    Delay3ms();
    P2 = 0xc0; P0 = 0x02;
    P2 = 0xff; P0 = duanxuan[er];
    Delay3ms();
}
void dispaly2(uchar san,uchar si)
{
    P2 = 0xc0; P0 = 0x04;
    P2 = 0xff; P0 = duanxuan[san];
    Delay3ms();
    P2 = 0xc0; P0 = 0x08;
    P2 = 0xff; P0 = duanxuan[si];
    Delay3ms();
}
void dispaly3(uchar wu,uchar liu)
{
    P2 = 0xc0; P0 = 0x10;
    P2 = 0xff; P0 = duanxuan[wu];
    Delay3ms();
    P2 = 0xc0; P0 = 0x20;
    P2 = 0xff; P0 = duanxuan[liu];
    Delay3ms();
}
void dispaly4(uchar qi,uchar ba)
{
    P2 = 0xc0; P0 = 0x40;
    P2 = 0xff; P0 = duanxuan[qi];
    Delay3ms();
    P2 = 0xc0; P0 = 0x80;
    P2 = 0xff; P0 = duanxuan[ba];
    Delay3ms();
}
void Delay400ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 17;
	j = 208;
	k = 27;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void Init_time1()//定时器计时50微妙
{
    AUXR |= 0x40;//1T模式
    TMOD &= 0x0f;
    TL1 = 0xd7;
    TH1 = 0xfd;
    TF1 = 0;//标志位清除
    TR1 = 1;//定时器1开始
    EA = 1;//总中断开关
    ET1 = 1;//定时器1中断开始
}
void luminance_adjust()//亮度调节
{
    if(AD_value > 0 && AD_value <= 64)//等级1
        luminance = 1;
    else if(AD_value > 64 && AD_value <= 128)//等级二
        luminance = 2;
    else if(AD_value > 128 && AD_value <= 192)//等级三
        luminance = 3;
    else if(AD_value > 192 && AD_value <= 256)//等级四
        luminance = 4;
}
void interupt_time1() interrupt 3//定时器1为自动重装
{
    tim++;
    ttt++;
    if(tim > 256)
    tim = 0;
    if(ttt == 100)//5毫秒获取一次AD值,AD_read()不要放在while（）中
    {
        ttt = 0;
        AD_value = AD_read(0x03);//AD转换函数里获取到的值
    }
}
void interupt_time()    interrupt 1 //定时器零模式零为自动重装初始值
{
    if(S6 == 1|| S6 == 2)//设置里被选择的单元以0.8秒间隔亮灭
    {
        LED_value2++;
        if(LED_value2 == 400)
        {
            LED_value2 = 0;
            flash++;
            if(flash == 10)
                flash = 0;
        }
    }
    if(S7 == 1 && S6 == 0)//启动流水灯
    {
        LED_value++;
        if(LED_value >= jiange_value / 2)//中断计数值达到间隔闪烁时间，启动流水灯、边沿属性应有两个限制条件 
        {    
            if (pattern == 1)
            {
                LED_value = 0;
                P2 = 0x80; P0 = 0xfe;
                P0 = _crol_(P0, i);
                i++;
                if(i == 8)  i = 0;
                if(P0 == 0xff)  P0 = 0xfe;
            }
            if(pattern == 2)
            {
                LED_value = 0;
                P2 = 0x80; P0 = 0x7f;
                P0 = _cror_(P0, i);
                i++;
                if(i == 8)  i = 0;
                if(P0 == 0xff)  P0 = 0x7f;
                            
						}
            if(pattern == 3)
            {
                LED_value = 0;
                P2 = 0x80; t1 = 0x7f; t2 = 0xfe;
                P0 = _cror_(t1,i)&_crol_(t2, i);
                i++;
                if(i == 4)  i = 0;
                if(P0 == 0xff)
                {
                    t1 = 0x7f;  t2 = 0xfe;
                }
            }
            if(pattern == 4)
            {
                LED_value = 0;
                P2 = 0x80; t1 = 0xef; t2 = 0xf7;
                P0 = _crol_(t1,i)&_cror_(t2, i);
                i++;
                if(i == 4)  i = 0;
                if(P0 == 0xff)
                {
                    t1 = 0xef;  t2 = 0xf7;
                }
            }
        }
    }
}