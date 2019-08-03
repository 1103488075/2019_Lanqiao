/*******************************************************************************  
* 文件名称：蓝桥杯单片机第九届省赛试题视频讲解配套程序
* 实验目的：彩灯控制器       
* 程序说明：如需了解有关本程序配套视频讲解，及比赛经验分享\
*					 欢迎访问淘宝店铺网址：shop117015787.taobao.com
* 日期版本：2019-1
*******************************************************************************/

#include<STC15F2K60S2.H>
#include<IIC.H>

uchar code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff}; 
uchar yi,er,san,si,wu,liu,qi,ba;
uint LED_tt=0,LED_Time=400,Set_tt=0,AD_tt=0;
uchar LED_n=0,Mode=1,Run=0,Set=0;
uchar AD=0;
uchar S4_Flag=0;
uchar Light=0,LED_T=0;

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
	Mode=EEPROM_read(0X00);delayms(5);
	LED_Time=EEPROM_read(0X01)*100;delayms(5);
	yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=11;ba=11;
	
	while(1)
	{
		keyscan();
		
		if((Set==0)&&(S4_Flag==1))
		{
			if(AD<64){yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=10;ba=1;}
			else if((AD>=64)&&(AD<128)){yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=10;ba=2;}
			else if((AD>=128)&&(AD<192)){yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=10;ba=3;}
			else if((AD>=192)&&(AD<256)){yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=10;ba=4;}
		}
		else if(Set==0)
		{
			yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=11;ba=11;
		}
		display1(yi,er);
		display2(san,si);
		display3(wu,liu);
		display4(qi,ba);
	}
}

void Time0() interrupt 1
{
	LED_tt++;
	Set_tt++;
	AD_tt++;
	
	if((LED_tt==1)&&(Run==1))
	{
		if(Mode==1)
		{
			P2=0X00;P0=0XFF;P2=0X80;P0=~(0X01<<LED_n);P2=0X00;
		}
		else if(Mode==2)
		{
			P2=0X00;P0=0XFF;P2=0X80;P0=~(0X80>>LED_n);P2=0X00;
		}
		else if(Mode==3)
		{
			P2=0X00;P0=0XFF;P2=0X80;
			if(LED_n==0)P0=0X7E;
			else if(LED_n==1)P0=0XBD;
			else if(LED_n==2)P0=0XDB;
			else if(LED_n==3)P0=0XE7;
			P2=0X00;
		}
		else if(Mode==4)
		{
			P2=0X00;P0=0XFF;P2=0X80;
			if(LED_n==0)P0=0XE7;
			else if(LED_n==1)P0=0XDB;
			else if(LED_n==2)P0=0XBD;
			else if(LED_n==3)P0=0X7E;
			P2=0X00;
		}
	}
	else if(LED_tt==Light)
	{
		P2=0X00;P0=0XFF;P2=0X80;P0=0XFF;P2=0X00;
	}
	else if(LED_tt==20)
	{
		LED_tt=0;LED_T++;
		if((LED_T*20)>=LED_Time)
		{
			LED_T=0;
			if(Mode==1){LED_n++;if(LED_n>=8)LED_n=0;}
			else if(Mode==2){LED_n++;if(LED_n>=8)LED_n=0;}
			else if(Mode==3){LED_n++;if(LED_n>=4)LED_n=0;}
			else if(Mode==4){LED_n++;if(LED_n>=4)LED_n=0;}	
		}		
	}
	
	if(Set_tt==800)
	{
		if(Set==1)
		{
			if(LED_Time>=1000){wu=LED_Time/1000;liu=LED_Time%1000/100;qi=LED_Time%100/10;ba=LED_Time%10;}
			else {wu=11;liu=LED_Time/100;qi=LED_Time%100/10;ba=LED_Time%10;}	
			yi=11;er=11;san=11;si=11;
		}
		else if(Set==2)
		{
			yi=10;er=Mode;san=10;si=11;wu=11;liu=11;qi=11;ba=11;
		}
	}
	else if(Set_tt==1600)
	{
		Set_tt=0;
		if(Set==1)
		{
			if(LED_Time>=1000){wu=LED_Time/1000;liu=LED_Time%1000/100;qi=LED_Time%100/10;ba=LED_Time%10;}
			else {wu=11;liu=LED_Time/100;qi=LED_Time%100/10;ba=LED_Time%10;}	
			yi=10;er=Mode;san=10;si=11;
		}
		else if(Set==2)
		{
			if(LED_Time>=1000){wu=LED_Time/1000;liu=LED_Time%1000/100;qi=LED_Time%100/10;ba=LED_Time%10;}
			else {wu=11;liu=LED_Time/100;qi=LED_Time%100/10;ba=LED_Time%10;}	
			yi=10;er=Mode;san=10;si=11;
		}
	}

	if(AD_tt==200)
	{
		AD_tt=0;
		AD=AD_read(0x03);
		if(AD<64)Light=2;//
		else if((AD>=64)&&(AD<128))Light=5;
		else if((AD>=128)&&(AD<192))Light=10;
		else if((AD>=192)&&(AD<256))Light=19;
	}	
}

