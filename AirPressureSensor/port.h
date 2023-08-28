#ifndef __PORT_H_
#define __PORT_H_

/* ********************************************************************
 * Mo ta: File dung de khai bao dinh nghia cac chan cua vi dieu khien *
 **********************************************************************/

#include "main.h"
   
/* define pins of LED 7 */
#define IE74595_SHCP    P1OUT_bit.P0
#define IE74595_DS      P1OUT_bit.P1
#define IE74595_STCP    P1OUT_bit.P2

#define LED_PIN_CONTROL_1 P1OUT_bit.P3
#define LED_PIN_CONTROL_2 P1OUT_bit.P4
#define LED_PIN_CONTROL_3 P1OUT_bit.P5
   
#define ADDO P2IN_bit.P2
#define ADSK P2OUT_bit.P1

#endif