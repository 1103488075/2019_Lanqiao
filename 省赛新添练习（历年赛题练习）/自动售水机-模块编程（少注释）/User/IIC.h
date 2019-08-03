#ifndef _IIC_H_
#define _IIC_H_

#include "typedef.h"
#define somenop {_nop_();_nop_();_nop_();_nop_();_nop_();};
#define SlaveAddrW 0xa0
#define SlaveAddrR 0xa1

sbit SDA = P2^1;    //date
sbit SCL = P2^0;    //clock

void IIC_Start(void);
void IIC_Stop(void);
void IIC_Ack(uchar ackbit);
void IIC_SenByte(uchar byt);
bit IIC_WaitAck(void);
uchar IIC_RecByte(void);
uchar AD_Read(uchar add);

#endif

