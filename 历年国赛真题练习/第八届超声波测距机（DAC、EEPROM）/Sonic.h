#ifndef _SONIC_H_
#define _SONIC_H_

#include "Head.h"


#define somenop2 {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();}

sbit TX = P1^0;
sbit RX = P1^1;

void Send_Wave(void);

uint Read_Distance();

extern uint t;

extern uint SonicValue;


#endif
