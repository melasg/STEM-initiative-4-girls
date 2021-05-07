/*	Author: home
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #8  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *  Use the tones C4, D4, and E4 from the table in the introduction section.
*   When a button is pressed and held, the tone mapped to it is generated on the speaker.
*   When more than one button is pressed simultaneously, the speaker remains silent. 
*   When no buttons are pressed, the speaker remains silent.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#define button (~PINA & 0x07)
enum PWM_states { INIT, START, PLAY, STOP} ostan;
static double C4 = 261.63, D4 = 293.66, E4 = 329.63; //no magic numbers
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

void musicbox() {
    switch (ostan) {
        case INIT:
        ostan = START;
        break;
        case START:
        if (button != 0x00) {
            ostan = PLAY;
            break;
        } else {
            ostan = INIT;
            break;
        }
        case PLAY:
        if (button != 0x00){ 
            ostan = PLAY;
            break;
        } else {
            ostan = STOP;
            break;
        }
        case STOP:
        ostan = INIT;
        break;
    }
    switch (ostan) {
       case INIT:
        break;
        case START:
        set_PWM(0);
        break;
        case PLAY:
        if (button == 0x01){
            set_PWM(C4);
            break;
        } else if (button == 0x02){
            set_PWM(D4);
            break;
        } else if (button == 0x04) {
            set_PWM(E4);
            break;
        }
        break;
        case STOP:
        set_PWM(0);
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
