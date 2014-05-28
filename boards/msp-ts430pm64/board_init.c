  /*
   * board_init.c - Implementation of functions to init board.
   * Copyright (C) 2013 Milan Babel <babel@inf.fu-berlin.de>
   *
   * This source code is licensed under the GNU Lesser General Public License,
   * Version 2.  See the file LICENSE for more details.
   */

#include "cpu.h"
#include "board.h"
#include "kernel_internal.h"
#include "msp430.h"
#include "debug.h"

volatile static uint32_t __msp430_cpu_speed = MSP430_INITIAL_CPU_SPEED;

void msp430_init_dco(void);

typedef enum {
    MCLK_2MHZ_SCLK_1MHZ = 1000002uL,
    MCLK_4MHZ_SCLK_1MHZ = 1000004uL,
    MCLK_8MHZ_SCLK_1MHZ = 1000008uL,
    MCLK_8MHZ_SCLK_8MHZ = 8000000uL
}speed_t;

/*---------------------------------------------------------------------------*/
static uint8_t calc_umctl(uint16_t br) {
    // from TI slaa049
    register uint8_t CMOD = 256 * br - 256 * (br + 1) / 2;
    register uint8_t c = 0;
    register int i = 0;
    register uint8_t a = CMOD;
    a <<= 1;
    do {
        if( a & 0x80 ) {           // Overflow to integer?
            a = a - 128 + CMOD;    // Yes, subtract 1.000000
            c |= 0x80;
        }
        else {
            a += CMOD;              // No, add fraction
        }
        if( i == 7 ) {
            return c;
        }
        i++;
        c >>= 1;
    } while(1);

    return 0;
}

static void ports_init(void)
{
    // Port 1: LED (P1.0)
   P1OUT = 0x00;
   P1DIR = 0x01;
   P1SEL = 0x00;

}

void msp430_set_cpu_speed(uint32_t speed)
{

    dint();
    __msp430_cpu_speed = speed;
    msp430_init_dco();
 //   uint16_t br;

//    U0CTL = SWRST;		//i2c enable
//    U0CTL = SWRST | CHAR;          // i2c enable + 10-bit addressing
//    U0TCTL = SSEL1 | TXEPT;        // UCLK = SCLK
//    U0RCTL = 0;
    // activate
//    ME1 |= UTXE0 + URXE0;          // Enable USART0 TXD/RXD
//    br = (uint16_t)((__msp430_cpu_speed & 0xFFFFF0) / 115200uL);
//    UBR00  = br;                   // set baudrate
//    UBR10  = br>>8;
//    UMCTL0 = calc_umctl(br);       // set modulation

//    U0CTL &= ~SWRST; //i2c disable

    //URCTL0 |= URXEIE;            // allow chars to interrupt
//    IE1  |= URXIE0;                // enable rx interrupt
//    IFG1 &= ~UTXIFG0;
    eint();
}

/*---------------------------------------------------------------------------*/
void msp430_init_dco(void)
{
  /*----------------------- use external oszillator -------------------------*/
  uint16_t i;

  // Stop watchdog
  WDTCTL = WDTPW + WDTHOLD;

  DCOCTL = DCO0 | DCO1 | DCO2;	//set max DCO frequency
  BCSCTL1 = XT2OFF | RSEL0 | RSEL1 | RSEL2;

  // Wait for xtal to stabilize
  do {
    IFG1 &= ~OFIFG;                // Clear oscillator fault flag
    for (i = 0xFF; i > 0; i--);    // Time for flag to set
  }
  while ((IFG1 & OFIFG) != 0);     // Oscillator fault flag still set?
  switch (__msp430_cpu_speed) {
  case MCLK_2MHZ_SCLK_1MHZ:
      BCSCTL2  = (SELM_0 | DIVM_2) | (0x00 | DIVS_3);
      break;
  case MCLK_4MHZ_SCLK_1MHZ:
      BCSCTL2  = (SELM_0 | DIVM_1) | (0x00 | DIVS_3);
      break;
  case MCLK_8MHZ_SCLK_1MHZ:
      BCSCTL2 = SELM_0 | (0x00 | DIVS_3);
      break;
  default:
      BCSCTL2 = SELM_0 + 0x00;     // MCLK and SMCLK = internal DCOCLK
      break;
  }
}

void board_init(void)
{
    msp430_cpu_init();
    ports_init();

    LED_YELLOW_ON;

    msp430_set_cpu_speed(MCLK_8MHZ_SCLK_8MHZ);
}
