#include "main.h"

int P = 0;
unsigned long result = 0;

void SystemClockConfig(void)
{
    BCSCTL1 = CALBC1_8MHZ; // Set DCO range select to 8 MHz
    DCOCTL = CALDCO_8MHZ; // Set DCO frequency control to 8 MHz
    BCSCTL2 = 0x06; // Set SMCLK source select to DCO/8 (8 MHz)
}

void GPIOInit(void)
{
    // For LED 7 Mpx4
    P1DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6; // pin P1.0 -> P1.6 as output
    
    // For communicate with sensor
    // ADSK
    P2DIR = BIT1;
    // ADDO
    P2REN = BIT2;
    
    P2OUT = BIT2 + BIT1;
}

void TimerAConfig(void)
{    
    TA0CCTL0 = CCIE; // Enable interrupt for Timer A 
    TA0CCTL1 = OUTMOD_7; // Set PWM output mode (Reset/set)
    TA0CTL = TASSEL_2 + MC_1; // Set SMCLK as clock source and Up mode, Timer A interrupt enable
    
    TA0CCR0 = 2000; // Set period to 2000 cycles
    TA0CCR1 = 0; 
}

void AirPressureReading()
{
  if (Hx710B_ReadAirPressure(&result, 1000u) != HX710B_OK)
  {
    P = -1;
  }
  else
  {
    float Vout = ((result / 16777215.0) * 5.0);
    P = (Vout - 0.1) / 0.09;
    //displayLED7Mpx4(P);                   // value in kPa
    delayMs(1000);
  }
}

int main( void )
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    
    SystemClockConfig();
    GPIOInit();
    Hx710B_Init();
    TimerAConfig();
    __bis_SR_register(GIE);
    while (1)
    {
      AirPressureReading();
    }
  //return 0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
   displayLED7Mpx4(P);
   TA0CCTL0 &= ~CCIFG; // Clear Timer A capture/compare register 0 interrupt flag
}
