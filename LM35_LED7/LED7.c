#include "LED7.h"

unsigned char Code7SegSink[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x00, 0x90, /*A*/0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};

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

void displayLED7Mpx3(unsigned int number)
{
    IE74595_Out(Code7SegSink[number%1000/100]);
    LED_PIN_CONTROL_2 = 0;
    delayMs(2);
    LED_PIN_CONTROL_2 = 1;
	
    IE74595_Out(Code7SegSink[number%100/10]);
    LED_PIN_CONTROL_3 = 0;
    delayMs(2);
    LED_PIN_CONTROL_3 = 1;
    
    IE74595_Out(Code7SegSink[number%10]);
    LED_PIN_CONTROL_4 = 0;
    delayMs(2);
    LED_PIN_CONTROL_4 = 1;
}