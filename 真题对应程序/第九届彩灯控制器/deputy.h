#ifndef __DEPUTY_H_
#define __DEPUTY_H_

void Write_Ds1302_Byte(unsigned  char temp);
void Write_Ds1302( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302 ( unsigned char address );
void DS_init(void);
void DS_get(void);

unsigned char rd_temperature(void);  
unsigned char Tempget(void);

#define uchar unsigned char
#define uint unsigned int

//º¯ÊýÉùÃ÷
void IIC_Start(void); 
void IIC_Stop(void);  
void IIC_Ack(bit ackbit); 
void IIC_SendByte(unsigned char byt); 
bit IIC_WaitAck(void);  
unsigned char IIC_RecByte(void); 
uchar AD_read(uchar add);
uchar EEPROM_read(uchar add);
void EEPROM_write(uchar add,uchar dat);

#endif