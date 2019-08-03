#ifndef _ONEWIRE_H
#define _ONEWIRE_H

#include "Hread.h" 

#define OW_SKIP_ROM 0xcc
#define DS18B20_CONVERT 0x44
#define DS18B20_READ 0xbe

//IC锟斤拷锟脚讹拷锟斤拷
sbit DQ = P1^4;

//锟斤拷锟斤拷锟斤拷锟斤拷
void Delay_OneWire(unsigned int t);
void Write_DS18B20(unsigned char dat);
bit Init_DS18B20(void);
unsigned char Read_DS18B20(void);
uchar Get_18B20();

#endif