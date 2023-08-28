#include "delayMs.h"

void delayMs(unsigned int ms)
{
  for (int i = 0; i < ms; i++)
  {
    __delay_cycles(CLOCK_SOURCE / 1000);
  }
}

