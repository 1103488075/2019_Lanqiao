#ifndef _SMG_H_
#define _SMG_H_
#define uchar unsigned char
#define uint unsigned int
uint cnt;   //cnt为全局变量，放到最前面可以在别的文件中使用(秒表中用到的)
         //段码表   0    1    2    3    4    5    6    7    8    9    灭    -
uchar code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf};

uchar dspbuff[]={10,10,10,10,10,10,10,10};
uchar dspcom=0;

void display()
{
	//数码管消隐
	P2=(P2&0x1f)|0xe0;
	P0=0xff;
	P2&=0x1f;
  //位选
	P2=(P2&0x1f)|0xc0;
	P0=(1<<dspcom);
	P2&=0x1f;
	//段码输入
	P2=(P2&0x1f)|0xe0;
	P0=tab[dspbuff[dspcom]];
	P2&=0x1f;
	if(++dspcom==8)
		dspcom=0;
}

void smg_Timerinit()
{
	TMOD|= 0x01;
	TH0 = (65535-2000)/256; //2ms
	TL0 = (65535-2000)%256;
	ET0 = 1;
	TR0 = 1;
	EA = 1;
}

void smg_timer0()interrupt 1 //定时器0对应 interrupt 1
{
	cnt++;
	TH0=(65535-2000)/256;
	TL0=(65535-2000)%256;
	display();
}

#endif