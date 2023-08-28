#include "LED7.h"

unsigned char count = 0;

unsigned char Code7SegSource[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77/*A*/, 0x7C, 0x39, 0x5E, 0x79, 0x71};

void IE74595_Out(unsigned char number)
{
    unsigned char i;
    
    IE74595_STCP = 0;
    
    for (i = 0; i < 8; i++)
    { 
        IE74595_SHCP = 0;
        
        if (number & 0x80)
        {
          IE74595_DS = 1;// get each bit from MSB to LSB
        }
        else
        {
          IE74595_DS = 0;
        }

        // Create pulse to transfer data to IC 74595
        IE74595_SHCP = 1;
        number <<= 1;
        //TestBug();
    }
    IE74595_STCP = 1;
}

void displayLED7Mpx4(unsigned int number)
{
  count = (count+1)%3;
  if(count == 0)
  {
    IE74595_Out(Code7SegSource[number%1000/100]);
    LED_PIN_CONTROL_3 = 0;
    LED_PIN_CONTROL_1 = 1;
  }
  else if (count == 1)
  {
    IE74595_Out(Code7SegSource[number%100/10]);
    LED_PIN_CONTROL_1 = 0;
    LED_PIN_CONTROL_2 = 1;
  }
  else if (count == 2)
  {
    IE74595_Out(Code7SegSource[number%10]);
    LED_PIN_CONTROL_2 = 0;
    LED_PIN_CONTROL_3 = 1;
  }
}