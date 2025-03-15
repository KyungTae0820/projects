#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "lcd.h"

void play_note(uint16_t);
void variable_delay_us(int16_t);
void timer1_init();

// Frequencies for natural notes from middle C (C4)
// up one octave to C5.
uint16_t frequency[8] =
    { 262, 294, 330, 349, 392, 440, 494, 523 };

volatile uint8_t new_state, old_state;
volatile uint8_t changed = 0;  // Flag for state change
volatile int16_t count = 0;		// Count to display
volatile uint8_t a, b;

volatile uint16_t numb_time = 0; //Set a global variable to how many times the ISR needs to run 

int main(void) {

    // Initialize DDR and PORT registers and LCD
	lcd_init();
	timer1_init();
	DDRB |= (1 << PB4);
	PORTC |= (1 << PC1) | (1 << PC5);
	PORTB &= ~(1 << PB4);
	PCICR |= (1 << PCIE1); //enable the pin change interrupts on Port C (PCINT1).
	PCMSK1 |= ((1 << PCINT9) | (1 << PCINT13)); //mask register to enable interrupts for the PC1 and PC5 I/O lines. For PC1 and PC5
	sei(); //global interrupt

    // Write a splash screen to the LCD
		char buf[12];
		lcd_writecommand(1);
		lcd_moveto(0, 5);
		lcd_stringout("KT Kim");
		lcd_moveto(1, 3);
		snprintf(buf, 12, "%d/%02d/%d", 2002, 8, 20);
		lcd_stringout(buf);
		_delay_ms(1000);
		lcd_writecommand(1);

    // Read the A and B inputs to determine the intial state.
    // In the state number, B is the MSB and A is the LSB.
    // Warning: Do NOT read A and B separately.
	uint8_t x = PINC;
	a = x & (1 << PC1);
	a = a >> 1; //set to 1, if not a will set to 2
	b = x & (1 << PC5);
	b = b >> 5; //set to 5, if not b will set to 32

    if (!b && !a) //both 00
	old_state = 0;
    else if (!b && a) //01 
	old_state = 1;
    else if (b && !a) //10
	old_state = 2;
    else //11
	old_state = 3;

    new_state = old_state;

	lcd_writecommand(1);
	char buf2[16]; //changed from 10 to 16
	snprintf(buf2, 16, "A=%d B=%d", a, b);
	lcd_moveto(0, 0);
	lcd_stringout(buf2);
	
	// Output count to LCD
	lcd_moveto(1,0);
	snprintf(buf2,16, "Count is %d", count);
	lcd_stringout(buf2);

    while (1) {                 // Loop forever


        if (changed) { // Did state change?
	    changed = 0;        // Reset changed flag

			//Output A and B
			lcd_writecommand(1);
			char buf[16]; //changed from 10 to 16
			snprintf(buf, 16, "A=%d B=%d", a, b);
			lcd_moveto(0, 0);
			lcd_stringout(buf);
			
			// Output count to LCD
			lcd_moveto(1,0);
			snprintf(buf,16, "Count is %d", count);
			lcd_stringout(buf);

			// Play a note?
			if ((count % 8) == 0) {
				// Determine which note (0-7) to play
				// Find the frequency of the note
				int16_t x = count;
				if (x < 0) x = -x;

				uint16_t freqEnum = frequency[((x%64)/8)]; //combine the upper two
				// Call play_note and pass it the frequency
				play_note(freqEnum);
			}
        }
    }
}

/*
  Play a tone at the frequency specified for one second 
*/
void play_note(uint16_t freq)
{
    // uint32_t period;

    // period = 1000000 / freq;    // Period of note in microseconds

    // while (freq--) {
	// PORTB |= (1 << PB4);    // Buzzer output high
	// variable_delay_us(period / 2);  // Delay for half the period
	// PORTB &= ~(1 << PB4);   // Buzzer output log
	// variable_delay_us(period / 2);  // Delay for half the period
    // }
	OCR1A = (16000000/(2*freq)) - 1; 
	TCCR1B |= (1 << CS10); //set prescalar to 1
	numb_time = 2*freq;
	//variable_delay_us(numb_time);
}

/*
    variable_delay_us - Delay a variable number of microseconds
*/
void variable_delay_us(int delay)
{
    int i = (delay + 5) / 10;

    while (i--)
        _delay_us(10);
}

ISR(PCINT1_vect)
{
    // add code to read the encoder inputs and determine the new
    // count value.
	// Read the input bits and determine A and B.
	uint8_t x = PINC;
	a = x & (1 << PC1);
	a = a >> 1; //set to 1, if not a will set to 2
	b = x & (1 << PC5);
	b = b >> 5; //set to 5, if not b will set to 32
	// For each state, examine the two input bits to see if state
	// has changed, and if so set "new_state" to the new state,
	// and adjust the count value.
	if (old_state == 0) { //00

		// Handle A and B inputs for state 0
		if(!b && a){ //from 00 to 01
			count++;
			new_state = 1;
		}

		else if(b && !a){//from 00 to 10
			count--;
			new_state = 2;
		} 
	}
	else if (old_state == 1) { //01

		// Handle A and B inputs for state 1
		if(b && a){ //from 01 to 11
			count++;
			new_state = 3;
		}

		else if(!b && !a){ //from 01 to 00
			count--;
			new_state = 0;
		} 
	}
	else if (old_state == 2) { //10

		// Handle A and B inputs for state 2
		if(b && a){ //from 10 to 11
			count--;
			new_state = 3;
		}

		else if(!b && !a){ //from 10 to 00
			count++;
			new_state = 0;
		} 
	}
	else {   // old_state = 3, 11

		// Handle A and B inputs for state 3
		if(!b && a){ //from 11 to 01
			count--;
			new_state = 1;
		}
		else if(b && !a){ //from 11 to 10
			count++;
			new_state = 2;
		} 
	}

	// If state changed, update the value of old_state,
	// and set a flag that the state has changed.
	if (new_state != old_state) {
		changed = 1;
		old_state = new_state;
	}

}

void timer1_init()
{
    // Add code to inititialize TIMER1, but don't start it counting
	TCCR1B |= (1 << WGM12); //Set the bits to put TIMER1 in CTC mode.
	TIMSK1 |= (1 << OCIE1A); //Enable interrupts by setting the OCIE1A bit to a one.
}

ISR(TIMER1_COMPA_vect)
{
    // Add code to change the output bit to the buzzer, and to turn
    // off the timer after enough periods of the signal have gone by.
	PORTB ^= (1 << PB4);
	if(--numb_time == 0){
		TCCR1B &= ~(1 << CS10); //clear the Timer bit
	}

}