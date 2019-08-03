#include<stc15f2k60s2.h>
#include "intrins.h"
#include "DEPUTY.H"

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long
	
uchar code tab[]={0xc0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0Xbf,0XFF};//ROM
uchar dsbuff[8]={11,11,11,11,11,11,11,11};

uint i=0,t1,t2;
uint shumadeng=1;
uint qidong=0,shezhi=0;
ulong tim,time,moshi,t,tt,ttt,tttt,flag=0,fla=0;
uint discount,liandu,dengji;
uint time1,time2,time3,time4;
uint s5=0,s4=0,A=0xff;

void delayms(int ms);
void allinit(void);
void keyscan();
void Timer0Init(void);		//2毫秒@11.0592MHz
void Timer1Init(void);		//1微秒@11.0592MHz
void display();	  //数码管显示

void main()
{
	moshi=1;
	allinit();
	Timer0Init();
	Timer1Init();

  EEPROM_write(0X01,4);//可以写的最大的
  delayms(5);  
  EEPROM_write(0X02,5);//可以写的最大的
  delayms(5);	
	EEPROM_write(0X03,6);//可以写的最大的
  delayms(5);  
  EEPROM_write(0X04,8);//可以写的最大的
  delayms(5);
	
	time1=EEPROM_read(0x01);
	delayms(5);
	time2=EEPROM_read(0x02);
	delayms(5);
	time3=EEPROM_read(0x03);
	delayms(5);
	time4=EEPROM_read(0x04);
	delayms(5);
	
//		dsbuff[0]=10;dsbuff[1]=moshi;dsbuff[2]=10;dsbuff[3]=11;dsbuff[48]=11;dsbuff[5]=time/100;dsbuff[6]=time%100/10;dsbuff[7]=time%10;
	while(1)
	{
		if((shezhi==0)&&(P33==1))
		{
			if(tim<liandu) {P2=0x80;P0=A;}
		  else {P2=0x80;P0=0xff;}		
		}

		keyscan();
		
		if(moshi==1) time=time1;
		if(moshi==2) time=time2;
		if(moshi==3) time=time3;
		if(moshi==4) time=time4;
		
		if((shezhi==0)&&(P33==1))
		{ 
    	dsbuff[0]=11;dsbuff[1]=11;dsbuff[2]=11;dsbuff[3]=11;dsbuff[4]=11;dsbuff[5]=11;dsbuff[6]=11;dsbuff[7]=11;
		}
		
		if(shezhi==1) 
		{
			dsbuff[0]=10;dsbuff[1]=moshi;dsbuff[2]=10;dsbuff[3]=11;
			if(flag==1)
			{
				flag=0;
				if(fla==0) {dsbuff[4]=time/10;dsbuff[5]=time%10;dsbuff[6]=0;dsbuff[7]=0;fla=1;}
				else if(fla==1) {dsbuff[4]=11;dsbuff[5]=11;dsbuff[6]=11;dsbuff[7]=11;fla=0;}
			}
		}
		
		if(shezhi==2) 
		{
			dsbuff[3]=11;dsbuff[4]=time/10;dsbuff[5]=time%10;dsbuff[6]=0;dsbuff[7]=0;
			if(flag==1)
			{
				flag=0;
				if(fla==0) {dsbuff[0]=10;dsbuff[1]=moshi;dsbuff[2]=10;fla=1;}
				else if(fla==1) {dsbuff[0]=11;dsbuff[1]=11;dsbuff[2]=11;fla=0;}
			}
		}
		
		if(s5==1)
		{
			s5=0;
			if(shezhi==1)
			{
				if(moshi==1)
			 {	
					time1=time1+1;
			    if(time1==13) time1=4;			
				}
			 
				if(moshi==2)
			 {	
					time2=time2+1;
			    if(time2==13) time2=4;			
				}
			 
				if(moshi==3)
			 {	
					time3=time3+1;
			    if(time3==13) time3=4;			
				}
			 
				if(moshi==4)
			 {	
					time4=time4+1;
			    if(time4==13) time4=4;			
				}
			}
			
			if(shezhi==2)
			{
				moshi++;
				if(moshi==5) moshi=1;
				i=0;
			}		
		}
		
		if((shezhi==1)||(shezhi==2))
		{
			if(s4==1)
			{
				s4=0;
				if(shezhi==1)
				{
					if(moshi==1)
					{
						time1=time1-1;
						if(time1==3) time1=12;
					}
					
					if(moshi==2)
					{
						time2=time2-1;
						if(time2==3) time2=12;
					}
					
					if(moshi==3)
					{
						time3=time3-1;
						if(time3==3) time3=12;
					}
					
					if(moshi==4)
					{
						time4=time4-1;
						if(time4==3) time4=12;
					}
				}
				
				if(shezhi==2)
				{
					moshi--;
					if(moshi==0) moshi=4;
					i=0;
				}		
			}
		}
		
		
		if((shezhi==1)||(shezhi==2)) {P2=0x80;P0=0xff;}
		
		if((liandu>0)&&(liandu<64)) dengji=1;
		if((liandu>64)&&(liandu<128)) dengji=2;
		if((liandu>128)&&(liandu<192)) dengji=3;
		if((liandu>192)&&(liandu<256)) dengji=4;
	}
}

