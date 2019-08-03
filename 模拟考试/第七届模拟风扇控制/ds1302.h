#ifndef __DS1302_H
#define __DS1302_H

#include "Head.h"

void Write_Ds1302_Byte(unsigned  char temp);
void Write_Ds1302( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302 ( unsigned char address );
  void Write_Time();
  void Read_Time();
extern uchar Time[];

#endif
