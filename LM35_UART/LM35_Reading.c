#include "LM35_Reading.h"

unsigned int ADC_Read() 
{
    ADC10CTL0 |= ENC + ADC10SC;                                 // Enable ADC conversion and start conversion
    while (ADC10CTL1 & ADC10BUSY);                              // Wait for conversion to complete
    
    return ADC10MEM;                                            // Return ADC conversion result
}

float LM35_Read() 
{
    unsigned int adc_value = ADC_Read();                                // Read LM35 output voltage
    float temperature = (float) adc_value * (1.5 / 1024.0) * 100.0;       // Convert ADC value to voltage, then to temperature in Celsius
    return temperature;
}