void keyscan()
{ 
	if(P30==0)
	{
		delayms(5);
		if(P30==0)
		{
			if(qidong==0) {qidong=1;}
			else if(qidong==1) {qidong=0;}
		}
		while(!P30);
	}
	if(P31==0)
	{
		delayms(5);
		if(P31==0)
		{
			if(shezhi==0) {shezhi=1;flag=0;fla=0;}    //shezhi=1;流转间隔。shezhi=2;运行模式。shezhi=0;数码全管熄灭。
			else if(shezhi==1) {shezhi=2;flag=0;fla=0;}
			else if(shezhi==2) 
					 {
						 shezhi=0;flag=0;fla=0;
						 if(moshi==1)
						 {
							 EEPROM_write(0X01,time1);//可以写的最大的
							 delayms(5);						 
						 }
	
						 else if(moshi==2)
						 {
							 EEPROM_write(0X02,time2);//可以写的最大的
							 delayms(5);						 
						 }
						 
						 	else if(moshi==3)
						 {
							 EEPROM_write(0X03,time3);//可以写的最大的
							 delayms(5);						 
						 }
						 
						 	else if(moshi==4)
						 {
							 EEPROM_write(0X04,time4);//可以写的最大的
							 delayms(5);						 
						 }
					 }
		}		
		while(!P31);
	}
	
	if(P32==0)
	{
		delayms(5);
		if(P32==0)
		{
			s5=1;
		}
		while(!P32);
	}
	
	if(P33==0)
	{
		delayms(5);
		if(P33==0)
		{
			s4=1;
			if(shezhi==0)
		  { 
//        dsbuff[0]=11;dsbuff[1]=11;dsbuff[2]=11;dsbuff[3]=11;dsbuff[48]=11;dsbuff[5]=11;
				dsbuff[6]=10;dsbuff[7]=dengji;
		  }
	 }
	 while(!P33);
	}
}

void Timer1Init(void)		//50微秒@11.0592MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xD7;		//设置定时初值
	TH1 = 0xFD;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	ET1=1;
	EA=1;
}

void timer1() interrupt 3
{
	tim++;
	ttt++;	
	
	if(tim>256) tim=0;
	
	if(ttt==100)     //重要，AD_read()，不要放在while(1)中。
	{
		ttt=0;
		liandu=AD_read(0x03);
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
	
	ET0=1;
	EA=1;
}

void time0() interrupt 1
{
	display();	
	t++;
	if(t==400)
	{
		t=0;
		flag=1;
	}
	
	if((qidong==1)&&(shezhi==0))
	{
		tt++;
		if(tt==(time*50))
		{
			tt=0;
			if(moshi==1)
			{
				P2=0x80;P0=0xfe;
				P0=_crol_(P0,i);
				i++;
				if(i==8) i=0;	
				if(P0==0xff) P0=0xfe;
			}
			
			if(moshi==2)
			{
				P2=0x80;P0=0x7f;
				P0=_cror_(P0,i);
				i++;
				if(i==8) i=0;	
				if(P0==0xff) P0=0x7f;
			}

			if(moshi==3)
			{
				P2=0x80;t1=0x7f;t2=0xfe;
				
				P0=_cror_(t1,i)&_crol_(t2,i);
				i++;
				if(i==4) i=0;
				if(P0==0xff) {t1=0x7f;t2=0xfe;}
			}
			
			if(moshi==4)
			{
				P2=0x80;t1=0xef;t2=0xf7;
				P0=_crol_(t1,i)&_cror_(t2,i);
				i++;
				if(i==4) i=0;	
				if(P0==0xff) {t1=0xef;t2=0xf7;}
			}
			A=P0;
		}
	}
}


void allinit(void)
{
	P2=0XA0;//打开控制蜂鸣器继电器573
	P0=0X00;//关闭蜂鸣器继电器
	
	P2=0XC0;//打开数码管位选
	P0=0XFF;//选择所有数码管
	P2=0XFF;//打开数码管段选
	P0=0XFF;//关闭所有数码管
	
	P2=0X80;//打开控制LED573
	P0=0XFF;//关闭所有LED灯
}


void delayms(int ms)
{
	int i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}

void display()	  //数码管显示
{
	P2=0xef;
	P0=0xff;
	P2=0x1f;

	P2=0xcf;
	P0=1<<discount;
	P2=0x1f;

	P2=0xef;
	P0=tab[dsbuff[discount]];
	P2=0x1f;

	if(++discount==8)
		discount = 0;
}

