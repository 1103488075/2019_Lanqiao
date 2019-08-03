#ifndef _keypad_h_
#define _keypad_h_

#define uchar unsigned char
#define uint unsigned int
#define gpio_key P3   // 矩阵键盘扫描端口定义 注意：端口扫描使用 #define

//sbit S7 = P3^0; //独立按键定义
//sbit S6 = P3^1;
//sbit S5 = P3^2;
//sbit S4 = P3^3;

bit SetFlag; //设置按钮标志位
uchar key_value=16; //键值变量定义，不显示,矩阵键盘与独立按键

uint TMAXTMIN = 0; //将用户输入的数值看为一个数

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

void key_down()
{
	//按键按下举证 1111 0000
	P44=0;P42=0;
	gpio_key=0x0f;
	if(gpio_key!=0x0f)
	{
		Delay10ms();//10ms 消抖
		if(gpio_key!=0x0f)
		{
			//列反转扫描初始化 1111 0000
			P42=1;P44=1;
			gpio_key=0x30;
			//列扫描判断
			if((gpio_key==0x30)&&(P44==0)&&(P42==1))
				key_value=0;
			if((gpio_key==0x30)&&(P44==1)&&(P42==0))
				key_value=1;
			if((gpio_key==0x10)&&(P44==1)&&(P42==1))
				key_value=2;
			if((gpio_key==0x20)&&(P44==1)&&(P42==1))
				key_value=3;
			//行反转扫描初始化 0000 1111
			P42=0;P44=0;
			gpio_key=0x0f;
			switch(gpio_key)
			{
				case(0x0e) : key_value +=0;break; //0000 1110               
				case(0x0d) : key_value +=4;break; //0000 1101
				case(0x0b) : key_value +=8;break; //0000 1011
				case(0x07) : key_value +=12;break; //0000 0111
			}
			if(key_value == 13)  //放在此处改变标志位不会重影，类似于独立按键，标志位取反要放在按键函数里
				SetFlag = ~SetFlag;
			if(SetFlag == 1) //进入设置界面按键有效
			{
				switch(key_value)
				{
					case(0): TMAXTMIN = 0 + TMAXTMIN *10;break;
					case(1): TMAXTMIN = 1 + TMAXTMIN *10;break;
					case(2): TMAXTMIN = 2 + TMAXTMIN *10;break;
					case(4): TMAXTMIN = 3 + TMAXTMIN *10;break;
					case(5): TMAXTMIN = 4 + TMAXTMIN *10;break;
					case(6): TMAXTMIN = 5 + TMAXTMIN *10;break;
					case(8): TMAXTMIN = 6 + TMAXTMIN *10;break;
					case(9): TMAXTMIN = 7 + TMAXTMIN *10;break;
					case(10): TMAXTMIN = 8 + TMAXTMIN *10;break;
					case(12): TMAXTMIN = 9 + TMAXTMIN *10;break;
					case(14): TMAXTMIN = 0;
				}
		  }
			/*松手检测*/
			while(gpio_key!=0x0f);
		}			// 注意松手检测的位置
	}
}


//key_down()
//{
//	if(!S7)
//	{
//		Delay10ms();
//		if(!S7)
//		{
//			key_value = 7;
//			SetFlag7 = ~SetFlag7;
//		}
//		while(!S7);
//	}
//	if(!S6)
//	{
//		Delay10ms();
//		if(!S6)
//		{
//			key_value = 6;
//		}
//		while(!S6);
//	}
//	if(!S5)
//	{
//		Delay10ms();
//		if(!S5)
//		{
//			key_value = 5;
//			SetFlag5 = ~SetFlag5;
//		}
//		while(!S5);
//	}
//	if(!S4)
//	{
//		Delay10ms();
//		if(!S4)
//		{
//			key_value = 4;
//		}
//		while(!S4);
//	}
//}

#endif