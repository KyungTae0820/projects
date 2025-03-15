#include <avr/io.h>

#include "adc.h"


void adc_init(void)
{
    // Initialize the ADC
    //1.
    ADMUX &= ~(1 << REFS1); //Set/clear the REFS[1:0] bits in ADMUX, AVCC Reference
    ADMUX |= (1 << REFS0);

    //2.
    ADMUX |= (1 << ADLAR); //Set ADLAR bit to 1 in the ADMUX register (1 = 8-bit results, 0 = 10-bit results)
    
    //3.
    //Set prescalar to 128 by turning on (setting) ADPS2, ADPS1, ADPS0 bits in ADCSRA register
    ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)); //Set/clear the ADPS[2:0] bits in ADCSRA to select an appropriate prescalar value.

    //4.
    ADCSRA |= (1 << ADEN); //Set the ADEN bit in ADCSRA to enable the ADC module.

}

uint8_t adc_sample(uint8_t channel)
{
    // Set ADC input mux bits to 'channel' value
    //1. If we want channel A3, set mux bits to 0011
    ADMUX &= ~(0x0f);
    ADMUX |= (channel & (0x0f));

    // Convert an analog input and return the 8-bit result
    //2. Set the ADSC bit in the ADCSRA register to a 1.
    ADCSRA |= (1 << ADSC);

    //3. Enter a loop that tests the ADSC bit each time through the loop and exits the loop when ADSC is 0.
    while((ADCSRA & (1 << ADSC)) != 0){}

    //4. Copy the 8-bit conversion result from the ADCH register and return it to the calling program.
    return ADCH;
}
