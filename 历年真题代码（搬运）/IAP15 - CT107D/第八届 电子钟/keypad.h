#ifndef _keypad_h_
#define _keypad_h_

#include"ds1302.h"

#define uchar unsigned char
#define uint unsigned int
//#define gpio_key P3   // 矩阵键盘扫描端口定义 注意：端口扫描使用 #define

sbit S7 = P3^0; //独立按键定义
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;



bit SetFlag; //设置按钮标志位
bit STAR = 0;
uchar key_value=16; //键值变量定义，不显示,矩阵键盘与独立按键

uchar setnum7 = 0,setnum6 = 1; //按键 S7 S6 的按键功能顺序切换 
bit TIME_NOW_FLAG = 0,TIME_BUZZ_FLAG = 0; //时间设置标志位


uchar Time_DEC = 0; //BCD码转换为十进制时间 + 1
uchar Hourbuff,Minbuff,Secbuff;
uchar Hour_Flag,Min_Flag,Sec_Flag; //闹钟时间
uint Temper;

void Delay10ms()		//@11.0592MHz
{
	uchar i, j;

	i = 108;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
}

//void key_down()
//{
//	//按键按下举证 1111 0000
//	P44=0;P42=0;
//	gpio_key=0x0f;
//	if(gpio_key!=0x0f)
//	{
//		Delay10ms();//10ms 消抖
//		if(gpio_key!=0x0f)
//		{
//			//列反转扫描初始化 1111 0000
//			P42=1;P44=1;
//			gpio_key=0x30;
//			//列扫描判断
//			if((gpio_key==0x30)&&(P44==0)&&(P42==1))
//				key_value=0;
//			if((gpio_key==0x30)&&(P44==1)&&(P42==0))
//				key_value=1;
//			if((gpio_key==0x10)&&(P44==1)&&(P42==1))
//				key_value=2;
//			if((gpio_key==0x20)&&(P44==1)&&(P42==1))
//				key_value=3;
//			//行反转扫描初始化 0000 1111
//			P42=0;P44=0;
//			gpio_key=0x0f;
//			switch(gpio_key)
//			{
//				case(0x0e) : key_value +=0;break; //0000 1110               
//				case(0x0d) : key_value +=4;break; //0000 1101
//				case(0x0b) : key_value +=8;break; //0000 1011
//				case(0x07) : key_value +=12;break; //0000 0111
//			}
//			if(key_value == 13)  //放在此处改变标志位不会重影，类似于独立按键，标志位取反要放在按键函数里
//				SetFlag = ~SetFlag;
//			if(SetFlag == 1) //进入设置界面按键有效
//			{
//				switch(key_value)
//				{
//					case(0): TMAXTMIN = 0 + TMAXTMIN *10;break;
//					case(1): TMAXTMIN = 1 + TMAXTMIN *10;break;
//					case(2): TMAXTMIN = 2 + TMAXTMIN *10;break;
//					case(4): TMAXTMIN = 3 + TMAXTMIN *10;break;
//					case(5): TMAXTMIN = 4 + TMAXTMIN *10;break;
//					case(6): TMAXTMIN = 5 + TMAXTMIN *10;break;
//					case(8): TMAXTMIN = 6 + TMAXTMIN *10;break;
//					case(9): TMAXTMIN = 7 + TMAXTMIN *10;break;
//					case(10): TMAXTMIN = 8 + TMAXTMIN *10;break;
//					case(12): TMAXTMIN = 9 + TMAXTMIN *10;break;
//					case(14): TMAXTMIN = 0;
//				}
//		  }
//			/*松手检测*/
//			while(gpio_key!=0x0f);
//		}			// 注意松手检测的位置
//	}
//}


