#ifndef _keypad_h_
#define _keypad_h_

#include"includes.h"

#define uchar unsigned char
#define uint unsigned int
#define gpio_key P3   // 矩阵键盘扫描端口定义 注意：端口扫描使用 #define

sbit S7 = P3^0; //独立按键定义
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;



void Delay10ms();		//@11.0592MHz
void key_down();

#endif
