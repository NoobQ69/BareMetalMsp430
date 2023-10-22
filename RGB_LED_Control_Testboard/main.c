#include "main.h"

float ValuePWM = 0;
int ModeBTN = 0, HasChanged;
unsigned char block = 0;


void System_Clock_Configuration()
{
    DCOCTL = CALDCO_8MHZ;          // Set DCO range select to 8 MHz
    BCSCTL1 = CALBC1_8MHZ;         // Set DCO frequency control to 8 MHz
    BCSCTL2 = SELM_0 + DIVS_3;    // Select DCO + SMCLK / 8
}

void GPIO_Init()
{
  // chiet ap
  P1SEL |= ADC_PIN_1; // Set ADC pin 1 to analog mode
  P1SEL2 |= ADC_PIN_1; // Set ADC pin to analog mode
  
  // nut nhan
  P1DIR &= ~(BIT1);
  P1REN |= BIT1;
  P1OUT |= BIT1;
  P1IE |= BIT1;  // Enable interrupts on on P1.0 and P1.1
}

void TimerAConfig(void)
{
    // TimerA1
    P2DIR |= TIMER1_OUT + TIMER2_OUT;   // Set P2.1, P2.4 and P2.6 as output
    P2SEL |= TIMER1_OUT + TIMER2_OUT;   // Set P2.1, P2.4 as P2.6 PWM output

    // TimerA0
    P1DIR |= TIMER3_OUT;
    P1SEL |= TIMER3_OUT;

    // *********************For Timer A0************************
    TA0CTL = TASSEL_2 + MC_1;           // Set SMCLK as clock source and Up mode, Timer A interrupt enable
    TA0CCTL0 |= CCIE;
    TA0CCR0 = 2000;                    // Set period to 20000 cycles

    TA0CCTL1 = OUTMOD_7;                // Set PWM output mode (Reset/set)
    TA0CCR1 = 1000;                    // Set duty cycle to 50%

    // ********************For timer A1*************************
    TA1CTL = TASSEL_2 + MC_1;           // Set SMCLK as clock source and Up mode, Timer A interrupt enable
    TA1CCR0 = 2000;                    // Set period to 2000 cycles

    TA1CCTL1 = OUTMOD_7;                // Set PWM output mode (Reset/set)
    TA1CCR1 = 1000;                    // Set duty cycle to 50%

    TA1CCTL2 = OUTMOD_7;                // Set PWM output mode (Reset/set)
    TA1CCR2 = 1000;                    // Set duty cycle to 50%
}

void ADC10_Init()
{
  ADC10CTL0 = SREF_0 + ADC10SHT_2 + REFON + REF2_5V + ADC10ON;    // Configure ADC clock divider and conversion sequence
  ADC10CTL1 = INCH_7 + ADC10DIV_4 + ADC10SSEL_3 + CONSEQ_0;             // Configure sample-and-hold time, enable ADC, and enable single channel and conversion mode
  ADC10AE0 |= ADC_PIN_1;                                                // Enable analog input on P1.7
}

void TimerInitSetup()
{
   RED_LED_TIMER   = 0x00;
   GREEN_LED_TIMER = 0x00;
   BLUE_LED_TIMER  = 0x00;
}

void ControlRGB()
{
  //unsigned char getModeBtn = DigitalRead(1, 1);
//  if ((P1IN_bit.P1) == 0)
//  {
//    delayMs(10);
//    if ((P1IN_bit.P1) == 0)
//    {
//      while ((P1IN_bit.P1) == 0){delayMs(10);}
//      ModeBTN++;
//    }
//  }
  ValuePWM = ADC10_Pin1_Read(); // Read potential meter
  
  switch (ModeBTN)
  {
  case 0:
    {
      TA1CCR1 = (int)(ValuePWM*1.95);        // RED
      break;
    }
  case 1:
    {
      TA1CCR2 = (int)(ValuePWM*1.95);        // GREEN
      break;
    }
  case 2:
    {
      TA0CCR1 = (int)(ValuePWM*1.95);        // BLUE
      break;
    }
  case 3:
    {
      TA1CCR1 = (int)(ValuePWM*1.95);        // RED
      TA1CCR2 = (int)(ValuePWM*1.95);        // GREEN
      TA0CCR1 = (int)(ValuePWM*1.95);        // BLUE
      break;
    }
  default:
    {
      // do something
    }
  }
  delayMs(20);
}

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  System_Clock_Configuration();
  GPIO_Init();
  ADC10_Init();
  TimerAConfig();
  TimerInitSetup();
  __bis_SR_register(GIE);                                               // Interrupts enabled

  while (1)
  {
    ControlRGB();
  }
}

// Timer A0 interrupt to handle bouncing button
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    if (block >= 1)
    {
      block++;
      if (block >= 15) block = 0;
    }
    TA0CCTL0 &= ~CCIFG; // Clear Timer A capture/compare register 0 interrupt flag
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
//  if (P1IFG & BIT0) // Check if P1.0 is pressed
//  {
//    if (block == 0)
//    {
//        HasChanged = 1;
//        handleModeButton();
//        block = 1;
//    }
//    P1IFG &= ~BIT0;
//  }

  if (P1IFG & BIT1) // Check if P1.1 is pressed
  {
    if(block == 0)
    {
        HasChanged = 1;
        ModeBTN = (ModeBTN+1)%4;
        block = 1;
    }
    P1IFG &= ~BIT1;
  }
}

