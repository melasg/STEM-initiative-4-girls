/*	Author: Melody Asghari
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #8  Exercise #1
 *	Exercise Description: 
 *  a) Use the tones C4, D4, and E4 
*   b) When a button is pressed and held, the tone mapped to it is generated on the speaker.
*   c) When more than one button is pressed simultaneously, the speaker remains silent. 
*   d) When no buttons are pressed, the speaker remains silent.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	
 *	VIDEO DEMO: < URL >
 *	
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//#define button (~PINA & 0x07)

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

//Use the tones C4, D4, and E4 from the table in the introduction section.
//C_4 = 261.63 Hz
//D_4 = 293.66 Hz
//E_4 = 329.63 Hz
//F_4 = 349.23 Hz
//G_4 = 392.00 Hz
//A_4 = 440.00 Hz
//B_4 = 493.88 Hz
//C_5 = 523.25 Hz
//enum PWM_states { INIT, START, PLAY, STOP} ostan;
static double C4 = 261.63, D4 = 293.66, E4 = 329.63; //no magic numbers
void musicbox() {
	switch (~PINA & 0x07) {
	case 0x01:
			set_PWM(261.63);
		break;
	case 0x02:
			set_PWM(293.66);
		break;
	case 0x04:
			set_PWM(329.63);
		break;	
	default:
			set_PWM(0.0);
		break;
		}
    }
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    ostan = INIT;
    PWM_on();
    TimerSet(50);
    TimerOn();
    while (1) {
        musicbox();
    }
    return 1;
}
