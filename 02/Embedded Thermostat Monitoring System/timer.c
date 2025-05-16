
#include <avr/io.h>
#include "timer.h"
#include <avr/interrupt.h>
#include <stdbool.h>

extern volatile uint16_t servocnt;
extern volatile uint16_t OCR2Aval;
extern bool servo_active;
extern bool servo_deactive;

//Timer for LED
void timer1_init()
{
    TCCR1A |= (1 << WGM10) | (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13);
    TCCR1B |= (1 << CS11) | (1 << CS10);
    OCR1A = 2499; //set prescalar 64
    OCR1B = OCR1A / 2;
    TIMSK1 |= (1 << OCIE1B) | (1 << TOIE1);
}
ISR(TIMER1_OVF_vect) {
    // Turn the PWM bit on
    PORTC |= (1 << PC3);
}
ISR(TIMER1_COMPB_vect) {
    // Turn the PWM bit off
    PORTC &= ~(1 << PC3);
}

//Timer for Servo Motor
void timer2_init()
{
    DDRB |= (1 << PB3);
    TCCR2A = (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
    TIMSK2 |= (1 << TOIE2);
}

//ISR for Servo Motor
ISR(TIMER2_OVF_vect) {
    if (!servo_active) return;
    servocnt++;
    if (servocnt % 25 == 0 && OCR2Aval > 11) {
        OCR2Aval--;
        OCR2A = OCR2Aval;
    }

    if (servocnt >= 610) {
        servo_active = false;
        servo_deactive = true;
    }
}
