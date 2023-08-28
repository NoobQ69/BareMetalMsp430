#include "LED_7_Mpx2.h"

unsigned char Code7SegSource[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77/*A*/, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x08};

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

void displayLED7Mpx2(unsigned int number1, unsigned int number2)
{
    IE74595_Out(Code7SegSource[number1%16]);
    LED_PIN_CONTROL_1 = 1;
    delayMs(2);
    LED_PIN_CONTROL_1 = 0;
    
    IE74595_Out(Code7SegSource[number2%16]);
    LED_PIN_CONTROL_1 = 1;
    delayMs(2);
    LED_PIN_CONTROL_1 = 0;
}

