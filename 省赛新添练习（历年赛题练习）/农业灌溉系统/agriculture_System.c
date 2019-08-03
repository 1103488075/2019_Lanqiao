#include "STC15F2K60S2.H"
#include "intrins.h"
#include "ds1302.h"
#include "iic.h"
typedef unsigned int uint;
typedef unsigned char uchar;

uchar code SMG[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99,
                    0x92, 0x82, 0xf8, 0x80, 0x90,
                    0xbf, 0xff};//10 = -
uchar yi = 0,er = 8,san = 10,si = 3,wu = 0,liu = 11,qi = 10,ba = 10;
uchar status = 0;//自动工作和手动工作状态
uchar S5 = 0,S4 = 0,S6 = 0,jia = 0,jian = 0;//S6按键加和减
uchar fazhi = 55;//阈值
uchar shidu = 50;
uchar shijian[7] ;
uchar ds[]={0x00,0x30,0x08,10,1,16};//初始化时间,十六进制编码写入
uchar DS_write[] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90};//写入时间时DS1302的地址
uchar DS_read[] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d, 0x8f, 0x91};//读取时间时要写入的地址
//uchar read_shijian[]={0};
void Delay2ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 22;
	j = 128;
	do
	{
		while (--j);
	} while (--i);
}
void Delay5ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 54;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}
void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 108;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
}


void INI_All()
{
    P2 = 0xa0; P0 = 0x00;//buzz
    P2 = 0x80; P0 = 0xfe;//LED
    P2 = 0xc0; P0 = 0xff;//weixuan
    P2 = 0xff; P0 = 0xff;//duanxuan
}
void display1(uchar yi,er)
{
    P2 = 0xc0; P0 = 0x01;
    P2 = 0xff; P0 = SMG[yi];
    Delay2ms();
    P2 = 0xc0; P0 = 0x02;
    P2 = 0xff; P0 = SMG[er];
    Delay2ms();
}
void display2(uchar san,si)
{
    P2 = 0xc0; P0 = 0x04;
    P2 = 0xff; P0 = SMG[san];
    Delay2ms();
    P2 = 0xc0; P0 = 0x08;
    P2 = 0xff; P0 = SMG[si];
    Delay2ms();
}
void display3(uchar wu, liu)
{
    P2 = 0xc0; P0 = 0x10;
    P2 = 0xff; P0 = SMG[wu];
    Delay2ms();
    P2 = 0xc0; P0 = 0x20;
    P2 = 0xff; P0 = SMG[liu];
    Delay2ms();
}
void display4(uchar qi, ba)
{
    P2 = 0xc0; P0 = 0x40;
    P2 = 0xff; P0 = SMG[qi];
    Delay2ms();
    P2 = 0xc0; P0 = 0x80;
    P2 = 0xff; P0 = SMG[ba];
    Delay2ms();
}
/********************************************************************/ 
/*单字节写入一字节数据*/
void Write_Ds1302_Byte(unsigned char dat) 
{
	unsigned char i;
	SCK = 0;
	for (i=0;i<8;i++) 
	{ 
		if (dat & 0x01) 	// 等价于if((addr & 0x01) ==1) 
		{
			SDA_SET;		//#define SDA_SET SDA=1 /*电平置高*/
		}
		else 
		{
			SDA_CLR;		//#define SDA_CLR SDA=0 /*电平置低*/
		}		 
		SCK_SET;        //拉高时钟，上升沿写入数据
		SCK_CLR;		//再拉低时钟，形成脉冲，完成一个位的操作
		dat = dat >> 1; 
	} 
}
/********************************************************************/ 
/*单字节读出一字节数据*/
unsigned char Read_Ds1302_Byte(void) 
{
	unsigned char i, dat=0;	
	for (i=0;i<8;i++)
	{	
		dat = dat >> 1;
		if (SDA_R) 	  //等价于if(SDA_R==1)    #define SDA_R SDA /*电平读取*/	
		{
			dat |= 0x80;
		}
		else 
		{
			dat &= 0x7F;
		}
		SCK_SET;//拉高时钟，为脉冲下降沿读出数据做准备
		SCK_CLR;//再拉低时钟，时钟下降沿读出，完成一个位的动作
	}
	return dat;//最后返回读到的字节数据
}

