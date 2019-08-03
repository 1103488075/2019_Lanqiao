/*******************************************************************************  
* 文件名称：蓝桥杯单片机第八届省赛试题视频讲解对应程序
* 实验目的：电子钟          
* 程序说明：如需了解有关本程序配套视频讲解，及比赛经验分享\
*					 欢迎访问淘宝店铺网址：shop117015787.taobao.com
* 日期版本：2017-12
*******************************************************************************/

#include<STC15F2K60S2.H>
#include "DEPUTY.H"

#define uchar unsigned char
#define uint unsigned int

uchar code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff,0xc6}; 
uchar yi,er,san,si,wu,liu,qi,ba;
extern unsigned char shijian[];
uchar Alarm_clock[3]={0,0,0};
uchar Time_set=5,Alarm_set=0;
uchar s4=0;
bit wendu=0;
uchar LED_shan=0;
uchar tt=0;
bit fla=0;
uint miao=0;

void allinit(void);
void delayms(uint ms);
void keyscan(void);
void display1(uchar yi,uchar er);
void display2(uchar san,uchar si);
void display3(uchar wu,uchar liu);
void display4(uchar qi,uchar ba);
void Timer0Init(void);		

void main(void)
{
	allinit();
	Timer0Init();
	DS_init();
	yi=0;er=8;san=10;si=3;wu=0;liu=10;qi=0;ba=0;
	while(1)
	{
		DS_get();
		if(wendu==0)
		{
			if(Time_set==5)
			{
				yi=shijian[2]/10;er=shijian[2]%10;san=10;si=shijian[1]/10;wu=shijian[1]%10;liu=10;qi=shijian[0]/10;ba=shijian[0]%10;
			}
			else if(Time_set==1)
			{
				if(shijian[0]%2==1){yi=shijian[2]/10;er=shijian[2]%10;san=10;si=shijian[1]/10;wu=shijian[1]%10;liu=10;qi=shijian[0]/10;ba=shijian[0]%10;}
				else {yi=11;er=11;san=10;si=shijian[1]/10;wu=shijian[1]%10;liu=10;qi=shijian[0]/10;ba=shijian[0]%10;}
			}
			else if(Time_set==2)
			{
				if(shijian[0]%2==1){yi=shijian[2]/10;er=shijian[2]%10;san=10;si=shijian[1]/10;wu=shijian[1]%10;liu=10;qi=shijian[0]/10;ba=shijian[0]%10;}
				else {yi=shijian[2]/10;er=shijian[2]%10;san=10;si=11;wu=11;liu=10;qi=shijian[0]/10;ba=shijian[0]%10;}
			}
			else if(Time_set==3)
			{
				if(shijian[0]%2==1){yi=shijian[2]/10;er=shijian[2]%10;san=10;si=shijian[1]/10;wu=shijian[1]%10;liu=10;qi=shijian[0]/10;ba=shijian[0]%10;}
				else {yi=shijian[2]/10;er=shijian[2]%10;san=10;si=shijian[1]/10;wu=shijian[1]%10;liu=10;qi=11;ba=11;}
			}	
			
			if(Alarm_set==5)
			{
				yi=Alarm_clock[2]/10;er=Alarm_clock[2]%10;san=10;si=Alarm_clock[1]/10;wu=Alarm_clock[1]%10;liu=10;qi=Alarm_clock[0]/10;ba=Alarm_clock[0]%10;
			}
			else if(Alarm_set==1)
			{
				if(shijian[0]%2==1){yi=Alarm_clock[2]/10;er=Alarm_clock[2]%10;san=10;si=Alarm_clock[1]/10;wu=Alarm_clock[1]%10;liu=10;qi=Alarm_clock[0]/10;ba=Alarm_clock[0]%10;}
				else {yi=11;er=11;san=10;si=Alarm_clock[1]/10;wu=Alarm_clock[1]%10;liu=10;qi=Alarm_clock[0]/10;ba=Alarm_clock[0]%10;}
			}
			else if(Alarm_set==2)
			{
				if(shijian[0]%2==1){yi=Alarm_clock[2]/10;er=Alarm_clock[2]%10;san=10;si=Alarm_clock[1]/10;wu=Alarm_clock[1]%10;liu=10;qi=Alarm_clock[0]/10;ba=Alarm_clock[0]%10;}
				else {yi=Alarm_clock[2]/10;er=Alarm_clock[2]%10;san=10;si=11;wu=11;liu=10;qi=Alarm_clock[0]/10;ba=Alarm_clock[0]%10;}
			}
			else if(Alarm_set==3)
			{
				if(shijian[0]%2==1){yi=Alarm_clock[2]/10;er=Alarm_clock[2]%10;san=10;si=Alarm_clock[1]/10;wu=Alarm_clock[1]%10;liu=10;qi=Alarm_clock[0]/10;ba=Alarm_clock[0]%10;}
				else {yi=Alarm_clock[2]/10;er=Alarm_clock[2]%10;san=10;si=Alarm_clock[1]/10;wu=Alarm_clock[1]%10;liu=10;qi=11;ba=11;}
			}
		}
		else if(wendu==1)
		{
			yi=11;er=11;san=11;si=11;wu=11;liu=Tempget()/10;qi=Tempget()%10;ba=12;
		}

		
		if((shijian[0]==Alarm_clock[0])&&(shijian[1]==Alarm_clock[1])&&(shijian[2]==Alarm_clock[2]))
		{
			LED_shan=1;tt=0;miao=0;
		}
		
		keyscan();
		
		display1(yi,er);
		display2(san,si);
		display3(wu,liu);
		display4(qi,ba);
	}
}

