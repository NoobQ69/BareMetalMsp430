#include "main.h"

unsigned char data;
unsigned int Temperature = 0;

void System_Clock_Configuration()
{
    DCOCTL = CALDCO_8MHZ;          // Set DCO range select to 8 MHz
    BCSCTL1 = CALBC1_8MHZ;         // Set DCO frequency control to 8 MHz       
    BCSCTL2 |= SELM_0 + DIVS_3;    // Select DCO + SMCLK / 8
}

void GPIO_Init()
{
    P1SEL |= LM35_PIN; // Set LM35 input pin to analog mode
    P1SEL2 |= LM35_PIN; // Set LM35 input pin to analog mode
    
    // For LED 7 Mpx4
    P1DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5; // pin P1.0 -> P1.5 as output
}

void ADC10_Init()
{
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + ADC10ON;               // ADC10ON
  ADC10CTL1 = INCH_7 + ADC10DIV_3 + ADC10SSEL_3 + CONSEQ_0;        // input A1, single chanel single conversion mode
  ADC10AE0 |= LM35_PIN;                                                 // PA.1 ADC option select
}

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  System_Clock_Configuration();
  GPIO_Init();
  ADC10_Init();
  //__bis_SR_register(GIE);
  
  while (1)
  {
    Temperature = LM35_Read(); // Read LM35 temperature
    for (int i = 0; i < 200; i++)
    {
        displayLED7Mpx3(Temperature);
    }
  }
  
  return 0;
}


//// USCI A0/B0 Receive ISR
//#pragma vector=USCIAB0RX_VECTOR
//__interrupt void USCI0RX_ISR(void)
//{
//  UCA0TXBUF = UCA0RXBUF;
//}