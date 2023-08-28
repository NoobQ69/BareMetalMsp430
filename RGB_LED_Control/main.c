#include "main.h"

float Value1 = 0, Value2 = 0, Value3 = 0;
extern unsigned char Mode, Effects, HasChanged;

unsigned char block = 0;

void System_Clock_Configuration()
{
    DCOCTL = CALDCO_8MHZ;          // Set DCO range select to 8 MHz
    BCSCTL1 = CALBC1_8MHZ;         // Set DCO frequency control to 8 MHz
    BCSCTL2 |= SELM_0 + DIVS_3;    // Select DCO + SMCLK / 8
}

void GPIO_Init()
{
    // ************************************ FOR ADC PINS ************************************

    P1SEL |= ADC_PIN_1 + ADC_PIN_2 + ADC_PIN_3; // Set LM35 input pin to analog mode
    P1SEL2 |= ADC_PIN_1 + ADC_PIN_2 + ADC_PIN_3; // Set LM35 input pin to analog mode

    // ************************************ FOR BUTTONS PINS ************************************

    P1DIR &= ~(BIT0 + BIT1);
    P1REN |= BIT0 + BIT1;
    P1OUT |= BIT0 + BIT1;
    //P1IES |= BIT0 + BIT1; // interrupt falling edge for P1.0 and P1.1
    P1IE |= BIT0 + BIT1;  // Enable interrupts on on P1.0 and P1.1
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
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + REF2_5V + ADC10ON + MSC;    // Configure ADC clock divider and conversion sequence
  ADC10CTL1 = ADC10DIV_4 + ADC10SSEL_3 + CONSEQ_1;                      // Configure sample-and-hold time, enable ADC, and enable multiple sample and conversion mode
  ADC10AE0 |= ADC_PIN_1 + ADC_PIN_2 + ADC_PIN_3;                        // Enable analog input on P1.7, P1.6 and P1.5
}

void TimerInitSetup()
{
   RED_LED_TIMER   = 0x00;
   GREEN_LED_TIMER = 0x00;
   BLUE_LED_TIMER  = 0x00;
}

void MonitorLED()
{
  if (Mode == 1) {
    TimerInitSetup();
    Value1 = ADC10_Pin1_Read(); // Read LM35 temperature

    Value2 = ADC10_Pin2_Read(); // Read LM35 temperature

    Value3 = ADC10_Pin3_Read(); // Read LM35 temperature

    TA1CCR1 = Value1*1.95;        // RED
    TA1CCR2 = Value2*1.95;        // GREEN
    TA0CCR1 = Value3*1.95;        // BLUE
    delayMs(40);
  }
  else if(Mode == 0){
    TimerInitSetup();

    switch (Effects)
    {
    case 1:
      {
        effect1();
        break;
      }
    case 2:
      {
        effect2();
        break;
      }
    case 3:
      {
        effect3();
        break;
      }
    case 4:
      {
        effect4();
        break;
      }
    default:
      {
        break;
      }
    }
  }
}

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  System_Clock_Configuration();
  GPIO_Init();
  ADC10_Init();
  TimerAConfig();

  __bis_SR_register(GIE);                                               // Interrupts enabled

  while (1)
  {
    MonitorLED();
  }

  return 0;
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
  if (P1IFG & BIT0) // Check if P1.0 is pressed
  {
    if (block == 0)
    {
        HasChanged = 1;
        handleModeButton();
        block = 1;
    }
    P1IFG &= ~BIT0;
  }

  if (P1IFG & BIT1) // Check if P1.1 is pressed
  {
    if(block == 0)
    {
        HasChanged = 1;
        handleEffectsButton();
        block = 1;
    }
    P1IFG &= ~BIT1;
  }
}
