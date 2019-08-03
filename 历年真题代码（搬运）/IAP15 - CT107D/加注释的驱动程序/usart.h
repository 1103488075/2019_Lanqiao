#ifndef _USART_H_
#define _USART_H_

#include "STC15F2K60S2.h"
void UartInit(void);
void SendData(unsigned char ch);
void SendString(unsigned char *s);

#endif
