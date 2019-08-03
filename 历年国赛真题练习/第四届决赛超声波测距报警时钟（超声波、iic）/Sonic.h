#ifndef _SONIC_H_
#define _SONIC_H_

#include "Head.h"

#define somenop2{_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); _nop_();}

sbit TX = P1^0;
sbit RX = P1^1;

extern uchar Distance;
extern uint t;
void send_wave(void);

uchar Read_Distance();


#endif 