void keyscan(void)
{
	if(P30==0)
	{
		delayms(5);
		if(P30==0)
		{
			if(LED_shan==0)
			{
				if(Time_set==0){Time_set=5;Alarm_set=0;}
				else if(Time_set==5)Time_set=1;
				else if(Time_set==1)Time_set=2;
				else if(Time_set==2)Time_set=3;
				else if(Time_set==3)Time_set=5;
			}
			else if(LED_shan==1)
			{
				LED_shan=0;P2=0X80;P0=0XFF;
			}
		}
		while(!P30);
	}
	else if(P31==0)
	{
		delayms(5);
		if(P31==0)
		{
			if(LED_shan==0)
			{
				if(Alarm_set==0){Alarm_set=5;Time_set=0;}
				else if(Alarm_set==5)Alarm_set=1;
				else if(Alarm_set==1)Alarm_set=2;
				else if(Alarm_set==2)Alarm_set=3;
				else if(Alarm_set==3)Alarm_set=5;
			}
			else if(LED_shan==1)
			{
				LED_shan=0;P2=0X80;P0=0XFF;
			}
		}
		while(!P31);
	}
	else if(P32==0)
	{
		delayms(5);
		if(P32==0)
		{	
			if(LED_shan==0)
			{
				if(Time_set==1)
				{
					if(shijian[2]==23)shijian[2]=0;
				  else shijian[2]++;
					DS_init();
				}
				else if(Time_set==2)
				{
				  if(shijian[1]==59)shijian[1]=0;
					else shijian[1]++;DS_init();
				}
				else if(Time_set==3)
				{ 
					if(shijian[0]==59)shijian[0]=0;
					else shijian[0]++;DS_init();
				}
				else if(Alarm_set==1)
				{
					if(Alarm_clock[2]==23)Alarm_clock[2]=0;
					else Alarm_clock[2]++;
				}
				else if(Alarm_set==2)
				{
					if(Alarm_clock[1]==59)Alarm_clock[1]=0;
					else Alarm_clock[1]++;
				}
				else if(Alarm_set==3)
				{
					if(Alarm_clock[0]==59)Alarm_clock[0]=0;
					else Alarm_clock[0]++;
				}
			}
			else if(LED_shan==1)
			{
				LED_shan=0;P2=0X80;P0=0XFF;
			}
		}
		while(!P32);
	}
	else if(P33==0)
	{
		delayms(5);
		if(P33==0)
		{
			s4=1;
			if(Time_set==5)wendu=1;
		}
	}
	
	if((s4==1)&&(P33==1))
	{	
		s4=0;
		if(LED_shan==0)
		{
			wendu=0;
			if(Time_set==1)
			{
				if(shijian[2]==0)shijian[2]=23;
				else shijian[2]--;
				DS_init();
			}
			else if(Time_set==2)
			{
				if(shijian[1]==0)shijian[1]=59;
				else shijian[1]--;
				DS_init();
			}
			else if(Time_set==3)
			{
				if(shijian[0]==0)shijian[0]=59;
				else shijian[0]--;
				DS_init();
			}
			else if(Alarm_set==1)
			{
				if(Alarm_clock[2]==0)Alarm_clock[2]=23;
				else Alarm_clock[2]--;
			}
			else if(Alarm_set==2)
			{
				if(Alarm_clock[1]==0)Alarm_clock[1]=59;
				else Alarm_clock[1]--;
			}
			else if(Alarm_set==3)
			{
				if(Alarm_clock[0]==0)Alarm_clock[0]=59;
				else Alarm_clock[0]--;
			}
		}
		else if(LED_shan==1)
		{
			LED_shan=0;P2=0X80;P0=0XFF;
		}
	}
}


