/*---------------------------------------------------------------------------------
使用时要在主函数对计时器1进行初始化
-------------------------------------------------------------------------------------*/
#ifndef _PWM_H_
#define _PWM_H_

#include"STC15F2K60S2.h"
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


void Timer1_Init();/200微秒@11.0592MHz

#endif



