#ifndef _HEAD_H_
#define _HEAD_H_

#include "STC15F2K60S2.h"
#include "intrins.h"

						 
 typedef unsigned char uchar;
 typedef unsigned int uint;

 //extern uchar t;
 extern bit s_flag;
 extern uint intr ;	//timer0 value

 extern uint Distance[10];
 extern uint addr;//eeprom addr
 extern uchar i;  //s4 value
 extern uint zone;//sonic bad zone
#endif