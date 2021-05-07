/*	Author: home
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #7  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 * If the result of the ADC is >= MAX/2, the LED is illuminated.
*   If the result of the ADC is < MAX/2, the LED is turned off.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	
 *	VIDEO : < URL >
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
const unsigned short max;
unsigned short light_state;
unsigned char tempB;

void ADC_init() {
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    ADC_init();
    while (1) {
        if (light_state >= (max/2)) {
            tempB = 0x01;
        } else {
            tempB = 0x00;
        }
        PORTB = tempB;
    }
    return 1;
}
