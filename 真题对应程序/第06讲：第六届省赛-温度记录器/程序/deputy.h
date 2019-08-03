#ifndef __DEPUTY_H_
#define __DEPUTY_H_

void Write_Ds1302_Byte(unsigned  char temp);
void Write_Ds1302( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302 ( unsigned char address );
void DS_init(void);
void DS_get(void);

unsigned char rd_temperature(void);  //; ;
unsigned char Tempget(void);


#endif