void Timer0Init(void)		//5毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x00;		//设置定时初值
	TH0 = 0x28;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	
	ET0=1;
	EA=1;
}


void time0() interrupt 1
{
	tt++;miao++;
	if((tt==40)&&(LED_shan==1))
	{
		tt=0;
		if(fla==0){fla=1;P2=0X80;P0=0XFE;}
		else if(fla==1){fla=0;P2=0X80;P0=0XFF;}
	}
	
	if(miao==1000)
	{
		miao=0;LED_shan=0;P2=0X80;P0=0XFF;
	}
}


void allinit(void)
{
	P2=0XA0;
	P0=0x00;//关闭蜂鸣器继电器
	
	P2=0X80;
	P0=0XFF;//关闭LED灯
	
	P2=0XC0;
	P0=0XFF;//选择所有数码管
	P2=0XFF;
	P0=0XFF;//关闭多有数码管	
}

void display1(uchar yi,uchar er)
{
	P2=0XC0;
	P0=0X01;//选择所有数码管
	P2=0XFF;
	P0=tab[yi];//关闭多有数码管	
	delayms(1);
	
	P2=0XC0;
	P0=0X02;//选择所有数码管
	P2=0XFF;
	P0=tab[er];//关闭多有数码管	
	delayms(1);
}

void display2(uchar san,uchar si)
{
	P2=0XC0;
	P0=0X04;//选择所有数码管
	P2=0XFF;
	P0=tab[san];//关闭多有数码管	
	delayms(1);
	
	P2=0XC0;
	P0=0X08;//选择所有数码管
	P2=0XFF;
	P0=tab[si];//关闭多有数码管	
	delayms(1);
}

void display3(uchar wu,uchar liu)
{
	P2=0XC0;
	P0=0X10;//选择所有数码管
	P2=0XFF;
	P0=tab[wu];//关闭多有数码管	
	delayms(1);
	
	P2=0XC0;
	P0=0X20;//选择所有数码管
	P2=0XFF;
	P0=tab[liu];//关闭多有数码管	
	delayms(1);
}

void display4(uchar qi,uchar ba)
{
	P2=0XC0;
	P0=0X40;//选择所有数码管
	P2=0XFF;
	P0=tab[qi];//关闭多有数码管	
	delayms(1);
	
	P2=0XC0;
	P0=0X80;//选择所有数码管
	P2=0XFF;
	P0=tab[ba];//关闭多有数码管	
	delayms(1);
	
	P2=0XC0;
	P0=0XFF;//选择所有数码管
	P2=0XFF;
	P0=0XFF;//关闭所有数码管	
}

void delayms(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}