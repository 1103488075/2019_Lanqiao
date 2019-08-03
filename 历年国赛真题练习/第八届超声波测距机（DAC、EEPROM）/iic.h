#ifndef _IIC_H
#define _IIC_H

#include "Head.h"

//º¯ÊýÉùÃ÷
void IIC_Start(void); 
void IIC_Stop(void);  
void IIC_Ack(bit ackbit); 
void IIC_SendByte(unsigned char byt); 
bit IIC_WaitAck(void);  
unsigned char IIC_RecByte(void); 

  uchar Read_AD(uchar addr);
  void Eeprom_Write(uchar addr,uchar dat);
  uchar Eeprom_Read(uchar addr);
#endif