#include "msp430g2553.h"

unsigned int CountingPulse = 0, UpToSecond = 0;
unsigned int FlowRate = 0;

void GPIOInit(void)
{
P1DIR = BIT2;
// chan ngat
P1DIR &= ~BIT0; 
P1IE |= BIT0;   
P1IES |= BIT0; 
P1IFG &= ~BIT0;
}


void SystemClockConfig(void)
{
BCSCTL1 = CALBC1_8MHZ; 
DCOCTL = CALDCO_8MHZ; 
BCSCTL2 = 0x06; 
}

void TimerAConfig(void)
{    
TA0CCTL0 = CCIE;
TA0CCTL1 = OUTMOD_7;
TA0CTL = TASSEL_2 + MC_1; 

TA0CCR0 = 50000;
}

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  SystemClockConfig();
  GPIOInit();
  TimerAConfig();
  __bis_SR_register(GIE);
  while (1)
  {
    
  }
  return 0;
}

#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void)
{
CountingPulse++;
P1IFG &= ~BIT0;
}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
  UpToSecond++;
  if (UpToSecond >= 20)
  {
   FlowRate = (CountingPulse / 7.5);
   UpToSecond = 0;
   CountingPulse = 0;

   TA0CCTL0 &= ~CCIFG; 
  }
}
