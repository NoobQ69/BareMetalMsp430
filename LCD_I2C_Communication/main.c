#include "main.h"

extern unsigned char err;

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
  I2C_MasterStoreSlaveAddress(0x27, 7);
  P2OUT |= BIT3;
  P2OUT &= ~BIT3;
  lcd_init();
  
  //__bis_SR_register(GIE);        // Enter LPM0 w/ interrupts
  
  while (1)
  {
    lcd_gotoxy(0,4);
    lcd_send_string("Test LCD");
    lcd_gotoxy(1,5);
    lcd_send_string("LM16X2");
    delayMs(1000);
    lcd_reset();
    if (err == 1)
      break;
  }
  //return 0;
}

