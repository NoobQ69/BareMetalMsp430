#include "main.h"

int temperature = 0;
long pressure = 0;

void SystemClockConfig(void)
{
    BCSCTL1 = CALBC1_8MHZ; // Set DCO range select to 8 MHz
    DCOCTL = CALDCO_8MHZ; // Set DCO frequency control to 8 MHz
    BCSCTL2 = 0x06; // Set SMCLK source select to DCO/8 (8 MHz)
}

void GPIOInit(void)
{
  P2DIR = BIT3;
  // For I2C pins
  P1SEL |= BIT6 + BIT7;
  P1SEL2 |= BIT6 + BIT7;
}

int main( void )
{
  // Stop watchdog timer to prevent time out reset
   WDTCTL = WDTPW + WDTHOLD;
  SystemClockConfig();
  GPIOInit();
  I2C_MasterModeInit();
  I2C_MasterStoreSlaveAddress(BMP180_ADDRESS, 7);
  P2OUT |= BIT3;
  P2OUT &= ~BIT3;
  
  while (1)
  {
    temperature = BMP180_GetTemperature();
    pressure = BMP180_GetPressure();
    delayMs(1000);
  }
  //return 0;
}