/********************************************************************/ 
/*向DS1302 单字节写入一字节数据*/
void Ds1302_Single_Byte_Write(unsigned char addr, unsigned char dat)
{ 

	RST_CLR;			/*RST脚置低，实现DS1302的初始化*/
	SCK_CLR;			/*SCK脚置低，实现DS1302的初始化*/

	RST_SET;			/*启动DS1302总线,RST=1电平置高 */
	addr = addr & 0xFE;	 
	Write_Ds1302_Byte(addr); /*写入目标地址：addr,保证是写操作,写之前将最低位置零*/	
	Write_Ds1302_Byte(dat);	 /*写入数据：dat*/
	RST_CLR;				 /*停止DS1302总线*/
}
/********************************************************************/ 
/*从DS1302单字节读出一字节数据*/
unsigned char Ds1302_Single_Byte_Read(unsigned char addr) 
{ 
	unsigned char temp;
 
	RST_CLR;			/*RST脚置低，实现DS1302的初始化*/
	SCK_CLR;			/*SCK脚置低，实现DS1302的初始化*/

	RST_SET;	/*启动DS1302总线,RST=1电平置高 */	
	addr = addr | 0x01;	 
	Write_Ds1302_Byte(addr); /*写入目标地址：addr,保证是读操作,写之前将最低位置高*/
	temp=Read_Ds1302_Byte(); /*从DS1302中读出一个字节的数据*/		
	RST_CLR;	/*停止DS1302总线*/
    SDA_CLR;                             //官方示例代码不完整，这里SDA应电平置低
	return temp;

}
void DS1302_Init()//初始化函数，要记要会写
{
        uchar i;
        Ds1302_Single_Byte_Write(0x8e,0x00);
        for(i=0; i<7 ;i++)
        {
					Ds1302_Single_Byte_Write(DS_write[i],ds[i]);	      	
        }
        Ds1302_Single_Byte_Write(0x8e,0x80);
}
void Key()
{

    if(P30 == 0)//S7
    {
        Delay5ms();
        if(P30 == 0)
        {
            if(status == 0)
            {
            status = 1;//手动工作模式
            P2 = 0x80; P0 = 0xfd;
            }
            else if(status == 1)
            {
            status = 0;
            P2 = 0x80; P0 = 0xfe;//自动工作模式,初始化为自动工作
            }
        }
        while(!P30);//判断是否松开按键
    }

    if(P31 == 0)
    {
        Delay5ms();
        if(P31 == 0)
        {
            if(status == 0)//自动工作状态
            {
                if(S6 == 0)
                {  
                   
                        S6 = 1;//进入阈值调整状态
                }
                else if(S6 == 1)
                {
             
                        S6 = 0;//退出
                }
              
            }
            if(status == 1)//自动工作状态
            {
                if(S6 == 0)
                {
                    S6 = 1;//关闭buzz提醒功能
                }
                else if(S6 == 1)
                {
                    S6 = 0;//打开buzz提醒功能
                }
            }
        }
        while(!P31);
    }

    if(P32 == 0)
    {
        Delay5ms();
        if(P32 == 0)
        {
            if(status == 0)//自动模式下+
            {
                jia = 1;
            }
            if(status == 1)//手动模式下打开灌溉
            {
                S5 = 1;
                S4 = 0;//S5按下之后S4按键清零，等待下一次按下
            }
        }
        while(!P32);
    }
    if(P33 == 0)
    {
        Delay5ms();
        if(P33 == 0)
        {
            if(status == 0)//自动模式下减
            {
                jian = 1;
            }
            if(status == 1)//手动模式下关闭灌溉
            {
                S4 = 1;
                S5 = 0;//S4按键被按下时S5按键清0，等待下一次按下
            }
        }
        while(!P33);
    }
 
}
//==============================IIC总线操作
void IIC_Start(void)//IIC开始总线
{
    SDA = 1;
    SCL = 1; 
    somenop;//空指令，延时几个机器周期
    SDA = 0; 
    somenop;
    SCL = 0;
}
void IIC_Stop()//IIC停止总线
{
    SDA = 0; SCL = 1;
    somenop; SDA = 1;
}
void IIC_MasterAck(uchar ackbit)//IIC_Ack应答位控制
{
    if(ackbit)
    SDA = 0;
    else
    SDA = 1;
    somenop;    SCL = 1;
    somenop;    SCL = 0;
                SDA = 1;
    somenop;
}
bit IIC_WaitAck(void)//等待答应
{
    SDA = 1; somenop;
    SCL = 1; somenop;
    if(SDA)
    {
        SCL = 0; IIC_Stop();
        return 0;
    }
    else
    {
        SCL = 0;
        return 1;
    }
}
void IIC_SendByte(uchar byt)//通过IIC总线发送数据
{
    uchar i;
    for(i = 0;i < 8;i++)
    {
        
        if (byt & 0x80)
        {
            SDA = 1;
        }
        else 
        {
            SDA = 0;
        }
        somenop; SCL = 1;
        byt <<= 1; somenop;
        SCL = 0;
    }
}
uchar IIC_RecByte(void)
{
    uchar da,i;
    for(i = 0;i < 8;i++)
    {
        SCL = 1; somenop;
        da <<= 1;
        if(SDA)
        da |= 0x01;
        SCL = 0;
        somenop;
    }
    return da;
}
//============IIC往EEPROM里写入数据
void Write_AT24C02(uchar add, uchar dat)//写入
{
    IIC_Start();//发送起始位
    IIC_SendByte(0xa0);//
    //等待答应，
    IIC_WaitAck();//等待答应
    IIC_SendByte(add);//发送想要写入的内部寄存器地址
    IIC_WaitAck();//等待答应
    IIC_SendByte(dat);//发送数据
    IIC_WaitAck();//等待答应
    IIC_Stop();
    //EEPROM收到停止信号后进入写入周期，需要10ms延时，否则失败
    Delay10ms();
}
//=============从EEPROM里读取数据(地址)
uchar ReadByte_AT24C02(uchar add)
{
    uchar dat;
    IIC_Start();//发送起始位;
    IIC_SendByte(0xa0);//激活该器件写操作，发送从机地址
    IIC_WaitAck();//等待答应信号
    IIC_SendByte(add);//发送内部寄存器地址
    IIC_WaitAck();//等待答应
    IIC_Start();//重新发送起始位
    IIC_SendByte(0xa1);//激活该操作，重新发送从机地址
    IIC_WaitAck();//等待答应
    dat = IIC_RecByte();//读出数据
    //主机接收器接收到最后一个字节后，不会发出ACK信号
    //于是从机发送器释放SDA线，以允许主机发出stop信号结束
    IIC_MasterAck(0);//IIC_Ack
    IIC_Stop();//停止发送位
    return dat;
}
//================ADC初始化
void ADC_Init(uchar chanel)
{
    IIC_Start();//启动
    IIC_SendByte(0x90);
    IIC_WaitAck();
    IIC_SendByte(chanel);
    IIC_WaitAck();
    IIC_Stop();
    Delay10ms();
}
//================读取AD转换后的值
uchar ADC_Read()
{
    uchar temp;
    IIC_Start();
    IIC_SendByte(0x91);
    IIC_WaitAck();
    temp = IIC_RecByte();
    IIC_MasterAck(0);
    IIC_Stop();
    return temp;
}
void main()
{
   // uchar t;
    INI_All();
    DS1302_Init();
  // t = ReadByte_AT24C02(0x00);
   //ADC_Init(0x03);
    while(1)
    {
       // shidu = ADC_Read();
       // shidu = shidu*100/255;
       //Write_AT24C02(0x00,t);
       Key();
       if(status == 0)//为自动工作模式
       {
           if(S6 == 1)//进入阈值调整界面
           {
               if(jia == 1)//阈值调整+
               { 
                  jia = 0;
                  fazhi = fazhi+1;
               }
               if(jian == 1)//阈值调整-
               {
                   jian = 0;
                   fazhi = fazhi-1;
               }
             
              yi = 10; er = 10;//阈值界面
              san = 11; si = 11; wu = 11; liu = 11; qi = fazhi/10;ba = fazhi%10;//切换为阈值界面
           }
           if(S6 == 0)//退出阈值调整界面
           {      
             
               
                yi = Ds1302_Single_Byte_Read(ds1302_hr_addr)/16;//从ds1302中获取小时
                er = Ds1302_Single_Byte_Read(ds1302_hr_addr)%16;
                san = 10;
                si = Ds1302_Single_Byte_Read(ds1302_min_addr)/16;//从ds1302中获取分钟
                wu = Ds1302_Single_Byte_Read(ds1302_min_addr)%16;
               
                liu = 10; 
                qi = shidu /10; ba = shidu%10;
           }
           if(shidu < fazhi)//湿度低于阈值，打开继电器
           {
               P2 = 0xa0; P0 = 0x10;
           }       
           else//湿度高于阈值，关闭
           {
               P2 = 0xa0; P0 = 0x00;
           }
       }
       if(status == 1)//切换为手动工作模式
       {
           if(S6 == 1)//关闭buzz
           {
               P2 = 0xa0; P0 = 0x00;
           }
           else if(S6 == 0)//允许buzz提醒
           {
               P2 = 0xa0; P0 = 0x40;//打开buzz 
           }
           if(S5 == 1)//打开灌溉
           {
               P2 = 0xa0; P0 = 0x10;
              // S5 = 0;
           }
           if(S4 == 1)//关闭灌溉
           {
               P2 = 0xa0; P0 = 0x00;
              // S4 = 0;
           }
          
       }
       
         display1(yi,er);
         display2(san,si);
         display3(wu,liu);
         display4(qi,ba);
 
    }

}