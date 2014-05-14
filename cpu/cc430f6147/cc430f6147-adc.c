/* *************************************************************************************************
 *
 *  Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *    Redistribution and use in source and binary forms, with or without
 *    modification, are permitted provided that the following conditions
 *    are met:
 *
 *      Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *      Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the
 *      distribution.
 *
 *      Neither the name of Texas Instruments Incorporated nor the names of
 *      its contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ************************************************************************************************/

/**
 * @ingroup cc430
 * @{
 */

/**
 * @file
 * @brief       eZ430 ADC driver
 *
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 *
 */


#include <legacymsp430.h>
#include "cpu.h"
#include "cc430f6147-adc.h"
#include "hwtimer.h"

uint16_t adc10_result;
uint8_t  adc10_data_ready;

/************************************************************************************************
 * @fn          adc12_single_conversion
 * @brief       Init ADC12. Do single conversion. Turn off ADC12.
 * @param       none
 * @return      none
 ************************************************************************************************/
uint16_t adc10_single_conversion(uint16_t ref, uint16_t sht, uint16_t channel)
{
    /* Initialize the shared reference module  */
    REFCTL0 |= REFMSTR + ref + REFON;           /* Enable internal reference (1.5V or 2.5V) */

    /* Initialize ADC10_A  */
    ADC10CTL0 = sht + ADC10ON;                  /* Set sample time  */
    ADC10CTL1 = ADC10SHP;                       /* Enable sample timer */
    ADC10MCTL0 = ADC10SREF_1 + channel;         /* ADC input channel   */
    ADC10IE = 0x001;                            /* ADC_IFG upon conv result-ADCMEMO */
    eINT();

    /* Wait 2 ticks (66us) to allow internal reference to settle */
    hwtimer_wait(2);

    /* Start ADC12 */
    ADC10CTL0 |= ADC10ENC;

    /* Clear data ready flag */
    adc10_data_ready = 0;

    /* Sampling and conversion start   */
    ADC10CTL0 |= ADC10SC;

    /* Wait until ADC10 has finished */
    hwtimer_wait(5);

    while (!adc10_data_ready);

    /* Shut down ADC12 */
    ADC10CTL0 &= ~(ADC10ENC | ADC10SC | sht);
    ADC10CTL0 &= ~ADC10ON;

    /* Shut down reference voltage   */
    REFCTL0 &= ~(REFMSTR + ref + REFON);

    ADC10IE = 0;

    /* Return ADC result */
    return adc10_result;
}

/*************************************************************************************************
 * @fn          ADC10ISR
 * @brief       Store ADC10 conversion result. Set flag to indicate data ready.
 * @param       none
 * @return      none
 *************************************************************************************************/
interrupt(ADC10_VECTOR) __attribute__((naked)) adc_isr(void)
{
    __enter_isr();

    switch(ADC10IV) {
        case  0:
            break;                           /* Vector  0:  No interrupt */
        case  2:
            break;                           /* Vector  2:  ADC overflow */
        case  4:
            break;                           /* Vector  4:  ADC timing overflow */
        case  6:
            /* Vector  6:  ADC10IFG0 */
            adc10_result = ADC10MEM0;                       /* Move results, IFG is cleared */
            adc10_data_ready = 1;
            break;
        case  8:
            break;                           /* Vector  8:  ADC10IFG1 */
        case 10:
            break;                           /* Vector 10:  ADC10IFG2 */
        case 12:
            break;                           /* Vector 12:  ADC10IFG3 */
        case 14:
            break;                           /* Vector 14:  ADC10IFG4 */
        case 16:
            break;                           /* Vector 16:  ADC10IFG5 */
        case 18:
            break;                           /* Vector 18:  ADC10IFG6 */
        case 20:
            break;                           /* Vector 20:  ADC10IFG7 */
        case 22:
            break;                           /* Vector 22:  ADC10IFG8 */
        case 24:
            break;                           /* Vector 24:  ADC10IFG9 */
        case 26:
            break;                           /* Vector 26:  ADC10IFG10 */
        case 28:
            break;                           /* Vector 28:  ADC10IFG11 */
        case 30:
            break;                           /* Vector 30:  ADC10IFG12 */
        case 32:
            break;                           /* Vector 32:  ADC10IFG13 */
        case 34:
            break;                           /* Vector 34:  ADC10IFG14 */
        default:
            break;
    }

    __exit_isr();
}
