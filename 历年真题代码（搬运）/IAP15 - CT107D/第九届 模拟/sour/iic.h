#ifndef _IIC_H
#define _IIC_H

#include "intrins.h"

#define somenop { unsigned char i=10; _nop_();_nop_();_nop_();_nop_();_nop_();while(i--);} //在AD转换中发现的
#define SlaveAddrW 0xA0
#define SlaveAddrR 0xA1
#define fun(x) (unsigned int)(5*x/256.0*100+2.5) //数字电压 x 转换为模拟电压的公式

//总线引脚定义
sbit SDA = P2^1;  /* 数据线 */
sbit SCL = P2^0;  /* 时钟线 */

//函数声明
void Delay10ms();//向EEPROM里写入数据时用到的

void IIC_Start(void);
void IIC_Stop(void);
void IIC_MasterAck(unsigned char ackbit);
void IIC_SendByte(unsigned char byt);
bit IIC_WaitAck(void);
unsigned char IIC_RecByte(void);

void Write_AT24C02(unsigned char add, unsigned char dat);
unsigned char ReadByte_AT24C02(unsigned char add);

//void ADC_Init(unsigned char chanel);
//unsigned char ADC_Read();

//bit ADC_Read(unsigned char chanel, unsigned int *dat); //AD 二合一

//bit DAC_Out(unsigned char dat);//DA输出


#endif
