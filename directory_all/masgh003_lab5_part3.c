/*	Author: Melody Asghari
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *  Create your own festive lights display with 6 LEDs connected to port P_B5..P_B0, lighting in some attractive sequence. Pressing the button on PA0 changes the lights to the next configuration in the sequence.  
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//SM constants
#define P_B5 (~PINA & 0x00)
#define P_B4 (~PINA & 0x01 || ~PINA & 0x02)
#define P_B3 (~PINA & 0x03 || ~PINA & 0x04 )
#define P_B2 (~PINA & 0x05 || ~PINA & 0x06)
#define P_B1 (~PINA & 0x07 || ~PINA & 0x08 || ~PINA & 0x09)
#define P_B0 (~PINA & 0x0A || ~PINA & 0x0B || ~PINA & 0x0C )
#define output PORTC
enum StateOfAffairs {INIT, START, FLASH, WAIT} ostan;
void tick() {
    switch (ostan) {
        case INIT:
        output = 0x00;
        ostan = START;
        break;
        case START:
        if (P_B4) {
            ostan = FLASH;
        } else {
            ostan = START;
        }
        break;
        case FLASH:
        ostan = WAIT;
        break;
        case WAIT:
        if (P_B4) {
            ostan = WAIT;
        } else if (P_B4 && P_B5) {
            ostan = START;
        }
        break; 
        default:
        break;
    }
    switch (ostan) {
        case INIT:
        break;
        case START:
        break;
        case FLASH:
        if (output == 0x00) {
            output = 0x01;
        } else if (output == 0x1F) {
            output = 0x00;
        } else {
            output = (output << 1);
            if ((output & 0x04) == 0x04) {
                output = output | 0x01;
            }
        }
        break;
        case WAIT:
        break;
        default:
        break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;
    /* Insert your solution below */
    ostan = INIT;
    while (1) {
        if (PB1 == P_B5) { //tbh i m confused
            tick();
        }
    }
    return 1;
}
