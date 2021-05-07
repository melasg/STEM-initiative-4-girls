/*	Author: Melody Asghari
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: 
 *	Create a simple light game that requires pressing a button on PA0
 * while middle 3 LEDs on PB0, PB1, and PB2 is lit
 *	LEDs light for 300 ms each in sequence
 *	When button pressed = current LED stays lit
 * Pressing button again resets the game
 *	video demo: < URL >
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum state {ROSHAN, LED1, LED2, LED3, STOP1, STOP2, STOP3} ostan;
  unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
  unsigned char tmpA = 0x00; // Temporary variable to hold the value of A

/*
Timer stuff
*/
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
    TCCR1B = 0x0B;
    OCR1A = 125;
    TIMSK1 = 0x02;
    TCNT1 = 0;
    _avr_timer_cntcurr = _avr_timer_M;
    SREG |= 0;
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
            if (tmpA) {
                ostan = STOP1;
            }
            ostan = LED2;
            break;
        case LED2:
            ostan = LED3;
            break;
        case LED3:
            ostan = LED1;
            break;
        case STOP1:
            if (tmpA) {
                ostan = STOP1;
            } else {
                ostan = STOP1;
            }
            break;
        case STOP2:
            if (tmpA) {
                ostan = STOP2;
            } else {
                ostan = STOP2;
            }
            break;
        case STOP3:
            if (tmpA) {
                ostan = STOP3;
            } else {
                ostan = STOP3;
            }
            break;
    }
    switch(ostan) {
        case ROSHAN:
            tmpB = 0;
            break;
        case LED1:
            tmpB = 0x01;
            break;
        case LED2:
            tmpB = 0x02;
            break;
        case LED3:
            tmpB = 0x04;
            break;
        case STOP1:
            tmpB = 0x01;
            break;
        case STOP2:
            tmpB = 0x02;
            break;
        case STOP3:
            tmpB = 0x04;
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
  DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
    /* Insert your solution below */
    TimerSet(300); 
    TimerOn(); 
    ostan = ROSHAN;
    tmpB = 0;
    while (1) {
            tmpA = PINA & 0x03;
            flicker();
            PORTB = tmpB;
            }
    return 1;
}
