#ifndef _IIC_H
#define _IIC_H

#include "Head.h"
void IIC_Start(void); 
void IIC_Stop(void);  
bit IIC_WaitAck(void);  
 
void IIC_SendByte(unsigned char byt); 
unsigned char IIC_RecByte(void); 
float Read_AD(uchar addr);

#endif