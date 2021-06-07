/*	Author: Melody Asghari
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #8  Exercise #3
 *	Exercise Description:
 *	
 *   Using the ATmega1284’s built in PWM functionality
 *	HAS TO BE COMPLEX, NOT C->B
 *		design a system where a short, five-second melody, is played when a button is pressed.
 *  When the button is pressed
 *	a)	the melody should play until completion
 *  b) 	Pressing the button again in the middle of the melody should do nothing
 *  c) 	If the button is pressed and held, when the melody finishes
 *		it should not repeat until the button is released and pressed again
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	
 *	VIDEO DEMO: < URL >
 *	
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//#define button (~PINA & 0x01)


//static double C4 = 261.63, D4 = 293.66, E4 = 329.63; //no magic numbers
// //rest of the library
// static double F4 =349.23,G4 =392.00,A4 =440.00,B4 = 493.88,C5 =523.25;

//PWM stuff here: (retyped from lab manual)
void set_PWM(double frequency) {
    static double current_frequency;
    if (frequency != current_frequency) {
        if (!frequency) {
            TCCR3B &= 0x08;
        } else {
            TCCR3B |= 0x03;
        }
        if (frequency < 0.954) {
            OCR3A = 0xFFFF;
        } else if (frequency > 31250) {
            OCR3A = 0x0000;
        } else {
            OCR3A = (short)(8000000 / (128 * frequency)) - 1;
        }
        TCNT3 = 0;
        current_frequency = frequency;
    }
}

void PWM_on() {
    TCCR3A = (1 << COM3A);
    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
    set_PWM(0);
}

void PWM_off(){
    TCCR3A = 0x00;
    TCCR3B = 0x00;
}

//just put the timer stuff here:
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
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
    TimerFlag = 1;
}

void TimerSet(unsigned long M) {
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

ISR(TIMER1_COMPA_vect) {
    _avr_timer_cntcurr--;
    if (_avr_timer_cntcurr == 0) {
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}
//One approach is to use three arrays.
//One array holds the sequence of notes for the melody.
//Another array holds the times that each note is held.
//The final array holds the down times between adjacent notes.


//C_4 = 261.63 Hz
//D_4 = 293.66 Hz
//E_4 = 329.63 Hz
//F_4 = 349.23 Hz
//G_4 = 392.00 Hz
//A_4 = 440.00 Hz
//B_4 = 493.88 Hz
//C_5 = 523.25 Hz


double library[10] = {
	0,		//idk what this is
    261.63, //C4
    293.66, //D4
    329.63, //E4
    349.23, //F4
    392.00, //G4
    440.00, //A4
    493.88, //B4
    523.25 }; //C5
unsigned char key = 0x00;
unsigned complex[4][4] = {{2,1,9,3},{1,5,7,4},{8,2,4,1},{5,2,6,4}};

enum PWM_states { init, tran, P_A0, R_A0, H_A0} ostan;
unsigned char buttonctrl = (~PINA & 0x01);
void player() {
	switch (ostan) {
		case init:
				ostan = st1;
			break;
		case tran:
				if (buttonctrl) {
					ostan = P_A0;
				}
			break;
		case P_A0:
				if (!buttonctrl) {
					ostan = R_A0;
				}
			break;
		case R_A0:
				if (buttonctrl && (key == 26)) {
					ostan = H_A0;
				} else {
					key = (key == 26) ? 0x01 : (key + 1);
				}
			break;
		case H_A0:
				key = 0x00;
				if (!buttonctrl) {
					ostan = tran;
				}
			break;
	}
}
//scaling from C to B is NOT complex
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */

    PWM_on();
//    TimerSet(500);
    TimerOn();

    while (1) {
        while(!TimerFlag);
        TimerFlag = 0;        
        PORTB = PORTB | (1 << (PORTB & 0x03));
        player();
        TimerSet((complex[1][key] * 7 ))
        set_PWM(library[complex[0][key]]);
    }
    return 1;
}