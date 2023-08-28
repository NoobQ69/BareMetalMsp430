#include "ADC_Reading.h"

unsigned int ADC_Read() 
{
    ADC10CTL0 |= ENC + ADC10SC;                                 // Enable ADC conversion and start conversion
    while (ADC10CTL1 & ADC10BUSY);                              // Wait for conversion to complete
    
    return ADC10MEM;                                            // Return ADC conversion result
}

unsigned int ADC10_Pin1_Read()
{
      // Read voltage on P1.7
    ADC10CTL0 &= ~ENC;                  // Disable ADC
    ADC10CTL1 &= ~(INCH_7 + INCH_6 + INCH_5);
    ADC10CTL1 |= INCH_7;    // Select P1.7 as input channel
    
    return ADC_Read();
}

unsigned int ADC10_Pin2_Read()
{
      // Read voltage on P1.6
    ADC10CTL0 &= ~ENC;                  // Disable ADC
    ADC10CTL1 &= ~(INCH_7 + INCH_6 + INCH_5);
    ADC10CTL1 = INCH_6;    // Select P1.7 as input channel
    
    return ADC_Read();
}

unsigned int ADC10_Pin3_Read()
{
      // Read voltage on P1.5
    ADC10CTL0 &= ~ENC;                  // Disable ADC
    ADC10CTL1 &= ~(INCH_7 + INCH_6 + INCH_5);
    ADC10CTL1 = INCH_5;    // Select P1.7 as input channel
    
    return ADC_Read();
}
