/*
  程序说明: 单总线驱动程序
  软件环境: Keil uVision 4.10
  硬件环境: CT107单片机综合实训平台
  日    期: 2011-8-9
*/

#include "onewire.h"
#include<intrins.h>

//单总线延时函数
void Delay_OneWire(unsigned int t) //延时 1us
{
  /*自增自减为 1 个机器周期，1T 模式下一个机器周期需要 1 个时钟周期，12T 需要 12 个时钟周期；
  比如对于常用的 12M晶振来说：12T模式，一个机器周期为 1us；1T模式，一个机器周期为1/12 us；
  时钟晶振的振荡频率为fosc，则振荡周期Tosc=（1/fosc）。如：晶振频率为12MHZ，则振荡周期Tosc=（1/12us）。
  STC15F2K60S2比89C51速度快了12倍，所以它运行12条指令才能延时为原来的 1 us；*/
  unsigned char i;
  while(t--)
  {
      for(i=0;i<12;i++);
  }
}

//DS18B20芯片初始化 [敲门说话--聆听声响--获知情况]  [人点烛,鬼吹灯]
bit Init_DS18B20(void)
{
	bit initflag = 0;
	DQ = 1; //DQ复位，不要也可行，因为上拉电阻的存在，总线一般属于高电平，处于空闲状态
	Delay_OneWire(12);  //稍作延时
	/*主机通过拉低总线至少 480us，以产生(Tx)复位脉冲。*/
	DQ = 0; //主机“敲门”，即控制器也就是单片机拉低总线     【人点烛】
	Delay_OneWire(80);  //精确延时，维持至少 480 us
	/*接着主机释放总线，并进入接收模式(Rx)。当总线被释放后，总线仿佛弹了回去，5K上拉电阻将单总线拉高。*/
	DQ = 1; //释放总线
	/*当单总线器件检测到上升沿后，延时16~60 us，接着通过拉低单总线60~240 us以产生应答脉冲*/
	Delay_OneWire(10);  //15~60us 的从机反应时间
	initflag = DQ;      //等待从机回应                     【鬼吹灯】
	Delay_OneWire(5);   //主机发送应答脉冲所需时间
    return initflag;
}

//通过单总线向DS18B20写一个字节 [ 指令都是一个字节 ]
void Write_DS18B20(unsigned char dat)  //每个写时隙需要 60 us
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;   //拉低总线
		_nop_();  //至少维持了1us，表示写时序(包括写0时序或写1时序)开始，1~15us的从机反应时间
		/*从字节的最低位开始传输；指令dat的最低位赋予给总线,
		必须在拉低总线后的15us内, 因为15us后DS18B20会对总线采样。*/
		DQ = dat&0x01;   //取出最低位
		Delay_OneWire(5);//必须让写时序至少持续60~45 us，等待从机采样
		DQ = 1;  //写完后必须释放总线
		dat >>= 1;
	}
	Delay_OneWire(5);
}

//从DS18B20读取一个字节, 读时隙也为60 us ，但主机必须在读时隙的前15 us内完成采样
unsigned char Read_DS18B20(void)
{
	unsigned char i;
	unsigned char dat;

	for(i=0;i<8;i++)
	{
		DQ = 0;    //将总线拉低，要在1us之后释放总线；主机采样在15us以内，单片机要在此下降沿后的15us内读数据才会有效。
		_nop_(); //至少维持了1~15 us,表示读时序开始
		dat >>= 1;//让从总线上读到的位数据，依次从高位移动到低位 /* 1xxx xxxx --> 21xx xxxx --> 321x xxxx -->...--->8765 4321 */
		DQ = 1;    //释放总线，此后从机 DS18B20会控制总线,把数据传输到总线上
                    //延时7us,此处参照推荐的读时序图，尽量把控制器采样时间放到读时序后的15us内的最后部分
		if(DQ)       //控制器进行采样
		{
			dat |= 0x80;
		}
		Delay_OneWire(5);//此延时不能少，确保读时序的长度60us。
	}
	return dat;
}

/******************************************************************************
小数时返回值为 float, 主函数调用时用 uint
*******************************************************************************/

unsigned char Temper_Read()
{
    unsigned char TL,TH;
	  char temp;            //整数
//	  unsigned int temp;    //小数
//	  float temperature;
    Init_DS18B20();       //DS18B20初始化
    Write_DS18B20(0xCC);  //跳过ROM的字节命令
    Write_DS18B20(0x44);  //开始转换思路
    Delay_OneWire(200);   //延时一段时间

    Init_DS18B20();      //再次初始化
    Write_DS18B20(0xcc);
    Write_DS18B20(0xbe); //读取指令
    TL=Read_DS18B20();   //读低八位
    TH=Read_DS18B20();   //读高8位
    //整数
	  temp=(TH<<4)|(TL>>4);
//    //小数部分	
//	  temp = (TH & 0x0f);
//    temp <<=8;
//    temp |=TL;
//	  temperature = temp*0.625; //选择精度，得到真实十进制温度值 //0.0625=xx, 0.625=xx.x, 6.25=xx.xx 
	  //整数
    return temp;
//		//小数
//		return temperature;
}
