#include <stdio.h>
#include "board.h"
#include <msp430.h>

#define MSEC ((uint32_t) 1000)
#define SEC ((uint32_t) 1000 * MSEC)

int main(void) {

	P1DIR |= 0x01;					// Set P1.0 to output direction
	P3DIR |= BIT6;

	P3OUT = BIT6;
	while(1) {
		__delay_cycles(F_CPU);
		P1OUT ^= 0x01;				// Toggle P1.0 using exclusive-OR
		P3OUT ^= BIT6;
	}
	return 0;
}
