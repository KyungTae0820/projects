#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h> //for snprinf

#include "lcd.h"
#include "adc.h"

int main(void)
{

    // Initialize the LCD
    lcd_init();

    // Initialize the ADC
    adc_init();

    // Initialize TIMER2


    // Write splash screen and delay for 1 second
    lcd_writecommand(1);
    lcd_moveto(0, 5);
    lcd_stringout("KT Kim");
    lcd_moveto(1, 2);
    lcd_stringout("EE109 Lab 7");
    _delay_ms(1000);
    lcd_writecommand(1);

    while (1) {
        // // Use adc_sample to read ADC value for buttons or potentiometer
        // char buf[5]; 
        // unsigned char adc_result = adc_sample(1);
        // // Use snprintf and lcd_stringout to display number on LCD
        // snprintf(buf, 5, "%4d", adc_result);
        // lcd_moveto(0, 0);
        // lcd_stringout(buf);
    }

    while (1) {                 // Loop forever
	// Check buttons and determine state


	// Change output based on state
        // If RIGHT or LEFT button pressed, move servo accordingly
	// If SELECT button pressed read potentiometer ADC channel
	//    Convert ADC value to OCR2A number for PWM signal



        // Display the PWM value on the LCD


    }

    return 0;   /* never reached */
}


/*
  timer2_init - Initialize Timer/Counter2 for Fast PWM
*/
void timer2_init(void)
{
    // Add code to initialize TIMER2
    TCCR2A |= (1 << COM2A1);
    TCCR2A &= ~(1 << COM2A0);
    TCCR2A |= ((1 << WGM21) | (1 << WGM20));
    OCR2A = 255;
    
}
