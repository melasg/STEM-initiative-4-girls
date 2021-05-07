/*	Author: home
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #7  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *  Design a system that
 *		reads the 10-bit ADC result from the ADC register
 *		displays the result on a bank of 10 LEDs.
 *	display the lower 8 bits on port B, and the upper 2 bits on PORTD.
 *	Use a “short” variable to hold the ADC result.
 *	Use bit shifting and casting to align the proper bits to the proper ports.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	
 *	VIDEO DEMO : < URL > 
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tempA, tempC;
void ADC_init() {
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}
int main(void) {
    /* Insert DDR and PORT initializations */
    //from the lecture:
    DDRA = 0x00; PORTA = 0xFF; // LEDS on B7:6
    DDRB = 0xFF; PORTB = 0x00; // LEDS on B7:6
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    ADC_init();
    while (1) {
        unsigned short light_value = ADC; //adc is set up
        tempA = (char) light_value;
        tempC = (char) (light_value >> 8);
        PORTA = tempA;
        PORTC = tempC;
        }
        
    }
    return 1;
}