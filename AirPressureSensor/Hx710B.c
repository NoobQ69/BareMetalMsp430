#include "Hx710B.h"

extern unsigned long result;

void Hx710B_Init()
{
  for (char i = 0; i < HX710B_DEFAULT_MODE; i++) 
  {
    delayUs(2);
    ADSK = 0;
    delayUs(2);
    ADSK = 1;
  }
  Hx710B_ReadAirPressure(&result, 500u);
  delayMs(500);
  Hx710B_ReadAirPressure(&result, 100u);
}

unsigned char Hx710B_IsReady(unsigned int timeOut)
{
  unsigned int countTime = 0;
    while (ADDO != 0)
    {
      countTime++;
      if (countTime > timeOut) return HX710B_TIMEOUT;
    // need delay;
      delayMs(1);
    }
    return HX710B_OK;
}

unsigned char Hx710B_ReadAirPressure(unsigned long *data, unsigned int timeOut)
{
  ADSK = 0;
  *data = 0;
  if (Hx710B_IsReady(timeOut) == HX710B_OK)
  {
      for (int i = 0; i < HX710B_DEFAULT_MODE; i++)
      {
        delayUs(2);
        ADSK = 1;
        delayUs(2);
        ADSK = 0;
        
        if (i < 24)
        {
            *data = *data << 1;
            if (ADDO == 1) *data = *data + 1;
        }
      }
     ADSK = 1;
     *data = *data ^ 0x800000;
     
     return HX710B_OK;
    }
  return HX710B_TIMEOUT;
}

