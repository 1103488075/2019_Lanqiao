#include "usart.h"

void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	TL1 = 0xE0;		//设定定时初值
	TH1 = 0xFE;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}

void SendData(unsigned char ch)		   //发送一个字节
{
	SBUF = ch;   //将待发送的数据放到发送缓冲器中
	while(!TI);  //等待发送完毕（未发送完时 TI 为 0，发送完之后 TI 为 1）
	TI = 0 ;     // 既然硬件置 1 了，那就必须软件清零
}
void SendString(unsigned char *s)		//发送一个字符串
{
	while(*s)  // 检测是否发送完毕（别忘了隐形的 \0）
	{
		SendData(*s++); // 调用函数一个字节一个字节发送
	}
}
