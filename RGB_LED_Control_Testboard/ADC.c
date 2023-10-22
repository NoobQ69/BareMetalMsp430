#include "ADC.h"

unsigned int ADC_Read() 
{
    ADC10CTL0 |= ENC + ADC10SC;                                 // Enable ADC conversion and start conversion
    while (ADC10CTL1 & ADC10BUSY);                              // Wait for conversion to complete
    
    return ADC10MEM;                                            // Return ADC conversion result
}

unsigned int ADC10_Pin1_Read()
{
      // Read voltage on P1.7
//    ADC10CTL0 &= ~ENC;                  // Disable ADC
    
    return ADC_Read();
}
