//================Serial communication
#include "STC15F2K60S2.h"
#include "intrins.h"
#include "String.h"

typedef unsigned int uint;
typedef unsigned char uchar;

void ALL_Init();
void Serial_Init();
void Send_String(uchar *p);
void Send_Byte(uchar byte);
void ExecuteCommand();
 
uchar array[]={"hello,world\n"};
uchar array2[] = {"one"};
uchar Recdate[4];
uchar conut;
uchar f;
// uchar i ;
void main()
{
	ALL_Init();
    Serial_Init();
    Send_String(array);
    while(1)
    {
       if(f == 1)
       {
           ExecuteCommand();
           f = 0;
       }
    }

}
void Time1() interrupt 4
{
    uchar *p ;
    p = Recdate;
    if(RI == 1)
    {
        while(1)
        {
            *p = SBUF ;//先接收
            RI = 0 ;//后清除标记
            if(*p == '\n')//如果是结束换行就停止接收
                break;//结束接收
            else
            {
                p++;//指向数组的下一位
                while(!RI);//等数据
            }
        }
        Send_String("already reception\r\n");
    }

}
void ExecuteCommand()
{
    if(Recdate[0] == '1')
    {
   	 Send_String("one\r\n");
    }
    else if(Recdate[0] == '2')
    {
        Send_String("tow\r\n");
    }
}

void Send_Byte(uchar byte)
{
    SBUF = byte;
    
    while(!TI) ;//TI串行接口发送完成中断标志位、需手动清零
    TI = 0;
}
void Send_String(uchar *p)
{
    while(*p != '\0')
    {
        Send_Byte(*p);
        p++;
    }

}
void Serial_Init()
{
    SCON = 0x50; //UART eight digit date
    AUXR |= 0x40; //timer one to 1T
    AUXR &= 0xfe; //Serial one choose one timer is baud rate happen
    TMOD &= 0x0f; //one timer is 16digit automation reload 
    TL1 = 0xe0;     //settings init
    TH1 = 0xfe;     //setting init 
    ET1 = 0;        //Stop one timer interrupt
    TR1 = 1;    //start one timer
    EA = 1;
    ES = 1;
}
 
void ALL_Init()
{	  	
	P2 = 0xa0; P0 = 0x00;
	P2 = 0x80; P0 = 0xff;
	P2 = 0xc0; P0 = 0xff;
	P2 = 0xff; P0 = 0xff;
}
 
 

 