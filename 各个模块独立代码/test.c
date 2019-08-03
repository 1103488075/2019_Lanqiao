#include<STC15F2K60S2.H>
#include<intrins.h>

#define uchar unsigned char 
#define uint unsigned int	
	
sbit DQ=P1^4;

uchar code tab[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF};
uchar yi,er,san,si,wu ,liu,qi,ba;

void delayms(int ms);
void Delay500us();
void Delay100us();	
void allinit();
void keyscan();
void dsinit();
uchar read();
uchar temget();
void write(uchar dat);
void rel(uchar dong);
void display1(uchar yi,uchar er);
void display2(uchar san,uchar si);
void display3(uchar wu,uchar liu);
void display4(uchar qi,uchar ba);

void main()
{
	uchar wendu;
	allinit();
	yi=11;er=11;san=11;si=11;wu=11;liu=0;qi=0;ba=0;
	while(1)
	{
		wendu=temget();
		
		liu=wendu/100;
		qi=wendu%100/10;
		ba=wendu%10;
		
		display1(yi,er);
		display2(san,si);
		display3(wu,liu);
		display4(qi,ba);
	}
}


uchar temget()
{
	uchar temp;
	
	uchar low,high;
	dsinit();
	write(0xcc);//忽略rom指令
	write(0x44);////温度转换指令
	Delay500us();	Delay500us();	

	dsinit();
	write(0xcc);
	write(0xbe);//忽略rom指令之后要跟着发送一条读取暂存器指令be
	
	low=read();
	high=read();
	//取出高8低8后，进行转换
	temp=high<<4;//0000 0101  =0101 0000
	temp |= (low>>4); //  1010 0110   0000 0110 | 0101 0000=0101 0110
	
	return temp;

}
uchar read()
{
	uchar i;
	uchar dat;
	
	for(i=0;i<8;i++)
	{
		DQ=0;
		_nop_();
		dat>>=1;
		DQ=1;
		if(DQ==1)
		{
			dat |= 0x80;// dat=dat|0x80;   0000 0000 | 1000 0000 =1000 0000
		}
		Delay100us();
	}
	return dat;
}

void write(uchar dat)
{
	uchar i;
	for(i=0;i<8;i++)//十六进制转换为二进制
{
		DQ=0;
        DQ=dat&0x01;//0100 0100 & 0000 0001 // 0000 0001
		Delay100us();
		DQ=1;
		dat>>=1;//dat=dat>>1;//1001 0000//0010 0001
	}
}

void dsinit()
{
	DQ=0;
	Delay500us();
	DQ=1;
	Delay500us();
}



void Delay100us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 2 ;
	j = 15  ;           
	do
	{
		while (--j);
	} while (--i);
}

void Delay500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}

void delayms(int ms)
{
	int i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}

void allinit()
{
	P2=0XA0;
	P0=0X00;//关闭蜂鸣器，继电器
	
	P2=0X80;
	
	P0=0XFF;//关闭LED灯
	P2=0XC0;
	P0=0XFF;//选择所有数码管
	P2=0XFF;
	P0=0XFF;//关闭所有数码管
}

void display1(uchar yi,uchar er)
{
		P2=0XC0;//打开位选573   U8
		P0=0X01;//选择第一个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[yi];
		delayms(1);
		
		P2=0XC0;//打开位选573   U8
		P0=0X02;//选择第二个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[er];
		delayms(1);
}	

void display2(uchar san,uchar si)
{
		P2=0XC0;//打开位选573   U8
		P0=0X04;//选择第三个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[san];
		delayms(1);
		
		P2=0XC0;//打开位选573   U8
		P0=0X08;//选择第四个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[si];
		delayms(1);
}

void display3(uchar wu,uchar liu)
{
		P2=0XC0;//打开位选573   U8
		P0=0X10;//选择第一个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[wu];
		delayms(1);
		
		P2=0XC0;//打开位选573   U8
		P0=0X20;//选择第一个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[liu];
		delayms(1);
}

void display4(uchar qi,uchar ba)
{
		P2=0XC0;//打开位选573   U8
		P0=0X40;//选择第一个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[qi];
		delayms(1);
		
		P2=0XC0;//打开位选573   U8
		P0=0X80;//选择第一个数码管
		P2=0XFF;//打开段选573   U7
		P0=tab[ba];
		delayms(1);
}



