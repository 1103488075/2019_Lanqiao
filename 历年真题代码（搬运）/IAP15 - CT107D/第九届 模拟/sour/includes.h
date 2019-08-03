#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#define uint unsigned int
#define uchar unsigned char

#include"STC15F2K60S2.h"
#include<stdio.h>
#include"intrins.h"
#include"allinit.h"
#include"smg.h"
#include"keypad.h"
//#include"ds1302.h"
//#include"iic.h"
//#include"onewire.h"
//#include"PWM.h"
#include"usart.h"

void sys_test();
void Delay500ms();
void Timer0();


#endif 