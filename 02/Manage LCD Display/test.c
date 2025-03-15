#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

enum states
{
    UP,
    DOWN,
    PAUSE
};

int main(void)
{

    // Setup DDR and PORT bits for the 3 input buttons as necessary
    DDRC &= ~((1 << 2) | (1 << 4));
    PORTC |= ((1 << 2) | (1 << 4));
    DDRB &= ~(1 << 3);
    PORTB |= (1 << 3);
    // Initialize the LCD
    lcd_init();
    // lcd_writecommand(1);

    // Use a state machine approach to organize your code
    //   - Declare and initialize a variable to track what state you
    //     are in by assigning the values UP, DOWN or PAUSE to that variable.
    char states = UP;
    unsigned char cnt = 0;
    int threshhold = 0;
    while (1)
    { // Loop forever
        // lcd_writedata(0);
        //  Use "if" statements to read the buttons and determine which
        //  state you are in
        if ((PINC & (1 << 2)) == 0)
        {
           states = UP;
        }
        else if ((PINC & (1 << 4)) == 0)
        {
           states = DOWN;
        }
        else if ((PINB & (1 << 3)) == 0) {
            states = PAUSE;
        }

        // Based on the current state, determine the new count value
        if(threshhold % 10 == 0){ //using modulo to make the buttons always change the counter direction regardlessof when they are pressed or for how long
            threshhold = 0;
            if (states == UP)
            {
                if (cnt < 9)
                {
                    cnt++;
                }
                else
                {
                    cnt = 0;
                }
            }
            else if (states == DOWN)
            {
                if (cnt > 0)
                {
                    cnt--;
                }
                else
                {
                    cnt = 9;
                }
            }
        }
        threshhold++;
        // Perform the output operations if necessary
        lcd_writecommand(1);
        lcd_writedata(cnt + '0');
        // Delay before we go to the next iteration of the loop
        _delay_ms(50);
    }

    return 0; /* never reached */
}
