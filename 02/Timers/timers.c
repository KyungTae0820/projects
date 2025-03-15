#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd.h"

void debounce(uint8_t);
void timer1_init(void);

enum states
{
    PAUSE,
    StartRUN,
    RUN,
    LAPPED
};
volatile int flag = 0;

int main(void)
{

    uint8_t state;

    // Initialize the LCD and TIMER1
    lcd_init();
    timer1_init();

    // Enable pull-ups for buttons
    DDRC &= ~((1 << 2) | (1 << 4));
    PORTC |= ((1 << 2) | (1 << 4)); // 2 is for start/stop, 4 is for Lap/restart

    DDRC |= (1 << PC5); // Task 3

    // Show the splash screen
    lcd_writecommand(1);
    lcd_moveto(0, 5);
    lcd_stringout("KT Kim");
    lcd_moveto(1, 2);
    lcd_stringout("EE109 Lab 5");
    _delay_ms(1000);
    lcd_writecommand(1);
    // Enable interrupts
    sei();

    char states = PAUSE;
    unsigned char cnt = 0;
    unsigned char sec = 0;
    unsigned char tensec = 0;
    unsigned char lapcnt = 0;
    unsigned char lapsec = 0;
    unsigned char laptensec = 0;

    while (1)
    { // Loop forever

        // Read the buttons
        if (states == PAUSE)
        { // PAUSE state
            if ((PINC & (1 << 2)) == 0)
            {
                states = StartRUN;
            }
            else if ((PINC & (1 << 4)) == 0)
            {
                debounce(4);
                cnt = 0;
                sec = 0;
                tensec = 0;
                lapcnt = 0;
                lapsec = 0;
                laptensec = 0;
                state = PAUSE;
            }
        }
        else if (states == StartRUN)
        {
            if ((PINC & (1 << 2)) != 0)
            {
                states = RUN;
            }
        }
        else if (states == RUN)
        { // RUN state
            if ((PINC & (1 << 2)) == 0)
            { // start/stop button pressed
                debounce(2);
                states = PAUSE;
            }
            else if ((PINC & (1 << 4)) == 0)
            { // lap/reset button pressed
                debounce(4);
                states = LAPPED;
                flag = 2;
                if (flag == 2)
                {
                    lapcnt = cnt;
                    lapsec = sec;
                    laptensec = tensec;
                    flag = 1;
                }
            }
        }
        else if (states == LAPPED)
        { // LAPPED state
            if ((PINC & (1 << 2)) == 0)
            { // start/stop button pressed
                debounce(2);
                states = RUN;
            }
            else if ((PINC & (1 << 4)) == 0)
            {
                debounce(4);
                states = RUN;
            }
        }

        // If necessary write time to LCD
        if (states == StartRUN || states == RUN || states == LAPPED)
        {
            if (flag == 1)
            {
                if (cnt < 9)
                {
                    cnt++;
                }
                else
                {
                    cnt = 0;
                    if (sec < 9)
                    {
                        sec++;
                    }
                    else
                    {
                        sec = 0;
                        if (tensec < 5)
                        {
                            tensec++;
                        }
                        else
                        {
                            tensec = 0;
                        }
                    }
                }
            }
        }
        // Perform the output operations if necessary
        if (states == LAPPED)
        {
            lcd_writecommand(1);
            if (laptensec != 0)
            {
                lcd_moveto(0, 0);
                lcd_writedata(laptensec + '0');
            }
            lcd_moveto(0, 1);
            lcd_writedata(lapsec + '0');
            lcd_moveto(0, 2);
            lcd_writedata('.');
            lcd_moveto(0, 3);
            lcd_writedata(lapcnt + '0');
            // Delay before we go to the next iteration of the loop
            _delay_ms(100);
        }
        else
        {
            lcd_writecommand(1);
            if (tensec != 0)
            {
                lcd_moveto(0, 0);
                lcd_writedata(tensec + '0');
            }
            lcd_moveto(0, 1);
            lcd_writedata(sec + '0');
            lcd_moveto(0, 2);
            lcd_writedata('.');
            lcd_moveto(0, 3);
            lcd_writedata(cnt + '0');
            // Delay before we go to the next iteration of the loop
            _delay_ms(100);
        }
    }
    return 0; /* never reached */
}

/* ----------------------------------------------------------------------- */

void debounce(uint8_t bit)
{
    // Add code to debounce input "bit" of PINC
    // assuming we have sensed the start of a press.
    if ((PINC & (1 << bit)) == 0)
    {
        _delay_ms(5);
        while ((PINC & (1 << bit)) == 0)
        {
        }
        _delay_ms(5);
    }
}

/* ----------------------------------------------------------------------- */

void timer1_init(void)
{
    // Add code to configure TIMER1 by setting or clearing bits in
    // the TIMER1 registers.
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12); // 256, 100
    TIMSK1 |= (1 << OCIE1A);
    OCR1A = 6250; //0.1s w/ 16 MHz clock
}

ISR(TIMER1_COMPA_vect)
{
    // Increment the time
    // PORTC ^= (1 << PC5);
    flag = 1; 
}
