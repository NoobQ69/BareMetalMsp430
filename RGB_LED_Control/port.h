#ifndef __PORT_H_
#define __PORT_H_

#define ADC_PIN_1       BIT7          // P1.7
#define ADC_PIN_2       BIT6          // P1.6
#define ADC_PIN_3       BIT5          // P1.5

#define TIMER1_OUT      BIT1         // P2.1
#define TIMER2_OUT      BIT4         // P2.4
#define TIMER3_OUT      BIT2         // P1.2

#define MODE_BUTTON     P1IN_bit.P0
#define EFFECTS_BUTTON  P1IN_bit.P1

#define RED_LED_TIMER   TA1CCR1        // RED
#define GREEN_LED_TIMER TA1CCR2        // GREEN
#define BLUE_LED_TIMER  TA0CCR1        // BLUE

#endif
