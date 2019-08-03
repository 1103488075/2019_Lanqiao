#include"STC15F2K60S2.h"
#include"allinit.h"
#include"smg.h"
#define uchar unsigned char
#define uint unsigned int

uint sec=23,min=59,hour=1; //这里的cnt的范围需要是0~500，所以不能是uchar；

void main()
{
	allinit();      
  smg_Timerinit(); //调用数码管显示驱动 smg.h ，记得在主函数中加这个定时器T0初始化
	//开机显示 00-00-00
	dspbuff[7]=sec%10;
	dspbuff[6]=sec/10;
	dspbuff[5]=11;
	dspbuff[4]=min%10;
	dspbuff[3]=min/10;
	dspbuff[2]=11;
	dspbuff[1]=hour%10;
	dspbuff[0]=hour/10;
	while(1)
	{
		if(cnt==500) //500*2ms=1 s
		{
			cnt=0; 
			sec++;
			if(sec<60)   //计时1分钟
			{
			  dspbuff[6]=sec/10;
				dspbuff[7]=sec%10;
			}
			
			if(sec==60)  //1分钟满
			{
				// 秒数归零
				sec=0;
				// 满一分钟显示 00-01-00
				dspbuff[6]=sec/10;
				dspbuff[7]=sec%10;
				min++;
				dspbuff[3]=min/10;
				dspbuff[4]=min%10;
				if(min==60)
			  {
					dspbuff[3]=0;
					dspbuff[4]=0;
					hour++;
					dspbuff[0]=hour/10;
					dspbuff[1]=hour%10;
					// 分钟数归零
					min=0;
			  }
		  }
	  }	
	}		
}
