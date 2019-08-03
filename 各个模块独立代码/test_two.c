#include "STC15F2K60S2.h"
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int
//共阳数码管、低电平点亮
uchar code tab[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92,
                    0x82, 0xf8, 0x80,0x90, 0xbf, 0xff};

uchar S7 = 0,S6 = 0,S5 = 0,S4 = 0;
uchar shijian[7];//储存获取的时间
uchar yi=2, er=0 ,san=1 , si=8, wu=10, liu=1, qi=1, ba=10;

sbit CE = P1^3; //RST
sbit IO = P2^3; //IO 
sbit SCLK = P1^7 ;   //SCLK
uchar code ds[] = {0, 47, 22, 7, 11, 4, 18};
//秒  分钟  小时  日期  月份  星期 年份

void delay(uint ms)
{
    uint i,j;
    for(i = ms; i>0; i--)
    for(j = 114; j>0; j--);
}
//==============LED函数
void LED_blibli()
{
    uchar i ;
    P2 = 0x80;//打开led灯573
    P0 = 0xfe;//给led灯赋值1111 1110
    for(i = 0; i<7; i++)
    {
        P0 = _crol_(P0,1);
        delay(500);
    }
    for(i = 0; i<7; i++)
    {
        P0 = _cror_(P0,1);
        delay(500);
    }
}
//========================8位数码管实现函数
void dispaly1(uchar yi,uchar er)//一二位
{
    P2 = 0xc0;//打开数码管位选573 u8芯片
    P0 = 0x01;//选择第一个数码管
    P2 = 0xff;//打开数码管段选573  u7芯片
    P0 = tab[yi];//数码管显示码值
    delay(5);

    P2 = 0xc0;
    P0 = 0x02;
    P2 = 0xff;
    P0 = tab[er];
    delay(5);
}
void dispaly2(uchar san,uchar si)//三四位
{
    P2 = 0xc0;//打开位选
    P0 = 0x04;//选中数码管
    P2 = 0xff;//打开段选
    P0 = tab[san];
    delay(5);
    P2 = 0xc0;
    P0 = 0x08;
    P2 = 0xff;
    P0 = tab[si];
    delay(5);
}
void dispaly3(uchar wu,uchar liu)//五六位
{
    P2 = 0xc0;
    P0 = 0x10;
    P2 = 0xff;
    P0 = tab[wu];
    delay(5);
    P2 = 0xc0;
    P0 = 0x20;
    P2 = 0xff;
    P0 = tab[liu];
    delay(5);
}
void dispaly4(uchar qi,uchar ba)//七八位
{
    P2 = 0xc0;
    P0 = 0x40;
    P2 = 0xff;
    P0 = tab[qi];
    delay(5);
    P2 = 0xc0;
    P0 = 0x80;
    P2 = 0xff;
    P0 = tab[ba];
    delay(5);
}

//================独立按键函数
void Key_Scan()
{
 
    if(P30 == 0)
    {
        delay(5);
        if(P30 == 0)
        {
            S7 = 1;
            
				
            LED_blibli();
        }
       while(!P30);
    }
    else if(P31 == 0)
    {  
        delay(5);
        if(P31 == 0)
         {   
             S6 = 1;
            LED_blibli();
         }
            while(!P31);
    }
    else if(P32 == 0)
    {
        delay(5);
        if(P32 == 0)
          {  
              S5 = 1;
              P0 = 0xfb; 
          }
            while(!P32);
    }
    else if(P33 == 0)
    {
        delay(5);
        if(P33 == 0)
          {  
              S4 = 1;
              P0 = 0xf7;
          }
            while(!P33);
    }
    
}

