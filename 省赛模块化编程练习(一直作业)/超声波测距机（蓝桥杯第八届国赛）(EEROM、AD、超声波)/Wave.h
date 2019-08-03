#ifndef _WAVE_H_
#define _WAVE_H_

 #include "Hread.h"
#define somenop2 {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();}

sbit TX = P1^0;
sbit RX = P1^1;
extern uint Distance;
extern uint t;
void SendWave();

#endif 