#include <stdio.h>
#include "board.h"
#include "vtimer.h"
#include <msp430.h>

#define MSEC ((uint32_t) 1000)
#define SEC ((uint32_t) 1000 * MSEC)

int main(void) {

	//set leds direction
	P1DIR |= BIT0;					// Set P1.0 to output direction
	P3DIR |= BIT6;

	//set clock output port
	P3DIR |= BIT0;	//P3.0 set to output
	P3SEL |= BIT0;	//P3.0 set to peripheral module function

	PMAPKEYID = PMAPPW;		//gain write access to port mapping registers
	P3MAP0 = PM_MCLK;	//send MCLK to P3.0
	PMAPKEYID = 0;

	P1OUT &= ~BIT0;	//turn off green led
	P3OUT |= BIT6;	//turn on red led


	while(1) {
		__delay_cycles(F_CPU);
//		vtimer_usleep(100 * MSEC);
		//toggle leds
		P1OUT ^= BIT0;				// Toggle P1.0 using exclusive-OR
		P3OUT ^= BIT6;
	}
	return 0;
}
