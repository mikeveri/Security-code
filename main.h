#ifndef _MAIN_H_
#define _MAIN_H_

#include <REG51.H>
#define OSC_FREQ (11059200UL)
#define OSC_PER_INST (12)

typedef unsigned char tByte ;
typedef unsigned int tWord ;
typedef unsigned long tLong ;

#define INTERRUPT_TIMER_0_OVERFLOW 1
#define INTERRUPT_TIMER_1_OVERFLOW 3
#define INTERRUPT_TIMER_2_OVERFLOW 5

#endif