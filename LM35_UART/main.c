#include "main.h"

unsigned char data;

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
}

void UART_Init()
{
  P1SEL |= BIT1 + BIT2;
  P1SEL2 |= BIT1 + BIT2;
  
  
  UCA0CTL0 = 0x00;                      // UART mode, No parity bit, 8 bit frame, 1 bit stop LSB
  UCA0CTL1 |= UCSSEL_2 + UCSWRST;       // Clock source for UART is SMCLK 1Mhz
  UCA0BR0 = 104;                        // 104 From User's Guide datasheet table
  UCA0BR1 = 0x00;
  UCA0MCTL = UCBRS_1;                   // Modulation value = 1 from datasheet
  
  UCA0CTL1 &= ~UCSWRST;                 // Clear UCSWRST to enable USCI_A0
  //IE2 |= UCA0RXIE;                    // Enable UART Rx
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
  UART_Init();
  ADC10_Init();
  //__bis_SR_register(GIE);
  
  while (1)
  {
    float temperature = LM35_Read(); // Read LM35 temperature
    UART_Send_String("Temperature: ");
    UART_Send_Number((unsigned int)temperature);
    delayMs(500);
  }
  
  return 0;
}


//// USCI A0/B0 Receive ISR
//#pragma vector=USCIAB0RX_VECTOR
//__interrupt void USCI0RX_ISR(void)
//{
//  UCA0TXBUF = UCA0RXBUF;
//}