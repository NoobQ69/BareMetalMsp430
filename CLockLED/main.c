#include "msp430g2553.h"

typedef struct Time
{
  unsigned char hours;
  unsigned char minutes;
} Time;

Time ClockTime;

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  return 0;
}
