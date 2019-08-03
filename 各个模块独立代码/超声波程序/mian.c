/*******************************************************************************  
* 文件名称：超声波测距实验
* 实验目的：1.掌握超声波测距原理
*           2.掌握15单片机定时器工作模式和配置方法
* 程序说明：设计延时函数，需要根据单片机的时钟频率进行调整,本例工作于11.0592MHz
* 硬件说明：IAP15F2K61S2@11.0592MHz
* 日期版本：2017-1-30
*******************************************************************************/

#include<STC15F2K60S2.H>
#include "intrins.h"

#define uchar unsigned char 
#define uint unsigned int	

#define somenop {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); _nop_();}
sbit TX = P1^0;  //发射引脚
sbit RX = P1^1;  //接收引脚

uchar code tab[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF};
uchar yi,er,san,si,wu ,liu,qi,ba;

unsigned int intr = 0;
bit s_flag;
unsigned int t = 0;

void send_wave(void);
void Timer0Init(void)	;
void Timer1Init(void);

void delayms(int ms);
void allinit();
void display1(uchar yi,uchar er);
void display2(uchar san,uchar si);
void display3(uchar wu,uchar liu);
void display4(uchar qi,uchar ba);

void main()
{
	unsigned int distance;
	
	Timer0Init();
  	Timer1Init();

	EA = 1;
	ET0 = 1;  //打开定时器0中断
	
	allinit();
	yi=11;er=11;san=11;si=11;wu=11;liu=0;qi=0;ba=0;
	
	while(1)
	{
		if(s_flag) // 200毫秒更新一次数据 
		{
			s_flag = 0;
			send_wave();  //发送方波信号
			TR1 = 1;  //启动计时
			while((RX == 1) && (TF1 == 0));  //等待收到脉冲
			TR1 = 0;  //关闭计时		
			
			if(TF1 == 1)//发生溢出
			{
				TF1 = 0;
				distance = 9999;  //无返回
			}
			else
			{		
				t = TH1;// 计算时间  
				t <<= 8;
				t |= TL1;
				distance = (unsigned int)(t*0.017);  //计算距离	
				distance = distance/12;
				//t*340   // t/1000000*340/2*100
			}
			TH1 = 0;
			TL1 = 0;
		}
		
		//数据处理  						 
		liu = distance/100;
		qi = distance%100/10;
		ba = distance%10; 
		
		display1(yi,er);
		display2(san,si);
		display3(wu,liu);
		display4(qi,ba);
	}
}

void Timer0Init(void)		//2毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x9A;		//设置定时初值
	TH0 = 0xA9;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

void Timer1Init(void)		//2毫秒@11.0592MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
}

//定时器0中断服务函数
void isr_timer_0(void)  interrupt 1  //默认中断优先级 1
{
	TL0 = 0x9A;		//设置定时初值
	TH0 = 0xA9;		//设置定时初值

	if(++intr == 100)
	{
		s_flag = 1;
		intr = 0;
  }
}

//TX引脚发送40KHz方波信号驱动超声波发送探头
//使用软件延时注意RC振荡器频率
void send_wave(void)
{
	unsigned char i = 8;  //发送8个脉冲
	
	do
	{
		TX = 1;
		somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;		
		TX = 0;
		somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;		
	}
	while(i--);
}


void delayms(int ms)
{
	int i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}

void allinit()
{
	P2=0XA0;
	P0=0X00;//关闭蜂鸣器，继电器
	
	P2=0X80;
	P0=0XFF;//关闭LED灯
	
	P2=0XC0;
	P0=0XFF;//选择所有数码管
	P2=0XFF;
	P0=0XFF;//关闭所有数码管
}

void display1(uchar yi,uchar er)
{
		P2=0XC0;//打开位选573   U8
		P0=0X01;//选择第一个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[yi];
		delayms(1);
		
		P2=0XC0;//打开位选573   U8
		P0=0X02;//选择第二个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[er];
		delayms(1);
}	

void display2(uchar san,uchar si)
{
		P2=0XC0;//打开位选573   U8
		P0=0X04;//选择第三个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[san];
		delayms(1);
		
		P2=0XC0;//打开位选573   U8
		P0=0X08;//选择第四个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[si];
		delayms(1);
}

void display3(uchar wu,uchar liu)
{
		P2=0XC0;//打开位选573   U8
		P0=0X10;//选择第一个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[wu];
		delayms(1);
		
		P2=0XC0;//打开位选573   U8
		P0=0X20;//选择第一个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[liu];
		delayms(1);
}

void display4(uchar qi,uchar ba)
{
		P2=0XC0;//打开位选573   U8
		P0=0X40;//选择第一个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[qi];
		delayms(1);
		
		P2=0XC0;//打开位选573   U8
		P0=0X80;//选择第一个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[ba];
		delayms(1);
}























