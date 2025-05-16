#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "serial.h"
#include "lcd.h"  

#define FOSC 16000000 // Clock frequency
#define BAUD 9600 // Baud rate used
#define MYUBRR (FOSC/16/BAUD-1) // Value for UBRR0

extern volatile int low;
extern volatile int high;

extern volatile char rx_Buf[6];
extern volatile uint8_t rx_index;
extern volatile uint8_t flag;
extern volatile int temp1; 
extern volatile int temp2;

void serial_init(void){
    // Enable RX and TX
    UCSR0B |= ((1 << TXEN0) | (1 << RXEN0)| (1 << RXCIE0)); 
    UCSR0C = (3 << UCSZ00); // Async., no parity,
                             // 1 stop bit, 8 data bits
    UBRR0 = MYUBRR; // checkpoint 3
}

char rx_char(){
    // Wait for receive complete flag to go high
    while ( !(UCSR0A & (1 << RXC0)) ) {}
    return UDR0;
}

void tx_char(char ch)
{
    // Wait for transmitter data register empty
    while ((UCSR0A & (1<<UDRE0)) == 0) {}
    UDR0 = ch;
}    

void transmit(){
    char rBuf[7];
    snprintf(rBuf, 7, "<%d%d>", low, high);
    for (int i = 0; rBuf[i] != '\0'; i++) {
        tx_char(rBuf[i]);
    }
}

void receive() {
    if (sscanf((const char *)rx_Buf, "%2d%2d", &temp1, &temp2) == 2) { //sscanf returns the number of input arguments 
        char buf[10];                                                  //which will be two temp1 and temp2 here
        snprintf(buf, 10, "L=%d H=%d", temp1, temp2);
        lcd_moveto(1, 1);
        lcd_stringout(buf);
    }
}

ISR(USART_RX_vect) {
    char x = rx_char();
    if (x == '<') { // Protocol Starts with '<'
        rx_index = 0;
        flag = 0;
    }
    else if (x >= '0' && x <= '9') {
            if (rx_index < 4) {
                rx_Buf[rx_index] = x;
                rx_index++;
            } 
            else {
                rx_index = 0;
            }
        }
    else if (x == '>') { // Protocol Ends with '>'
        if (rx_index > 0 && rx_index <= 4) { //Receive total 4 numbers
            rx_Buf[rx_index] = '\0';
            flag = 1;
        }
    }
}
