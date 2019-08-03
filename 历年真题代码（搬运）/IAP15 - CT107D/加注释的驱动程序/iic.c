/*
  程序说明: IIC总线驱动程序（加注释版）
  软件环境: Keil uVision 5
  硬件环境: CT107单片机综合实训平台(12MHz)
  日    期: 2018-01-24
*/
#include "iic.h"

//void Delay10ms()		//EEPROM 使用
//{
//	unsigned char i, j;

//	i = 108;
//	j = 145;
//	do
//	{
//		while (--j);
//	} while (--i);
//}


//总线启动条件	1
void IIC_Start(void)
{
	SDA = 1;
	SCL = 1;
	somenop;
	SDA = 0;
	somenop;
	SCL = 0;
}

//总线停止条件	2
void IIC_Stop(void)
{
	SDA = 0;
	SCL = 1;
	somenop;
	SDA = 1;
}

//主机应答位控制 3
/*主机做的都是编程控制，从机做的都是自主控制，也可以说是硬件控制，如主机给应答信号是编程控制，
  但是从机给应答信号是硬件控制，我们只需要在 WaitAck() 中检测SCL为高电平期间，SDA保持低电平一
  些时间，即可判定从机给了主机应答信号。[高电平期间，快递车一直在行驶，快件儿必须待在车上，装卸必须在停车的情况下进行
*/
void IIC_MasterAck(unsigned char ackbit)	 //1代表想继续接收
{
	if(ackbit)
	{
		SDA = 0;
	}
	else
	{
		SDA = 1;
	}
	somenop;
	SCL = 1;
	somenop;
	SCL = 0;
	SDA = 1;
	somenop;
}

//等待应答	4
bit IIC_WaitAck(void) //返回一代表得到应答
{
    /*数据位有效性：SCL为高电平期间内，SDA必须先保持稳定，
	只有在时钟线为低电平期间，数据线的高电平或低电平状态才允许变化；*/
	SDA = 1;
	somenop;
	SCL = 1;
	somenop;
	if(SDA) //检测SDA数据线是否被拉低，若拉低返回 1，表示应答即继续接受数据；
	{
		SCL = 0;
		IIC_Stop();
		return 0;
	}
	else
	{
		SCL = 0;
		return 1;
	}
}

//通过I2C总线发送数据	5
void IIC_SendByte(unsigned char byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(byte&0x80) //1000 0000
		{
			SDA = 1;
		}
		else
		{
			SDA = 0;
		}
		somenop;
		SCL = 1;
		byte <<= 1;//数据移位可不可以放到最后？
		somenop;
		SCL = 0;//IIC进行写操作时，时钟线SCL要拉低，数据线SDA才允许变化。
	}
}

//从I2C总线上接收数据  6
unsigned char IIC_RecByte(void)
{
	unsigned char dat;
	unsigned char i;

	for(i=0;i<8;i++)
	{
		SCL = 1;//IIC读取的时候，要拉高SCL保持数据稳定。
		somenop;
		dat <<= 1;
		/* 如果数据线为高电平，说明有数据，或上0000 0001，取date的最后一位，
		而后date左移一位，向低位读*/
		if(SDA)
		dat |= 0x01;
		SCL = 0;
		somenop;
	}
	return dat;
}
/***********************************************************************************
//以下为自己需要写的程序部分: EEPROM
***********************************************************************************/
//向EEPROM里写入数据（地址+数据）
void Write_AT24C02(unsigned char add, unsigned char dat)
{
    IIC_Start(); //发送起始位
    IIC_SendByte(0xa0);//  ,发送从设备的地址1010  000和读/写0选择位；
    /*释放总线，等到EEPROM拉低总线进行应答；如果EEPROM接收成功，则进行应答；
    若没有握手成功或者发送的数据错误时EEPROM不产生应答，此时要求重发或者终止*/
    IIC_WaitAck();
    IIC_SendByte(add);//发送想要写入的内部寄存器地址；
    IIC_WaitAck();//EEPROM对其发出应答；
    IIC_SendByte(dat);//发送数据
    IIC_WaitAck();//EEPROM对其发出应答；
    IIC_Stop();//发送停止位
    Delay10ms();
    /*EEPROM收到停止信号后，进入到一个内部的写入周期，大概需要10ms，此间任何操作都不会被EEPROM响应；
    (因此以这种方式的两次写入之间要插入一个延时，否则会导致失败*/
}