//========================矩阵键盘函数
/*
void Key_Scan16()
{
    uchar temp;
    P2 = 0x80;P0 = 0xff;//打开led灯573寄存器

    P44 = 0;P42 = 1;   //转接板的P36、P37位P42、P44
    P3 = 0x7f;temp = P3;
    temp = temp&0x0f;   //1111 1101&0000 1111 = 0000 1101
    if(temp != 0x0f)
    {   
        delay(5);
        temp = P3;
        temp = temp&0x0f;
        if(temp != 0x0f)
        {
            temp = P3;
            switch(temp)//扫描行
            {
             case 0x7e:P0 = 0xfe;break;//1111 1110
             case 0x7d:P0 = 0xfd;break;
             case 0x7b:num = 2;break;
             case 0x77:num = 3;break; 
            }
            while(temp != 0x0f)
            {
              temp = P3;
              temp = temp&0x0f;
            }
        }
    }
    P44 = 1;P42 = 0;P3 = 0xbf;//1011 111
    temp = P3;
    temp = temp&0x0f;//1111 1101 &0000 1111 = 0000 1101
    if(temp != 0x0f)
    {
        delay(5);
        temp = P3;
        temp = temp&0x0f;
        if(temp!= 0x0f)
        {
            temp = P3;
            switch(temp)
            {
                case 0xbe:num = 4;break;
                case 0xbd:num = 5;break;
                case 0xbb:num = 6;break;
                case 0xb7:num = 7;break;
            }
            while(temp != 0x0f)
            {
                temp = P3;
                temp = temp&0x0f;
            }
        }
    }

    P3 = 0xdf;P44 = 1;P42 = 1;
    temp = P3;
    temp = temp&0x0f;//1111 1101 &0000 1111 = 0000 1101
    if(temp != 0x0f)
    {
        delay(5);
        temp = P3;
        temp = temp&0x0f;
        if(temp != 0x0f)
        {
            temp = P3;
            switch(temp)
            {
                case 0xde:num = 8;break;
                case 0xdd:num = 9;break;
                case 0xdb:num = 10;break;
                case 0xd7:num = 11;break;
            }
            while(temp!= 0x0f)
            {
                temp = P3;
                temp = temp&0x0f;
            }
        }
    }
    P3 = 0xef;P44 = 1;P42 = 1;//1101 1111
    temp = P3;
    temp = temp&0x0f;//1111 1101&0000 1111 = 0000 1101
    if(temp!=0x0f)
    {
        delay(5);
        temp = P3;
        temp = temp&0x0f;
        if(temp!=0x0f)
        {
            temp = P3;
            switch(temp)
            {
                case 0xee:num = 12;break;
                case 0xed:num = 13;break;
                case 0xeb:num = 14;break;
                case 0xe7:num = 15;break;
            }
            while(temp != 0x0f)
            {
                temp = P3;
                temp = temp&0x0f;
            }
        }
    }

}
*/
//====================开发板初始化函数
void  allinit(void)
{
    P2 = 0xa0;//打开控制蜂鸣器和继电器573
    P0 = 0x00;//关闭蜂鸣器和继电器
    P2 = 0xc0;//打开数码管位选
    P0 = 0xff;//选择所有数码管
    P2 = 0xff;//打开数码管段选
    P0 = 0xff;//关闭所有数码管段选
    P2 = 0x80;//打开控制LED灯的573
    P0 = 0xff;//关闭所有LED灯1111 1111
}
//==============================================DS1302
  void writebyte(uchar dat)//写字节
 {
     uchar i;
     for(i = 0; i<8; i++)
     {
         SCLK = 0;//初始时钟线置零
         IO = dat&0x01;//取最低为，1302的数据和地址都是从最低位传输
         SCLK = 1;//置高，上升沿，IO的数据被传输
         dat>>= 1;//数据右移一位，准备传输下一位数据
     }
 }
 
 void write(uchar add,uchar dat)//写操作
 {//在写操作里调用Writebyte函数
     uchar num;
     CE = 0;  SCLK =0;  CE = 1;//CE置1，传输开始
     writebyte(add);//传输命令字，要写入的时间/日历地址
     num = (dat/10<<4)|(dat%10);
     writebyte(num);//写入要修改的时间/日期
     CE = 0;//结束传输，CE置零
 }
 
 uchar read(uchar add)//读操作
 {//在读操作里调用writebyte函数，传入获取时间的地址和命令
     uchar i,temp;
     uchar dat1,dat2;
     CE = 0;  SCLK = 0;  CE = 1;//CE置1，传输开始
     writebyte(add);
     for(i = 0; i<8; i++)
     {
         SCLK = 0;//制造下降沿
         temp >>= 1;//将要返回的数据左移一位
         if(IO)
         {
             temp |= 0x80;//要传输数据的当前值置为1，否不是则为0
         }
         SCLK = 1;//拉高时钟线
     }
     IO = 0;
     dat1 = temp/16;//得到去除16进制个位部分的剩余数字
     dat2 = temp%16;//得到16进制个位部分的值
     temp = dat1*10+dat2;//将去除个位部分的值乘10加上个位部分的值
     return temp;
 }

void read_time()//读取时间
{ 
    uchar i; uchar add = 0x81;//0x81、83、85是读操作的储存地址
    write(0x8e, 0x00);//0x8e是写保护，0x00写入时间为空
    for(i = 0; i<7; i++)
    {
        shijian[i] = read(add);//将获取到的时间值赋值给数组
        add = add+2;//地址+2
    } 
    write(0x8e, 0x80);//0x80是写入秒
}
void dsinit()//DS1302初始化
 {
     uchar i;  uchar add = 0x80;
     write (0x8e, 0x00);//0x8e是写保护，写入一个时间
     for(i = 0; i<7; i++)
     {
         write(add, ds[i]);//写进初始时间
         add = add+2;//写操作的地址是0x80+2
     }
     write(0x8e, 0x80);//0x8e写保护，0x80是写入秒
 }

//===================主函数
void main()
{
    //必考内容：数码管、LED、独立按键/矩阵按键，独立按键居多
    allinit();
    dsinit();
    while(1)
    {
        read_time();
        yi = shijian[2]/10;//分解成小时
				er = shijian[2]%10;
        san = 10; 
				si = shijian[1]/10;// 分解成分钟
				wu = shijian[1]%10;
        liu = 10;
				qi = shijian[0]/10;  //分解成秒
				ba = shijian[0]%10;
        //Key_Scan();
			  dispaly1(yi,er);
        dispaly2(san,si);
        dispaly3(wu,liu);
        dispaly4(qi,ba);
    }
}
