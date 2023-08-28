#include "delayMs.h"

/* ************************
 * Mo ta: Ham delay ms    *
 **************************/

void delayMs(unsigned int ms)
{
  for (int i = 0; i < ms; i++)
  {
     __delay_cycles(CLOCK_SOURCE / 1000);
  }
}

void delayUs(unsigned int us)
{
  for (int i = 0; i < us; i++)
  {
     __delay_cycles(CLOCK_SOURCE / 1000000);
  }
}

