/*	Author: home
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 * PB0 and PB1 each connect to an LED, and PB0's LED is initially on. Pressing a button connected to PA0 turns off PB0's LED and turns on PB1's LED, staying that way after button release. Pressing the button again turns off PB1's LED and turns on PB0's LED. 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned char tempA = 0x00, tempC = 0x00;
//#define P_B0 (~PINA & 0x00)
//#define P_B1 (~PINA & 0x01)
//unsigned char tempA = 0x00, tempC = 0x00;
enum SM_1 {INIT, PRESS_1, PRESS_2, REL_1, REL_2} ostan;

void tick() {
    switch (ostan) {
        case INIT:
        ostan = REL_2;
        break;
        case PRESS_1:
        if (PINA & 0x01) {
            ostan = PRESS_1;
            break;
        } else {
            ostan = REL_1;
            break;
        }
        case PRESS_2:
        if (PINA & 0x01) {
            ostan = PRESS_2;
            break;
        } else {
            ostan = REL_2;
            break;
        }
        case REL_1:
        if (PINA & 0x01) {
            ostan = PRESS_2;
            break;
        } else {
            ostan = REL_1;
            break;
        }
        case REL_2:
        if (PINA & 0x01) {
            ostan = PRESS_1;
            break;
        } else {
            ostan = REL_2;
            break;
        }
    }
    switch (ostan) {
        case INIT:
        break;
        case PRESS_1:
        PORTC = 0x02;
        break;
        case PRESS_2:
        PORTC = 0x01;
        break;
        case REL_1:
        break;
        case REL_2:
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
		 tick();
    }
    return 1;
}
