/********* Delay C file for one milliseconds****/


#include <MAIN.H> //include main header file
#include <DELAY.H> //include delay header file
#define PRELOAD01 (65536 - (tWord)(OSC_FREQ / (OSC_PER_INST * 1020)))
#define PRELOAD01H (PRELOAD01 / 256)
#define PRELOAD01L (PRELOAD01 % 256)


void delay (const tWord delay_ms){
	static tWord x;
	tWord j;
	x = delay_ms;
		TMOD &=0xF0;
		TMOD |= 0x01;
	
			ET0=0;
	for (j =0; j<x ; j++ ){
		
			TH0 = PRELOAD01H;
			TL0 = PRELOAD01L;
			TF0 = 0;
			TR0 = 1;
		while (TF0 == 0);
		TR0=0;
	}
	
}