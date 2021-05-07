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

enum state {init, start, blink, press_button1, press_button2, release_buttons} ostan;
  unsigned char buttons = 0; 
  unsigned char tmpB = 0x00; // Temporary variable to hold the value of B

void tick() {
	TimerSet(300);
	TimerOn();
	switch (ostan) {
		case init:
		ostan = 0x01;
		buttons = 0x01;
			break;
		case start:
			if (buttons) {
				ostan = press_button1;
			} else {
				ostan = blink;
			}
		break;
		case blink:
			ostan = start;
		break;
		case press_button1:
		if (!button) {
			ostan = press_button2;
		}
		break;
		case press_button2:
			if (buttons) {
				ostan = release_buttons;
			}
		break;
		case release_buttons:
			if (!buttons) {
				ostan = start;
			}
		break;
		default:
		break;
	}
	
	switch (ostan) {
		case init:
		
		break;
		case start:
			while(!TimerFlag) {
				buttons = ~PINA & 0x01;
			}
			TimerFlag = 0;
			PORTB = tmpB;
			tmpB = (tmpB == 0x04) ? 0x01: tmpB << 1;
		break;
		case blink:
		break;
		case press_button1:
		ostan = press_button1;
		break;
		case press_button2:
		break;
		case release_buttons:
		break;
		default:
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
//    ostan = init;
//    tmpB = 0;
    while (1) {
//            tmpA = PINA & 0x03;
            tick();
//            PORTB = tmpB;
            }
    return 1;
}
