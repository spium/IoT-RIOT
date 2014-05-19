#include <stdio.h>
#include "board.h"
#include "vtimer.h"
#include "net_if.h"
#include <msp430.h>

#define MSEC ((uint32_t) 1000)
#define SEC ((uint32_t) 1000 * MSEC)

int main(void) {

	//set leds direction
	P1DIR |= BIT0;					// Set P1.0 to output direction
	P3DIR |= BIT6;

	P1OUT &= ~BIT0;	//turn off green led
	P3OUT &= ~BIT6;	//turn on red led


	int n = 0;
	while(n < 3) {
		__delay_cycles(F_CPU/2);
//		vtimer_usleep(100 * MSEC);
		//toggle leds
		P1OUT ^= BIT0;		// Toggle P1.0 using exclusive-OR
		++n;
	}

	P1OUT &= ~BIT0;	//turn off green led

	int iface = net_if_init_interface(NET_IF_L3P_RAW, TRANSCEIVER_CC1100);

	if(iface < 0) P3OUT |= BIT6;
	else P1OUT |= BIT0;




	return 0;
}
