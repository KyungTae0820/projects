#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h> //for snprinf

#include "lcd.h"
#include "adc.h"

void timer2_init(void);

enum states
{
    VARIABLE,
    LEFT,
    RIGHT
};

int main(void)
{
    uint8_t state; //for state

    // Initialize the LCD
    lcd_init();

    // Initialize the ADC
    adc_init();

    // Initialize TIMER2
    timer2_init();

    // Write splash screen and delay for 1 second
    lcd_writecommand(1);
    lcd_moveto(0, 5);
    lcd_stringout("KT Kim");
    lcd_moveto(1, 2);
    lcd_stringout("EE109 Lab 7");
    _delay_ms(1000);
    lcd_writecommand(1);

    state = VARIABLE;
    while (1) {                 // Loop forever
        // Check buttons and determine state
        unsigned char adc_result = adc_sample(0);
        if((adc_result >=200) && (adc_result < 210)){
            state = VARIABLE;
        }
        else if((adc_result >=150) && (adc_result < 160)){
            state = LEFT;
        }
        else if((adc_result >= 0) && (adc_result < 5)){
            state = RIGHT;
        }
        else{
            //Nothing
        }
    // Change output based on state
        // If RIGHT or LEFT button pressed, move servo accordingly
        if(state == LEFT){
            OCR2A = 35;
        }
        else if(state == RIGHT){
            OCR2A = 11;
        }
        // If SELECT button pressed read potentiometer ADC channel
        //    Convert ADC value to OCR2A number for PWM signal
        else if(state == VARIABLE){
            adc_result = adc_sample(1);
            OCR2A = 35 - ((adc_result * (35 -11))/255); 
        }
        // Display the PWM value on the LCD
        char buf[8];
        snprintf(buf, 8, "PWM=%2d", OCR2A);
        lcd_moveto(1, 5);
        lcd_stringout(buf);

    }

    return 0;   /* never reached */
}


/*
  timer2_init - Initialize Timer/Counter2 for Fast PWM
*/
void timer2_init(void)
{
    // Add code to initialize TIMER2
    // TCCR2A |= (1 << COM2A1);
    // TCCR2A &= ~(1 << COM2A0);
    // TCCR2A |= ((1 << WGM21) | (1 << WGM20));
    // OCR2A = 255;
    DDRB |= (1 << PB3); //add code to set the DDR bit for Port B, bit 3 to a one to make it the PWM pulse output
    TCCR2A |= (0b11 << WGM20);  // Fast PWM mode, modulus = 256
    TCCR2A |= (0b10 << COM2A0); // Turn D11 on at 0x00 and off at OCR2A
    OCR2A = 22;        // Initial pulse width
    TCCR2B |= (0b111 << CS20);  // Prescaler = 1024 for 16ms period
    
}
