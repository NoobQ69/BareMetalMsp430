#include "buttons.h"

unsigned char Mode = 1, Effects = 1;

void handleModeButton(void)
{
  if (Mode == 0)
  {
    Mode = 1;
  }
  else
  {
    Mode = 0;
  }   
}

void handleEffectsButton(void)
{
  
  Effects = (Effects % 4 + 1);  
}