key_down()
{
	if(!S7)
	{
		Delay10ms();
		if(!S7)
		{
			key_value = 7;
			if(STAR_Flag == 1)
			{
				LED2(1);
				STAR = 0;
				STAR_Flag = 0;
			}
			TIME_NOW_FLAG = 1; //按下S7时间标志位 为 1
			TIME_BUZZ_FLAG = 0;
			setnum7++;
			if(setnum7 == 4 )
				setnum7 = 0;
			if(setnum7 == 0)
			{
				TIME_NOW_FLAG = 0; //归零后使用默认显示
		    DS1302_Init();
			}
		}
		while(!S7);
	}
	if(!S6)
	{
		Delay10ms();
		if(!S6)
		{
			key_value = 6;
			if(STAR_Flag == 1)
			{
				LED2(1);
				STAR = 0;
				STAR_Flag = 0;
			}
			TIME_NOW_FLAG = 0;
			TIME_BUZZ_FLAG = 1;
			setnum6++;
			if(setnum6 == 4)
				setnum6 = 0;
			if(setnum6 == 0)
				TIME_BUZZ_FLAG = 0; //归零后使用默认显示
		}
		while(!S6);
	}
	if(!S5)  // +
	{
		Delay10ms();
		if(!S5)
		{
			if(STAR_Flag == 1)
			{
				LED2(1);
				STAR = 0;
				STAR_Flag = 0;
			}
			if(TIME_NOW_FLAG == 1 )
			{
				switch(setnum7)
				{
					case(1): 
					{
						Time_DEC = (Hourbuff / 16) * 10 + (Hourbuff % 16);  //将当前读到的BCD码转换为10进制
						Time_DEC++;   //用十进制数显示加 1 动作
						Timeinit[2] = (Time_DEC / 10) * 16 + (Time_DEC % 10); 
					  if(Timeinit[2] == 0x24)  //数据的边界属性
					    Timeinit[2] = 0x00; 
						Hourbuff = Timeinit[2]; //将调整后的数值显示
					  break;
					}
					case(2): 
					{
						Time_DEC = (Minbuff / 16) * 10 + (Minbuff % 16); 
						Time_DEC++;
						Timeinit[1] = (Time_DEC / 10) * 16 + (Time_DEC % 10); 
					  if(Timeinit[1] == 0x60) 
					    Timeinit[1] = 0x00; 
						Minbuff = Timeinit[1]; //将调整后的数值显示
					  break;
					}
					case(3): 
					{
						Time_DEC = (Secbuff / 16) * 10 + (Secbuff % 16); 
						Time_DEC++;
						Timeinit[0] = (Time_DEC / 10) * 16 + (Time_DEC % 10); 
					  if(Timeinit[0] == 0x60) 
					    Timeinit[0] = 0x00; 
						Secbuff = Timeinit[0]; //将调整后的数值显示
					  break;
					}
				}
			}
			if(TIME_BUZZ_FLAG == 1 )
			{
				switch(setnum6)
				{
					case(1): 
					{
						Hour_Flag++;   //用十进制数显示加 1 动作
					  if(Hour_Flag == 24)  //数据的边界属性
					    Hour_Flag = 0; 
						Hourbuff = Hour_Flag; //将调整后的数值显示
					  break;
					}
					case(2): 
					{
						Min_Flag++;
					  if(Min_Flag == 60) 
					    Min_Flag = 0; 
						Minbuff = Min_Flag; //将调整后的数值显示
					  break;
					}
					case(3): 
					{
						Sec_Flag++;
					  if(Sec_Flag == 0x60) 
					    Sec_Flag = 0x00; 
						Secbuff = Sec_Flag; //将调整后的数值显示
					  break;
					}
				}
			}
		}
		while(!S5);
	}
	if(!S4)  // -
	{
		Delay10ms();
		if(!S4)
		{
			key_value = 4;
			if(STAR_Flag == 1)
			{
				LED2(1);
				STAR = 0;
				STAR_Flag = 0;
			}
			if(TIME_NOW_FLAG == 0 && TIME_BUZZ_FLAG == 0)
			{
				dspbuff[0] = 16; 
				dspbuff[1] = 16;
				dspbuff[2] = 16;
				dspbuff[3] = 16;
				dspbuff[4] = 16;
				dspbuff[5] = Temper / 10;
				dspbuff[6] = Temper % 10;
				dspbuff[7] = 12;
			}
			if(TIME_NOW_FLAG == 1 ) 
			{
				switch(setnum7)
				{
					case(1): 
					{
						Time_DEC = (Hourbuff / 16) * 10 + (Hourbuff % 16); 
						Time_DEC--;
						Timeinit[2] = (Time_DEC / 10) * 16 + (Time_DEC % 10); 
					  if(Time_DEC == -1) 
					    Timeinit[2] = 0x23; 
						Hourbuff = Timeinit[2]; //将调整后的数值显示
					  break;
					}
					case(2): 
					{
						Time_DEC = (Minbuff / 16) * 10 + (Minbuff % 16); 
						Time_DEC--;
						Timeinit[1] = (Time_DEC / 10) * 16 + (Time_DEC % 10); 
					  if(Time_DEC == -1) 
					    Timeinit[1] = 0x59; 
						Minbuff = Timeinit[1]; //将调整后的数值显示
					  break;
					}
					case(3): 
					{
						Time_DEC = (Secbuff / 16) * 10 + (Secbuff % 16); 
						Time_DEC--;
						Timeinit[0] = (Time_DEC / 10) * 16 + (Time_DEC % 10); 
					  if(Time_DEC == -1) 
					    Timeinit[0] = 0x59; 
						Secbuff = Timeinit[0]; //将调整后的数值显示
					  break;
					}
				}
			}
			if(TIME_BUZZ_FLAG == 1 ) 
			{
				switch(setnum6)
				{
					case(1): 
					{ 
						Hour_Flag--;
					  if(Hour_Flag == -1) 
					    Hour_Flag = 23; 
						Hourbuff = Hour_Flag; //将调整后的数值显示
					  break;
					}
					case(2): 
					{
						Min_Flag--;
					  if(Min_Flag == -1) 
					    Min_Flag = 59; 
						Minbuff = Min_Flag; //将调整后的数值显示
					  break;
					}
					case(3): 
					{
						Sec_Flag--;
					  if(Sec_Flag == -1) 
					    Sec_Flag = 59; 
						Secbuff = Sec_Flag; //将调整后的数值显示
					  break;
					}
				}
			}
		}
		while(!S4);
	}
}

#endif