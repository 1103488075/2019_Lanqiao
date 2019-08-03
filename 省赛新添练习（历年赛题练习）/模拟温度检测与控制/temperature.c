#include "STC15F2K60S2.h"
#include "intrins.h"
#include "onewire.h"
typedef unsigned int uint;
typedef unsigned char uchar;
uchar code SMG[] = {0xc0, 0xf9, 0xa4, 0xb0,
                    0x99, 0x92, 0x82, 0xf8,
                    0x80, 0x90, 0xbf, 0xff};
uchar temperature = 31;//温度值
uchar yi = 10,er = 1,san = 10,si = 11;//数码管值
uchar wu = 11,liu = 11,qi = 11,ba = 11;
uchar key_value;//按键的值
bit SetFlag;//设置界面键
uint num ;//按键按下显示的值
uchar max = 30,min = 20;//温度最大最小值
uchar secsion;//现温度值处于的区间-0-1-2-
uint i;//记录中断值
uint j ;//刷新温度值
void Delay3ms();
void Delay5ms();
void Init_All();
void display1(uchar yi,er);
void display2(uchar san,si);
void display3(uchar wu,liu);
void display4(uchar qi,ba);
void Kye_Scan16();
void init_time();
uchar Temper_Read();
void main()
{
    Init_All();
	init_time();
    temperature = Temper_Read();
    yi = 10,er = secsion,san = 10,si = 11;
    wu = 11, liu = 10, qi = temperature /10, ba = temperature%10;
    while(1)
    {
       // temperature = Temper_Read();
      
        Kye_Scan16();
        if(SetFlag == 1)//在设置界面
        {
            if(num == 0)//从键盘输入的数为空，数码管不显示
            {
                yi = 10;er = 11;san = 11;si = 11;
                liu = 10;qi = 11; ba = 11;
            }
            else if(num != 0)//不为空,显示
            {
                 max = (num/1000)*10+(num%1000/100);//从num中取出前两位的值做max
                 min = (num%100/10)*10+(num%10);//从num中取出后两位的值做min
                    if(max<min)//最大温度小于最小温度，LED亮
                    {
                    P2 = 0x80; P0 = 0xfd;
                    }
                  
                er = max/10;//显示
                san = max%10;
                qi = min/10;
                ba = min%10;
            }     
        }
        else if(SetFlag == 0)//第一界面
        {
                yi = 10,er = secsion,san = 10,si = 11;
                wu = 11, liu = 10, qi = temperature /10, ba = temperature%10;
        }   	
        if(max>min&&SetFlag == 0)//关闭警告设置温度冲突的led
        {
            P2 = 0x80; P0 = 0xff;
        }
        if(temperature<min&&SetFlag == 0)//温度区间
            secsion = 0;
        else if(min<=temperature&&max>=temperature&&SetFlag == 0)//温度区间
            secsion = 1;
        else if(temperature>max&&SetFlag == 0)//温度区间
            secsion = 2;

        display1(yi,er);
        display2(san,si);
        display3(wu,liu);
        display4(qi,ba);
    }
}
void init_time()
{
    AUXR |= 0x80;
    TMOD &= 0xf0;
    TL0 = 0x00;
    TH0 = 0x28;
    TF0 = 0;
    TR0 = 1;
    EA = 1;
    ET0 = 1;
}
void Kye_Scan16()
{
    P42 = 0; P44 = 0;//P42 = P36pin，P44 = P37pin
    P3 = 0x0f;//低四位全1

    if(P3 != 0x0f)
    {
        Delay5ms();
        if(P3 != 0x0f)
        {
            P42 = 1;    P44 = 1;
            P3 = 0x30;//1111 0000
            //高四位为列扫描
            if((P3 == 0x30)&&(P44 == 0)&&(P42 == 1))//=0111 0000
                key_value = 0;
            if((P3 == 0x30)&&(P44 == 1)&&(P42 == 0))//=1011 0000
                key_value = 1;
            if((P3 == 0x10)&&(P44 == 1)&&(P42 == 1))//=1101 0000
                key_value = 2;
            if((P3 == 0x20)&&(P44 == 1)&&(P42 == 1))//=1110 0000
                key_value = 3;

            P42 = 0;   P44 = 0;
            P3 = 0x0f;//0000 1111
            switch(P3)//低四位为行扫描
            {
                case (0x0e): key_value += 0;break;
                case (0x0d): key_value += 4;break;
                case (0x0b): key_value += 8;break;
                case (0x07): key_value += 12;break;
            }
            if(key_value == 13)//进入设置界面
                SetFlag = ~SetFlag;
            if(SetFlag == 1)
            {
                switch(key_value)
                {
                    case (0):num = 0+num*10;break;
                    case (1):num = 1+num*10;break;
                    case (2):num = 2+num*10;break;
                    case (4):num = 3+num*10;break;
                    case (5):num = 4+num*10;break;
                    case (6):num = 5+num*10;break;
                    case (8):num = 6+num*10;break;
                    case (9):num = 7+num*10;break;
                    case (10):num = 8+num*10;break;
                    case (12):num = 9+num*10;break;
                    case (14):num = 0;
                } 
            }   		
            while(P3 != 0x0f);//松开检测
        }
    }
}
void Delay3ms()
{
    uchar i,j;
    _nop_();
    _nop_();    i = 33;
    j = 66;
    do
    {
        while(--j);
    }while(--i);
}
void Delay5ms()
{
    uchar i, j;
    i = 54; j = 199;
    do
    {
        while(--j);
    } while(--i);
}
void Init_All()
{
    P2 = 0xa0; P0 = 0x00;//buzz
    P2 = 0x80; P0 = 0xff;//LED
    P2 = 0xc0; P0 = 0xff;//weixuan
    P2 = 0xff; P0 = 0xff;//duanxuan
}
void display1(uchar yi,er)
{
    P2 = 0xc0; P0 = 0x01;
    P2 = 0xff; P0 = SMG[yi];
    Delay3ms();
    P2 = 0xc0; P0 = 0x02; 
    P2 = 0xff; P0 = SMG[er];
    Delay3ms();
}
void display2(uchar san,si)
{
    P2 = 0xc0; P0 = 0x04;
    P2 = 0xff; P0 = SMG[san];
    Delay3ms();
    P2 = 0xc0; P0 = 0x08;
    P2 = 0xff; P0 = SMG[si];
    Delay3ms();
}
void display3(uchar wu,liu)
{
    P2 = 0xc0; P0 = 0x10;
    P2 = 0xff; P0 = SMG[wu];
    Delay3ms();
    P2 = 0xc0; P0 = 0x20;
    P2 = 0xff; P0 = SMG[liu];
    Delay3ms();
}
void display4(uchar qi,ba)
{
    P2 = 0xc0; P0 = 0x40;
    P2 = 0xff; P0 = SMG[qi];
    Delay3ms();
    P2 = 0xc0; P0 = 0x80;
    P2 = 0xff; P0 = SMG[ba];
    Delay3ms();
}
void Delay_OneWire(uint t)//为延时1us
{
    /*1T模式机械周期需要一个时钟周期，12T需要12个时钟周期*/
    /*故1T单片机要延时1us时需多加12个时钟周期*/
    uchar i;
    while(t--)
    {
    for(i = 0;i < 12;i++);
    }
   
}
bit Init_DS18B20(void)//DS18B20初始化
{
    bit initflag = 0;
    DQ = 1;         //DQ复位、先置高
     Delay_OneWire(12); //稍作延时，拉低总线时至少延时48us
    DQ = 0;        //拉低DQ线
     Delay_OneWire(80);//精确延时，维持至少480us
    DQ = 1;//接着释放总线，进入接收模式
    /*当总线器件检测到上升沿后，延时16~60us，接着通过拉低单总线60~240产生答应脉冲*/
     Delay_OneWire(10);//15~6-us的从机反应时间
    initflag = DQ;//等待从机回应
    Delay_OneWire(5);//主机发送答应脉冲所需的时间
    return initflag;
}
void Write_DS18B20(uchar dat)//通过单总线向DS18B20写入一个字节
{//每个写间隙都要60us
    uchar i;
    for(i = 0;i < 8;i++)
    {
        DQ = 0;//拉低总线
        _nop_();//维持1us，表示写时序开始，1~15的从机反应时间
        //从字节的最低位开始传输，指令dat的最低位赋予总线
        //必须在总线后的15us内，因为15us后DS18B20会对总线采样
        DQ = dat & 0x01;//取出最低位
        Delay_OneWire(5);//必须让写时许持续60~45us，等待从机采样
        DQ = 1;//写完后释放总线
        dat >>= 1;
    }
    Delay_OneWire(5);
}
uchar Read_DS18B20(void)//从ds18B20读取一个字节，读间隙60us，但主机必须在读间隙前15us内完成采样
{
    uchar i; uchar dat;
    for(i = 0;i < 8;i++)
    {
        DQ = 0;//将总线拉低，要在1us后释放总线
        _nop_();//维持1~15us，表示读时序开始
        dat >>= 1;//依次从高位读到低位
        DQ = 1;//释放总线
        if (DQ)//控制器进行采样
        {
            dat |= 0x80;
        }
        Delay_OneWire(5);//延时不能少，确保读时序的长度60us
    }
    return dat;
}
uchar Temper_Read()
{
    uchar TL,TH;
    uchar temp;
    Init_DS18B20();//初始化
    Write_DS18B20(0xcc);//跳过rom字节命令
    Write_DS18B20(0x44);//开始转换
    Delay_OneWire(200);

    Init_DS18B20();//再次初始化
    Write_DS18B20(0xcc);//跳过rom
    Write_DS18B20(0xbe);//读取指令
    TL = Read_DS18B20();//读第八位
    TH = Read_DS18B20();//读高八位
    temp = (TH<<4)|(TL>>4);
    return temp;
}
void time_interrupt()   interrupt 1
{
    TL0 = 0x00;
    TH0 = 0x28;
    i++;
    j++;
        if(i == 160&&secsion == 0)//区间0，800ms
        {        P2 = 0xa0; P0 = 0x00;//关闭relay继电器
                 P2 = 0x80; P0 = 0xfe; i = 0; 
        }    
        if(i == 80&&secsion == 1)//区间1，400ms
        {   
                P2 = 0xa0; P0 = 0x00; //close relay
                P2 = 0x80; P0 = 0xfe;i = 0;
        }
        if(i == 40&&secsion == 2)//区间2，200ms
        {   
                P2 = 0xa0; P0 = 0x10;//open relay
                P2 = 0x80; P0 = 0xfe;i = 0;   
        }
        if(j == 500)
        {
  //          temperature = Read_DS18B20();
//            Delay_OneWire(20);
            j = 0;
            temperature = Temper_Read();
        }
}