//从EEPROM里读数据（地址）
unsigned char ReadByte_AT24C02(unsigned char add)
{
    unsigned char dat;
    IIC_Start();//发送起始位；
    IIC_SendByte(0xa0);// 1010  000 0激活该器件写操作，发送从机地址+读1/写0位
    IIC_WaitAck();
    IIC_SendByte(add);//发送内部寄存器地址；
    IIC_WaitAck();
    IIC_Start();//重新发送起始位，即restart；
    IIC_SendByte(0xa1);//1010 000 1，激活读操作,重新发送从机地址+读1/写0位；
    IIC_WaitAck();
    dat=IIC_RecByte();//读取数据
    /* 主机接收器在接收到最后一个字节后，也不会发出ACK信号。
    于是，从机发送器释放SDA线，以允许主机发出 stop 信号结束传输。*/
    IIC_MasterAck(0);
    IIC_Stop();// 发送停止位 

	  return dat;
}

///******************************************************************************************************
// 需要自己写的函数：ADC部分 AD转换，即模拟信号转数字信号
// ------------------------------------------------------------------------------------------------------
// 芯片： PCF8591
// PCF8591 是单电源，低功耗8 位CMOS 数据采集器件，具有4 个模拟输入AIN0~AIN3、一个输出AOUT和一个串行I2C 总线接口。
// 3 个地址引脚A0、A1 和A2 用于编程硬件地址，允许将最多8 个器件连接至I2C总线而不需要额外硬件。器件的地址、控制和数据
// 通过两线双向I2C总线传输。器件功能包括多路复用模拟输入、片上跟踪和保持功能、8位模数转换和8位数模拟转换。
// 最大转换速率取决于I2C总线的最高速率。
//*******************************************************************************************************/
///*该函数是初始化的，当使用AD转换的时候需要在main函数开始时调用*/
//void ADC_Init(unsigned char chanel)
//{
//	IIC_Start();          //IIC 启动信号
//	IIC_SendByte(0x90);   //1001 000 0 ；选中该器件，(前七位是地址，最后一位是R/~W，表示写)
//	IIC_WaitAck();        //等待应答
//	IIC_SendByte(chanel); //通过IIC发送通道，板上有4个模拟输入口，分别为0,1,2,3；设置哪一个模拟输入口就是根据这句代码,由控制字决定
//	IIC_WaitAck();        //等待应答
//	IIC_Stop();           //IIC停止信号
//	Delay10ms();          //等待10ms
//}

///*读取AD转换后的数值，这个函数直接调用就可以了，函数内部如何实现不用管，
//但是需要注意的是：该函数扫描调用最好是100ms。*/
//unsigned char ADC_Read()
//{
//	unsigned char temp;
//	IIC_Start();        //IIC启动信号
//	IIC_SendByte(0x91); //1001 000 1;选中该器件(前七位是地址，最后一位是R/~W，表示读)
//	IIC_WaitAck();     //等待应答
//	temp=IIC_RecByte(); //通过IIC读取采集的值
//	IIC_MasterAck(0);         //通过IIC发送应答
//	IIC_Stop();
//	return temp;
//}

///*************************************************************************************************
// AD转换函数二合一版

//函数： bit ADC_Read(unsigned char chanel, unsigned *dat)
//参数： chanel,ADC控制字节； *dat 指针变量，用于存放形参变量的地址
//返回：返回 1 执行成功，0 失败
//描述：读取PCF8591的转换回的值
//***************************************************************************************************/
//bit ADC_Read(unsigned char chanel, unsigned int *dat)
//{
//	IIC_Start();
//	IIC_SendByte(0x90);
//	if(!IIC_WaitAck())
//	{
//		return 0;
//	}
//	IIC_SendByte(chanel);
//	IIC_MasterAck(0);

//	IIC_Start();
//	IIC_SendByte(0x91);
//	if(!IIC_WaitAck())
//	{
//		return 0;
//	}
//	*dat = IIC_RecByte();
//	IIC_MasterAck(0);
//	IIC_Stop();
//	return 1;
//}







///******************************************************************************************************************
//DAC输出
// ＤＡ转换即将从总线上接收到的数字量通过ＡＯＵＴ输出，该函数无返回值，有一个形参
// 输入参数： dat—— 输入进行数模转换的数据
// 输出参数： 无
//********************************************************************************************************************/
//bit DAC_Out(unsigned char dat)
//{
//	IIC_Start();
//	IIC_SendByte(0x90);
//	if(! IIC_WaitAck()){ return 0; }
//	IIC_SendByte(0x40);  //DAC输出模式 0100 0000 允许模拟输入，不自增单端
//	if(! IIC_WaitAck()){ return 0; }

//	IIC_SendByte(dat);
//	if(! IIC_WaitAck()){ return 0; }
//	IIC_Stop();
//	return 1;
////DA_led=0;     //转换成功显示
//}
