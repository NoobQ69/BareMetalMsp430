#include "buttons.h"

unsigned char DigitalRead(unsigned char port, unsigned char pin)
{
  if (port == 1)
  {
    port = P1IN;
  }
  else if (port == 2)
  {
    port = P2IN;
  }
    switch (pin)
    {
    case 0:
      {
        return getPinStatePort(port, BIT0);
        break;
      }
    case 1:
      {
        return getPinStatePort(port, BIT1);
        break;
      }
    case 2:
      {
        return getPinStatePort(port, BIT2);
        break;
      }
    case 3:
      {
        return getPinStatePort(port, BIT3);
        break;
      }
    case 4:
      {
        return getPinStatePort(port, BIT4);
        break;
      }
    case 5:
      {
        return getPinStatePort(port, BIT5);
        break;
      }
    case 6:
      {
        return getPinStatePort(port, BIT6);
        break;
      }
    case 7:
      {
        return getPinStatePort(port, BIT7);
        break;
      }
    }
  return 0;
}

void DigitalWrite(unsigned char port, unsigned char pin, unsigned char value)
{
  if (port == 1)
  {
    port = P1OUT;
  }
  else if (port == 2)
  {
    port = P2OUT;
  }
    switch (pin)
    {
    case 0:
      {
        if (value == 1)
          port |= BIT0;
        else
          port &= ~BIT0;
        break;
      }
    case 1:
      {
        if (value == 1)
          port |= BIT1;
        else
          port &= ~BIT1;
        break;
      }
    case 2:
      {
        if (value == 1)
          port |= BIT2;
        else
          port &= ~BIT2;
        break;
      }
    case 3:
      {
        if (value == 1)
          port |= BIT3;
        else
          port &= ~BIT3;
        break;
      }
    case 4:
      {
        if (value == 1)
          port |= BIT4;
        else
          port &= ~BIT4;
        break;
      }
    case 5:
      {
        if (value == 1)
          port |= BIT5;
        else
          port &= ~BIT5;
        break;
      }
    case 6:
      {
        if (value == 1)
          port |= BIT6;
        else
          port &= ~BIT6;
        break;
      }
    case 7:
      {
        if (value == 1)
          port |= BIT7;
        else
          port &= ~BIT7;
        break;
      }
    }
}

unsigned char getPinStatePort(unsigned char port, unsigned char pin)
{
    if ((port & pin) == 0)
    {
        delayMs(10);
        if ((port & pin) == 0)
        {
          while ((port & pin) == 0){delayMs(10);}
          return 1;
        }
    }
    return 0;
}
