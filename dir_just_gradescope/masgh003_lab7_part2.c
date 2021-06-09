/*	Author: Melody Asghari
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #7  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 * 	replacing the potentiometer w/ a photoresistor/ 330 ohm resistor.
 *	Take note of the highest ADC value displayed (MAX) when the photoresistor is exposed to light
 *	lowest ADC value displayed (MIN) when the photoresistor is deprived of all light
 *	These values will be used for the remaining lab exercises.
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
	unsigned char b_d = 0x00, b_h = 0x00;
    ADC_init();
    while (1) {
        unsigned short light_value = ADC; //adc is set up
        b_d = (char) light_value;
        b_h = (char) (light_value >> 8);
        PORD = b_h;
        PORTB = b_d;
        }
        
    }
    return 1;
}