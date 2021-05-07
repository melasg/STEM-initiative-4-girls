/*	Author: Melody Asghari
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description:
 * Create a synchSMS to blink 3 LEDs connected to PB0, PB1, and PB2 in sequence
 *	Implement that synchSM in C using defined method in class
 *	PB0, PB1, PB2, ... (repeats x3) ...
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
