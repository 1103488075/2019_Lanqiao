#ifndef _keypad_h_
#define _keypad_h_

#define uchar unsigned char
#define uint unsigned int
#define gpio_key P3   // 矩阵键盘扫描端口定义 注意：端口扫描使用 #define

uchar key_value=16; //键值变量定义，不显示

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
			/*松手检测*/
			while(gpio_key!=0x0f); // 注意松手检测的位置
		}
	}
}
#endif