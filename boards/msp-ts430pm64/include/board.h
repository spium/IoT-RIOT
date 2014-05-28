
#ifndef _TS430_BOARD_H
#define _TS430_BOARD_H

#include "board-conf.h"

// for correct inclusion of <msp430.h>
#ifndef __MSP430F1611__
#define __MSP430F1611__
#endif

//MSB430 core
#define MSP430_INITIAL_CPU_SPEED    800000uL
#define F_CPU                       MSP430_INITIAL_CPU_SPEED
#define F_RC_OSCILLATOR             32768
#define MSP430_HAS_DCOR             1
#define MSP430_HAS_EXTERNAL_CRYSTAL 0

/* LEDs ports MSB430 */
#define LEDS_PxDIR P1DIR
#define LEDS_PxOUT P1OUT
#define LEDS_CONF_YELLOW		0x01

#define LED_YELLOW_OFF      LEDS_PxOUT &=~LEDS_CONF_YELLOW
#define LED_YELLOW_ON     LEDS_PxOUT |= LEDS_CONF_YELLOW
#define LED_YELLOW_TOGGLE     LEDS_PxOUT ^= LEDS_CONF_YELLOW

#include <msp430x16x.h>

typedef uint8_t radio_packet_length_t;

/** @} */
#endif // _TS430_BOARD_H
