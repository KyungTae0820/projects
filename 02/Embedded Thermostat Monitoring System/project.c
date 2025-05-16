/********************************************
 *
 *  Name: KyungTae Kim
 *  Email: kyungtae@usc.edu
 *  Project - Temperature Monitor
 *
 ********************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdbool.h>
#include <stdio.h>
#include "ds18b20.h"
#include "lcd.h"
#include "serial.h"
#include "timer.h"

volatile int low = 50;
volatile int high = 90;
enum states {LOW, HIGH};
volatile uint8_t state;

//Rotary Encoder
volatile uint8_t new_state, old_state;
volatile uint8_t changed = 0;  // Flag for state change
volatile int16_t count = 0;     // Count to display
volatile uint8_t a, b;

//Servo
volatile uint16_t servocnt = 0;
volatile uint16_t OCR2Aval = 30;
bool servo_active = false;
bool servo_deactive = false;

//RX/TX
enum rstates {UPPER, LOWER};
volatile uint8_t rstate;

volatile char rx_Buf[6];
volatile uint8_t rx_index = 0;

volatile uint8_t flag = 0;
volatile int temp1 = 50; 
volatile int temp2 = 90;

 int main(void)
 {
    // Initialize the LCD
    lcd_init();

    // Initialize Serial
    serial_init();

    // Initialize timer
    timer1_init();
    timer2_init();

    // PWM and Enable signal
    DDRB |= (1 << PB3) | (1 << PB4);
    PORTB |= (1 << PB5); //Enable pullup resistor for HI/LO Button

    // LED and Buttons
    DDRC |= (1 << PC2) | (1 << PC3) | (1 << PC4);
    PORTC |= (1 << PC2) | (1 << PC3) | (1 << PC4);
    PORTC |= ((1 << PC1) | (1 << PC5));

    // Rotary Encoder 
    PORTD |= ((1 << PD2) | (1 << PD3));
    PCICR |= (1 << PCIE2);   // Enable Pin Change Interrupts for Port D
    PCMSK2 |= (1 << PCINT18) | (1 << PCINT19);  // Enable interrupts for PD2 and PD3
    
    sei(); // Enable Global Interrupts

    uint8_t x = PIND;
    a = x & (1 << PD2);
    a = a >> PD2; 
    b = x & (1 << PD3);
    b = b >> PD3;
    if (!b && !a) // both 00
        old_state = 0;
    else if (!b && a) // 01 
        old_state = 1;
    else if (b && !a) // 10
        old_state = 2;
    else // 11
        old_state = 3;

    new_state = old_state;

    // Write splash screen
    lcd_writecommand(1);
    lcd_moveto(0, 5);
    lcd_stringout("KT Kim");
    lcd_moveto(1, 2);
    lcd_stringout("EE109 Project");
    _delay_ms(1000);
    lcd_writecommand(1);

    if (ds_init() == 0) {    // Initialize the DS18B20
        // Sensor not responding
    }
    ds_convert();    // Start first temperature conversion

    // Set EEPROM to store the high and low temperature threshold values
    low = eeprom_read_byte((uint8_t*)100);
    high = eeprom_read_byte((uint8_t*)200); 

    if (low < 50 || low > 90) {
        low = 50;  
    }
    if (high < 50 || high> 90) {
        high = 90;  
    }

	char Buf[11];
	snprintf(Buf, 11, ">L=%d H=%d", low, high);
	lcd_moveto(0,0);
	lcd_stringout(Buf);
	lcd_moveto(0,10);
	lcd_stringout("<");

    state = LOW;
    rstate = UPPER;
    unsigned char t[2];
    while (1) {
        //Temperature conversion
        if (ds_temp(t)) {    // True if conversion complete
            /*
              Process the values returned in t[0]
              and t[1] to find the temperature.
            */
            int16_t tempbit = (t[1] << 8) | t[0];
            int16_t tempf = (tempbit * 9)/8 + 320;

            if (tempf < 0) tempf = 0;   //limit Temp
            if (tempf > 999) tempf = 999; //limit Temp

            char buf[5];
            snprintf(buf, 5, "%2d.%1d", tempf/10, tempf%10);
            lcd_moveto(0, 12);
            lcd_stringout(buf);
            ds_convert();   // Start next conversion

            // (UPPER state)
            if(tempf < (low*10) && rstate == UPPER) { //Blue
                PORTC |= ((1 << PC3) | (1 << PC4));
                PORTC &= ~(1 << PC2);
                OCR1B = OCR1A;
                if (!servo_active && !servo_deactive) {
                    servo_active = true;
                    servocnt = 0;
                    OCR2Aval = 35;
                    OCR2A = 35;
                }
            }
            else if(tempf > (high*10) && rstate == UPPER) { //Red
                PORTC |= ((1 << PC2) | (1 << PC3));
                PORTC &= ~(1 << PC4);
                OCR1B = OCR1A;
                if (!servo_active && !servo_deactive) {
                    servo_active = true;
                    servocnt = 0;
                    OCR2Aval = 35;
                    OCR2A = 35;
                }
            }
            if(tempf > (low*10) && tempf < (high*10) && rstate == UPPER) { //Green
                servo_active = false;
                servo_deactive = false;
                PORTC |= ((1 << PC2) | (1 << PC4));
                if (low == high) {
                    OCR1B = OCR1A/2;
                } 
                else {
                    OCR1B = (-1250/(high*10-low*10))*(tempf-(low*10))+2499;
                }
            }

            //When Local/Remove Pressed (LOWER state)
            if(tempf < (temp1*10) && rstate == LOWER) {
                PORTC |= ((1 << PC3) | (1 << PC4));
                PORTC &= ~(1 << PC2);
                OCR1B = OCR1A;
                if (!servo_active && !servo_deactive) {
                    servo_active = true;
                    servocnt = 0;
                    OCR2Aval = 35;
                    OCR2A = 35;
                }
            }
            else if(tempf > (temp2*10) && rstate == LOWER) {
                PORTC |= ((1 << PC2) | (1 << PC3));
                PORTC &= ~(1 << PC4);
                OCR1B = OCR1A;
                if (!servo_active && !servo_deactive) {
                    servo_active = true;
                    servocnt = 0;
                    OCR2Aval = 35;
                    OCR2A = 35;
                }
            }
            if(tempf > (temp1*10) && tempf < (temp2*10) && rstate == LOWER) {
                servo_active = false;
                servo_deactive = false;
                PORTC |= ((1 << PC2) | (1 << PC4));
                if (temp1 == temp2) {
                    OCR1B = OCR1A/2;
                }
                else {
                    OCR1B = (-1250/(temp2*10-temp1*10))*(tempf-(temp1*10))+2499;
                }
            }
        }

        //HI/LO button
        if((PINB & (1 << 5)) == 0){
            while((PINB & (1 << 5)) == 0){}
            char Buf1[11];
            if (state == LOW && rstate == UPPER) {
                state = HIGH;
                snprintf(Buf1, 11, " L=%d>H=%d", low, high);
                lcd_moveto(0, 0);
                lcd_stringout(Buf1);
            } 
            else if(state == HIGH && rstate == UPPER){
                state = LOW;
                snprintf(Buf1, 11, ">L=%d H=%d", low, high);
                lcd_moveto(0, 0);
                lcd_stringout(Buf1);
            }
        }

        //Rotary encoder
        if (changed) { 
            changed = 0;     

            eeprom_update_byte((uint8_t*)100, low);
            eeprom_update_byte((uint8_t*)200, high);

            if (state == LOW){
                snprintf(Buf, 11, ">L=%d H=%d", low, high);
                lcd_moveto(0, 0);
                lcd_stringout(Buf);
            }
            else if(state == HIGH){
                snprintf(Buf, 11, " L=%d>H=%d", low, high);
                lcd_moveto(0, 0);
                lcd_stringout(Buf);
            }
        }

        //LOCAL/REMOTE button
        if((PINC & (1 << 5)) == 0){
            while((PINC & (1 << 5)) == 0){}
            if(rstate == UPPER){
                rstate = LOWER;
                lcd_moveto(0, 10);
                lcd_stringout(" ");
                lcd_moveto(1, 10);
                lcd_stringout("<");
            }
            else{
                rstate = UPPER;
                lcd_moveto(0, 10);
                lcd_stringout("<");
                lcd_moveto(1, 10);
                lcd_stringout(" ");
            }
        }

        //SEND(RIGHT) Button to Transmit Data
        if((PINC & (1 << 0)) == 0){
            while((PINC & (1 << 0)) == 0) {}
            transmit();
        }

        //Receiving Data
        if(flag == 1){
            receive();
        }
    }   
    return 0;   /* never reached */
} 

