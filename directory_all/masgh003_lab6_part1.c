/*	Author: Melody Asghari
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #5  Exercise #1
 *	Exercise Description:
 * A car has a fuel level sensor:
 *	sets PA3...PA0 to val between 0->15 (full)
 *	LEDs connected to PC5...PC0 should light up.
 *	If fuel level is 1 or 2, PC5 lights 
 * If level is 3 or 4, PC5/PC4 light
 *	If 5-6, PC5..PC3
 *	7-9 -> PC5...PC2
 *	10-12 PC5...C1
 *	13-15 PC5...PC0
 *	PC6 connected to LED that lights iff ≥ level 4
 *	buttons PA3...PA0 to mimic fuel level sensor w/ presses
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 * 
 * VIDEO DEMO < URL > 
 */
//#include "../header/timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
/* 
timer.h
*/
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char output = 0x00;
enum States {ROSHAN, LED1, LED2, LED3} ostan;
void TimerOn() {
    TCCR1B = 0x0B;
    OCR1A = 125;
    TIMSK1 = 0x02;
    TCNT1 = 0;
    _avr_timer_cntcurr = _avr_timer_M;
    SREG |= 0x80;
}

void TimerOff() {
    TCCR1B = 0x00;
}
void TimerISR() {
    TimerFlag =1;
}
ISR(TIMER1_COMPA_vect) {
    _avr_timer_cntcurr--;
    if (_avr_timer_cntcurr == 0) {
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}
void TimerSet (unsigned long M) {
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

void flicker() {
    switch(ostan) {
        case ROSHAN:
            ostan = LED1;
            break;
        case LED1:
            ostan = LED2;
            break;
        case LED2:
            ostan = LED3;
            break;
        case LED3:
            ostan = LED1;
            break;
    }
    switch(ostan) {
        case LED1:
            output = 0x01;
            break;
        case LED2:
            output = 0x02;
            break;
        case LED3:
            output = 0x04;
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
    /* Insert your solution below */
    TimerSet(1000); 
    TimerOn(); 
    ostan = ROSHAN; 
    while (1) {
        flicker();
        while (!TimerFlag);
        TimerFlag = 0;
        PORTB = output;
    }
    return 1;
}
