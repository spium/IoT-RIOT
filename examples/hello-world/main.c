#include <stdio.h>
#include "board.h"
#include "vtimer.h"
//#include "net_if.h"
#include <msp430.h>

#define MSEC ((uint32_t) 1000)
#define SEC ((uint32_t) 1000 * MSEC)

int main(void) {

//	int n = 0;
	while(1) {
		__delay_cycles(4444444);
//		vtimer_sleep(interval);

		//toggle leds
		LED_YELLOW_TOGGLE;
//		++n;
	}

//	P1OUT &= ~BIT0;	//turn off green led
//
//	int iface = net_if_init_interface(NET_IF_L3P_RAW, TRANSCEIVER_CC1100);
//
//	if(iface < 0) P3OUT |= BIT6;
//	else P1OUT |= BIT0;




	return 0;
}
