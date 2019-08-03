#ifndef _SONIC_H_
#define _SONIC_H_

#include "Head.h"

#define somenop2 {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); _nop_();}

 
extern unsigned int t;
sbit TX = P1^0;  //send pin
sbit RX = P1^1;  //	reception pin
extern  uint Distance;

void send_wave(void);	

uint ReadDistance();


#endif 



