#include "STC15F2K60S2.h"
typedef unsigned char uchar;
typedef unsigned int uint;

#define OW_SKIP_ROM 0xcc
#define DS18B20_CONVERT 0x44
#define DS18B20_READ 0xbe

sbit DQ = P1^4;

void Delay_OneWire(uint t);
void Write_DS18B20(uchar dat);
bit Init_DS18B20(void);
uchar Read_DS18B20(void);
uchar Use_DS18B20();

