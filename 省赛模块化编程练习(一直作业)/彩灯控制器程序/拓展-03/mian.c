/*******************************************************************************  
* 文件名称：蓝桥杯单片机第九届省赛试题视频讲解配套程序
* 实验目的：彩灯控制器       
* 程序说明：如需了解有关本程序配套视频讲解，及比赛经验分享\
*					 欢迎访问淘宝店铺网址：shop117015787.taobao.com
* 日期版本：2019-1
*******************************************************************************/

#include<STC15F2K60S2.H>
#include<IIC.H>

#define uchar unsigned char 
#define uint unsigned int	

uchar code tab[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF};
unsigned char Digbuf[8] = {0,1,2,3,4,5,6,7};
uchar S1_Flag=0,S2_Flag=0,S3_Flag=0,S4_Flag=0;
uchar Digcom=0;
uchar Key_temp=0xff,key=0xff;

uint LED_tt=0,LED_Time=400,Set_tt=0,AD_tt=0;
uchar LED_n=0,Mode=1,Run=0,Set=0;
uchar AD=0;
uchar Light=0,LED_T=0;

void delayms(int ms);
void allinit(void);
void keyscan(void);

void Timer0Init(void);
void Timer2Init(void);
void DIG(void);
void DIG_Close(void);

void main(void)
{
	allinit();
	Timer0Init();
	Timer2Init();
	EA=1;
	Mode=EEPROM_read(0X00);delayms(5);
	LED_Time=EEPROM_read(0X01)*100;delayms(5);
	while(1)
	{
		keyscan();
		if((Set==0)&&(S4_Flag==1))
		{
			DIG_Close();
			if(AD<64){Digbuf[6]=10;Digbuf[7]=1;}
			else if((AD>=64)&&(AD<128)){Digbuf[6]=10;Digbuf[7]=2;}
			else if((AD>=128)&&(AD<192)){Digbuf[6]=10;Digbuf[7]=3;}
			else if((AD>=192)&&(AD<256)){Digbuf[6]=10;Digbuf[7]=4;}
		}
		else if(Set==0)
		{
			DIG_Close();
		}		
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
			if(LED_Time>=1000){Digbuf[4]=LED_Time/1000;Digbuf[5]=LED_Time%1000/100;Digbuf[6]=LED_Time%100/10;Digbuf[7]=LED_Time%10;}
			else {Digbuf[4]=11;Digbuf[5]=LED_Time/100;Digbuf[6]=LED_Time%100/10;Digbuf[7]=LED_Time%10;}	
			Digbuf[0]=11;Digbuf[1]=11;Digbuf[2]=11;Digbuf[3]=11;
		}
		else if(Set==2)
		{
			Digbuf[0]=10;Digbuf[1]=Mode;Digbuf[2]=10;
			Digbuf[3]=11;Digbuf[4]=11;Digbuf[5]=11;Digbuf[6]=11;Digbuf[7]=11;
		}
	}
	else if(Set_tt==1600)
	{
		Set_tt=0;
		if(Set==1)
		{
			if(LED_Time>=1000){Digbuf[4]=LED_Time/1000;Digbuf[5]=LED_Time%1000/100;Digbuf[6]=LED_Time%100/10;Digbuf[7]=LED_Time%10;}
			else {Digbuf[4]=11;Digbuf[5]=LED_Time/100;Digbuf[6]=LED_Time%100/10;Digbuf[7]=LED_Time%10;}	
			Digbuf[0]=10;Digbuf[1]=Mode;Digbuf[2]=10;
		}
		else if(Set==2)
		{
			if(LED_Time>=1000){Digbuf[4]=LED_Time/1000;Digbuf[5]=LED_Time%1000/100;Digbuf[6]=LED_Time%100/10;Digbuf[7]=LED_Time%10;}
			else {Digbuf[4]=11;Digbuf[5]=LED_Time/100;Digbuf[6]=LED_Time%100/10;Digbuf[7]=LED_Time%10;}	
			Digbuf[0]=10;Digbuf[1]=Mode;Digbuf[2]=10;
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
	Key_temp=P3;                     // 1111 1110
	if( (Key_temp&0x0f) != 0x0f)			//	1111 1110 & 0000  1111  =0000 1110
 	{
		delayms(5);
		Key_temp=P3;
		if( (Key_temp&0x0f) != 0x0f)
		{
			key=Key_temp&0x0f;           //key = 0000 1110
			if(key==0x07)S4_Flag=1;
		}
	}
	
	if(((key&0x0f) !=0x0f)&&((Key_temp&0x0f) == 0x0f))
	{
		delayms(5);
		if( (Key_temp&0x0f) == 0x0f)
		{
			switch(key)
			{
				case 0x0e:
					LED_tt=0;
					if(Run==0){Run=1;LED_tt=0;LED_n=0;}
					else if(Run==1){Run=0;P2=0X80;P0=0XFF;}
					key=0xff;
				break;
				case 0x0d:
					if(Set==0){Set=1;Set_tt=0;DIG();}
					else if(Set==1){Set=2;Set_tt=0;DIG();}			
					else if(Set==2)
					{
						Set=0;Set_tt=0;DIG_Close();
						EEPROM_write(0X00,Mode);delayms(5);
						EEPROM_write(0X01,LED_Time/100);delayms(5);
					}					
					key=0xff;
				break;
				case 0x0b:
					if(Set==1)
					{
						Mode=Mode+1;if(Mode>=4)Mode=4;
					}
					else if(Set==2)
					{
						LED_Time=LED_Time+100;if(LED_Time>=1200)LED_Time=1200;
					}
				key=0xff;
				break;
				case 0x07:
					S4_Flag=0;
					if(Set==1)
					{
						Mode=Mode-1;if(Mode<=1)Mode=1;
					}
					else if(Set==2)
					{
						LED_Time=LED_Time-100;if(LED_Time<=400)LED_Time=400;
					}
					key=0xff;
				break;
			}	
		}
	}
}


void DIG(void)
{
	Digbuf[0]=10;Digbuf[1]=Mode;Digbuf[2]=10;Digbuf[3]=11;
	if(LED_Time>=1000){Digbuf[4]=LED_Time/1000;Digbuf[5]=LED_Time%1000/100;Digbuf[6]=LED_Time%100/10;Digbuf[7]=LED_Time%10;}
	else {Digbuf[4]=11;Digbuf[5]=LED_Time/100;Digbuf[6]=LED_Time%100/10;Digbuf[7]=LED_Time%10;}		
}

void DIG_Close(void)
{
	Digbuf[0]=11;Digbuf[1]=11;Digbuf[2]=11;Digbuf[3]=11;Digbuf[4]=11;Digbuf[5]=11;Digbuf[6]=11;Digbuf[7]=11;
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
}

void Timer2Init(void)		//1毫秒@11.0592MHz
{
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = 0xCD;		//设置定时初值
	T2H = 0xD4;		//设置定时初值
	AUXR |= 0x10;		//定时器2开始计时
	IE2 |= 0x04;    //开定时器2中断
}

//中断服务程序
void timer2int() interrupt 12           //中断入口
{
		P2|=0XC0;//打开位选573   U8
	  P2&=0XDF;
		P0=(1<<Digcom);
		P2|=0XE0;
		P2&=0XFF;//打开段选573   U7
		P0=tab[Digbuf[Digcom]];
		P2&=0X1F;
	 if(++Digcom==8)Digcom=0;
}

void delayms(int ms)
{
	int i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}

void allinit(void)
{
	P2|=0XA0;
	P2&=0XBF;
	P0=0X00;//关闭蜂鸣器，继电器
	
	P2|=0X80;
	P2&=0X9F;
	P0=0XFF;//关闭LED灯
	
	P2|=0XC0;//打开位选573   U8
	P2&=0XDF;
	P0=0XFF;//选择所有数码管
	P2|=0XE0;//打开位选573   U7
	P2&=0XFF;
	P0=0XFF;//关闭所有数码管
}
