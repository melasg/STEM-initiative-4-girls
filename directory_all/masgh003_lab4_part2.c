/*	Author: home
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_1 {INIT, INC, DEC, WAIT, RESET} ostan;
void tick() {
    switch(ostan) {
        case INIT:
        PORTC = 0x07;
        if ((PINA & 0x03) == 0x01) {
            ostan = INC;
            break;
        } else if ((PINA & 0x03) == 0x02) {
            ostan = DEC;
            break;
        }
        else if ((PINA & 0x03) == 0x03) 
        {
            ostan = RESET;
            break;
        } else {
            ostan = INIT;
            break;
        }
        case INC:
        if (PORTC >= 0x09) {
            PORTC = 0x09;
            ostan = WAIT;
            break;
        } else {
            PORTC = PORTC + 0x01;
            ostan = WAIT;
            break;
        }
        case DEC:
        if (PORTC <= 0x00) {
            PORTC = 0x00;
            ostan = WAIT;
            break;
        } else {
            PORTC = PORTC - 0x01;
            ostan = WAIT;
            break;
        }
        case WAIT:
        if ((PINA & 0x03) == 0x01) {
            ostan = INC;
            break;
        } else if ((PINA & 0x03) == 0x02) {
            ostan = DEC;
            break;
        } else if ((PINA & 0x03) == 0x03) {
            ostan = RESET;
            break;
        } else {
            ostan = WAIT;
            break;
        }
        break;
        case RESET:
        if ((PINA & 0x03) == 0x03) {
            ostan = RESET;
            PORTC = 0x07;
            break;

        } else {
            ostan = INIT;
            break;
        }
        break;
    }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;
    ostan = INIT;
    /* Insert your solution below */
    while (1) {
        tick();
    }
    return 1;
}