void keyscan(void)
{
	if(P30==0)
	{
		delayms(5);
		if(P30==0)
		{
			LED_tt=0;
			if(Run==0){Run=1;LED_tt=0;LED_n=0;}
			else if(Run==1){Run=0;P2=0X80;P0=0XFF;}
		}
		while(!P30);
	}
	else if(P31==0)
	{
		delayms(5);
		if(P31==0)
		{
			if(Set==0)
			{
				Set=1;Set_tt=0;
				yi=10;er=Mode;san=10;si=11;
				if(LED_Time>=1000){wu=LED_Time/1000;liu=LED_Time%1000/100;qi=LED_Time%100/10;ba=LED_Time%10;}
				else {wu=11;liu=LED_Time/100;qi=LED_Time%100/10;ba=LED_Time%10;}	
			}
			else if(Set==1)
			{
				Set=2;Set_tt=0;
				yi=10;er=Mode;san=10;si=11;
				if(LED_Time>=1000){wu=LED_Time/1000;liu=LED_Time%1000/100;qi=LED_Time%100/10;ba=LED_Time%10;}
				else {wu=11;liu=LED_Time/100;qi=LED_Time%100/10;ba=LED_Time%10;}	
			}
			else if(Set==2)
			{
				Set=0;Set_tt=0;
				yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=11;ba=11;
				EEPROM_write(0X00,Mode);delayms(5);
				EEPROM_write(0X01,LED_Time/100);delayms(5);
			}
		}
		while(!P31);
	}
	else if(P32==0)
	{
		delayms(5);
		if(P32==0)
		{
			if(Set==1)
			{
				Mode=Mode+1;if(Mode>=4)Mode=4;
			}
			else if(Set==2)
			{
				LED_Time=LED_Time+100;if(LED_Time>=1200)LED_Time=1200;
			}
		}
		while(!P32);
	}
	else if(P33==0)
	{
		delayms(5);
		if(P33==0)
		{
			S4_Flag=1;
		}
	}
	
	if((S4_Flag==1)&&(P33==1))
	{
		S4_Flag=0;
		if(Set==1)
		{
			Mode=Mode-1;if(Mode<=1)Mode=1;
		}
		else if(Set==2)
		{
			LED_Time=LED_Time-100;if(LED_Time<=400)LED_Time=400;
		}
	}
}

void Timer0Init(void)		//1毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初值
	TH0 = 0xD4;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;
	EA=1;
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
	P0=0X01;
	P2=0XFF;
	P0=tab[yi];
	delayms(1);
	
	P2=0XC0;
	P0=0X02;
	P2=0XFF;
	P0=tab[er];
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
}


void delayms(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}