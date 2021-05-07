/*	Author: home
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description:
 *	Buttons connected to PA0 and PA1
 *	Output for PORTB = 7 initially
 *	Pressing PA0 = increment once (stops at 9)
 *	Pressing PA1 = decrements once PORTB (stops at 0)
 * NOW WITH TIMING: check to see if a button has been pressed every 100 ms
 * if button is held, then the count should continue to inc/dec at a rate of 1/s
 *
 * VIDEO demo: < URL >
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum state {ROSHAN, RESET, S1, S2, S3, S4, S5, W1, W2, W3, W4, W5, W6} ostan;
  unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
  unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
unsigned char count=0;
//time stuff:
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
            ostan = RESET;
            break;
        case RESET:
            if (tmpA) {
                ostan = W1;
            } else {
                ostan = RESET;
            }
            break;
        case S1:
        if (tmpA) {
            ostan = W2;
        } else {
            ostan = S1;
        }
            break;
        case S2:
        if (tmpA) {
            ostan = W3;
        } else {
            ostan = S2;
        }
        break;
        case S3:
            if (tmpA) {
                ostan = W4;
            } else {
                ostan = S3;
            }
        break;
        case S4:
        if (tmpA) {
            ostan = W5;
        } else {
            ostan = S4;
        }
        break;
        case S5:
        if (tmpA) {
            ostan = W6;
        } else {
            ostan = S5;
        }
        break;
        case W1:
        if (!tmpA) {
            ostan = S1;
        } else {
            ostan = W1;
        }
        break;
        case W2:
        if (!tmpA) {
            ostan =S2;
        } else {
            ostan = W2;
        }
        break;
        case W3:
        if (!tmpA) {
            ostan = S3;
        } else {
            ostan = W3;
        }
        break;
        case W4:
        if (!tmpA) {
            ostan = S4;
        } else {
            ostan = W4;
        }
        break;
        case W5:
        if (!tmpA) {
            ostan = S5;
        } else {
            ostan = W5;
        }
        break;
        case W6:
        if (!tmpA) {
            ostan = RESET;
        } else {
            ostan = W6;
        }
        break;
    }
    switch(ostan){
    
    }
}
int main(void) {
    /* Insert DDR and PORT initializations */
 DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as tmpBs, initialize to 0s
    /* Insert your solution below */
    TimerSet(300);
    TimerOn();
    ostan = ROSHAN;
    while (1) {
        while(!TimerFlag);
        TimerFlag = 0;
        tmpA = ~PINA & 0x01;
        tmpB = ~PINA & 0x02;
        flicker();
        PORTC = tmpB;
    }
    return 1;
}