// ISR for Rotary Encoder
ISR(PCINT2_vect)
{
    uint8_t x = PIND;
    a = x & (1 << PD2);
    a = a >> PD2; 
    b = x & (1 << PD3);
    b = b >> PD3; 
    if (old_state == 0 && rstate == UPPER) { //00
        // Handle A and B inputs for state 0
        if(!b && a){ //from 00 to 01
            new_state = 1;
            if(state == LOW){
                if(low < high) low++;
            }
            else{
                if(high < 90) high++;
            }
        }
        else if(b && !a){//from 00 to 10
            new_state = 2;
            if(state == LOW){
                if(low > 50) low--;
            }
            else{
                if(high > low) high--;
            }
        } 
    }
    else if (old_state == 1 && rstate == UPPER) { //01
        // Handle A and B inputs for state 1
        if(b && a){ //from 01 to 11
            new_state = 3;
            if(state == LOW){
                if(low < high) low++;
            }
            else{
                if(high < 90) high++;
            }
        }
        else if(!b && !a){ //from 01 to 00
            new_state = 0;
            if(state == LOW){
                if(low > 50) low--;
            }
            else{
                if(high > low) high--;
            }
        } 
    }
    else if (old_state == 2 && rstate == UPPER) { //10
        // Handle A and B inputs for state 2
        if(b && a){ //from 10 to 11
            new_state = 3;
            if(state == LOW){
                if(low > 50) low--;
            }
            else{
                if(high > low) high--;
            }
        }
        else if(!b && !a){ //from 10 to 00
            new_state = 0;
            if(state == LOW){
                if(low < high) low++;
            }
            else{
                if(high < 90) high++;
            }
        } 
    }
    else if(old_state == 3 && rstate == UPPER){   // old_state = 3, 11
        // Handle A and B inputs for state 3
        if(!b && a){ //from 11 to 01
            new_state = 1;
            if(state == LOW){
                if(low > 50) low--;
            }
            else{
                if(high > low) high--;
            }
        }
        else if(b && !a){ //from 11 to 10
            new_state = 2;
            if(state == LOW){
                if(low < high) low++;
            }
            else{
                if(high < 90) high++;
            }
        } 
    }
    // If state changed, update the value of old_state,
    // and set a flag that the state has changed.
    if (new_state != old_state) {
        changed = 1;
        old_state = new_state;
    }
}
