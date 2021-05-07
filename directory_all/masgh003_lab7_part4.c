/*	Author: home
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #7  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *   Design a system, using a bank of eight LEDs, where the number of LEDs illuminated is a representation of how much light is detected. For example, when more light is detected, more LEDs are illuminated. 
 *  The LEDs should illuminated in sequence from 0 to 7, based on the amount of light detected by the photoresistor.
 *	use the max adc val observed from ex.2 as the highest amount of light detectable
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	
 *	VIDEO DEMO: < URL > 
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
const unsigned short max = 0x00;
unsigned short a = 0x00, b = 0x00;
void ADC_init() {
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}
void process(){
    //The LEDs should illuminated in sequence from 0 to 7, based on the amount of light detected by the photoresistor.
    if (a > max) {
        max = a;
        b = (max /8);
    } else if (a <= b){
        PORTB = 0x00;
    }
    else if (a <= (b*2)) {
        0x01
    } else if (a <= (b*3)) {
        0x03
    }
    else if(a <= (b*4)) {
        PORTB = 0x07;
    } else if (a <= (b*5)) {
        PORTB = 0x0F;
    } else if (a <= (b*6)) {
        PORTB = 0x1F;
    } else if (a <= (b*7)) {
        PORTB = 0x3F;
    } else if (a <= (b*8)) {
        PORTB = 0x7F;
    } else {
        PORTB = 0xFF;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    ADC_init();
    /* Insert your solution below */
    while (1) {
        light_state = ADC;
        process();
    }
    return 1;
}
