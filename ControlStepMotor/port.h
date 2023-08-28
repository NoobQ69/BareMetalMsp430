#ifndef __PORT_H_
#define __PORT_H_

#define STATE_BUTTON            P2IN_bit.P4
#define DIRECTION_BUTTON        P2IN_bit.P5

#define STEPPER_INPUT_1         P2OUT_bit.P0
#define STEPPER_INPUT_2         P2OUT_bit.P1
#define STEPPER_INPUT_3         P2OUT_bit.P2
#define STEPPER_INPUT_4         P2OUT_bit.P3

#define IE74595_SHCP            P1OUT_bit.P0
#define IE74595_DS              P1OUT_bit.P1
#define IE74595_STCP            P1OUT_bit.P2
#define LED_PIN_CONTROL_1       P2OUT_bit.P6
#define LED_PIN_CONTROL_2       P2OUT_bit.P7

#endif