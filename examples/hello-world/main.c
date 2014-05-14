#include <stdio.h>
#include "vtimer.h"
#include "board.h"
#include <msp430.h>

#define MSEC ((uint32_t) 1000)
#define SEC ((uint32_t) 1000 * MSEC)

int main(void) {
	volatile uint32_t i;
	P1DIR |= 0x01;					// Set P1.0 to output direction

	while(1) {
		for(i = 0; i < 100; ++i);


		P1OUT ^= 0x01;				// Toggle P1.0 using exclusive-OR
	}
	return 0;
}
