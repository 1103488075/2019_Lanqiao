/*---------------------------------------------------------------------------------
使用时要在主函数对计时器1进行初始化
-------------------------------------------------------------------------------------*/
#ifndef _PWM_H_
#define _PWM_H_

#include<intrins.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

#define LED       P0               //定义LED接口
#define LED_ON()  LED = 0x00;      //所有LED亮   /* 可以定义具体输出管脚 */
#define LED_OFF() LED = 0xff;		//所有LED灭

#define PWM_LIMIT_MAX  99      //0~99等分情况下的占空比上下限
#define PWM_LIMIT_MIN  0



static uchar TimerConter = 0;      //定时器中断次数
static uchar PWMDirection = 0;     //占空比变化方向  1 ： 占空比减少  0： 占空比增加
static signed char PWMConter = 0;  //占空比     


void Timer1_Init()//200微秒@11.0592MHz
{
	TMOD &= 0x0f;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x47;		//设置定时初值
	TH1 = 0xff;		//设置定时初值
	TR1 = 1;		//定时器0开始计时
	ET1  = 1;
	EA = 1;
}


//每200us进入一次中断,占空比会在计数100次调整占空比，每个调整出的占空比会在计数的同时依次减一，减完后的剩余时间完成与之前相反的活动
void Timer1(void) interrupt 3
{
	static  signed char PWMConter_NOW = 0;
	TL1 = 0x47;		//设置定时初值
	TH1 = 0xff;		//设置定时初值

  if(++TimerConter >= 100)  //200us*100 调整一次占空比 占空比的上限必须小于 100，因为每个周期(2ms)的占空比必须在下一次调整前减完，也就是不能超过计数的最大值
	{
		TimerConter = 0;      //定时器中断计数值归零
		if((PWMConter <= PWM_LIMIT_MAX) && (0 ==PWMDirection ))    // 判断占空比是否小于上限并处于增加的方向
		{
			PWMConter++;
			if(PWMConter > PWM_LIMIT_MAX)
			{
				PWMDirection = 1;
				PWMConter = PWM_LIMIT_MAX;
			}
		}
		if((PWMConter >= PWM_LIMIT_MIN) && (1 == PWMDirection))    // 判断占空比是否大于下限并处于减小的方向
		{
			PWMConter--;
			if(PWMConter < PWM_LIMIT_MIN)
			{
				PWMDirection = 0;
				PWMConter = PWM_LIMIT_MIN;
			}
		}
		PWMConter_NOW = PWMConter;
	}
  
  if(PWMConter_NOW > 0)  //每次进入中断都会进行判断并执行
 	{
		LED_ON();         //低电平   |____
		PWMConter_NOW--;
	}
  else
	{
		LED_OFF();        //高电平 
	}		
}

#endif



