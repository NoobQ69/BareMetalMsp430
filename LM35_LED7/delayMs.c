#include "delayMs.h"

void delayMs(unsigned int ms)
{
  for (int i = 0; i < ms; i++)
  {
    __delay_cycles(SYSTEM_CLOCK / 1000);
  }
}

