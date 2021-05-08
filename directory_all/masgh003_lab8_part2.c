/*	Author: Melody Asghari
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #8  Exercise #2
 *	Exercise Description:
 *	
 *  Using the ATmega1284’s PWM functionality, design a system where the notes:
 *	C4, D, E, F, G, A, B, and C5
 *  a) The system should scale up/down one note per button press.
*   b) When scaling down, the system should not scale below a C.
*   c) When scaling up, the system should not scale above a C.
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
#define checker 0
#define button (~PINA & 0x07)

//C_4 = 261.63 Hz
//D_4 = 293.66 Hz
//E_4 = 329.63 Hz
//F_4 = 349.23 Hz
//G_4 = 392.00 Hz
//A_4 = 440.00 Hz
//B_4 = 493.88 Hz
//C_5 = 523.25 Hz

enum PWM_states { INIT, START, PLAY, STOP, RAISE, LOWER} ostan;
double library[8] = {
    261.63, //C4
    293.66, //D4
    329.63, //E4
    349.23, //F4
    392.00, //G4
    440.00, //A4
    493.88, //B4
    523.25}; //C5
unsigned char key = 8;

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
void player() {
    switch(ostan) {
        case INIT:
        ostan = START;
        break;
        case START:
        if (button == 0x01) {
            ostan = STOP;
            break;
        } else if (button == 0x02) {
            ostan = RAISE;
            break;
        } else if (button == 0x04) {
            ostan = LOWER;
        } else {
            ostan = START;
        }
        break;
        case PLAY:
        if (button== 0x00) {
            ostan = START;
        } else {
            ostan = PLAY;
        }
        break;
        case STOP:
        if (checker == 1) {
            PWM_off();
            checker = 0;
            ostan = PLAY;
            break;
        } else if (checker == 0) {
            PWM_on();
            checker = 1;
            ostan = PLAY;
            break;
        }
        break;
        case RAISE:
        ostan = PLAY;
        break;
        case LOWER:
        ostan = PLAY;
        break;
    }
    switch(ostan) {
        case INIT:
        break;
        case START:
        break;
        case PLAY:
            set_PWM(tone[key]);
            break;
        break;
        case STOP:
        break;
        break;
        case RAISE:
        key++;
        if (key > 7) {
            key = 7;
            break;
        } else {
            key = key;
        } break;
        break;
        case LOWER:
        key--;
        if (key < 0) {
            key = 0;
            break;
        } else {
            key = key;
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
    ostan = INIT;
    PWM_on();
    TimerSet(500);
    TimerOn();
    while (1) {
        player();
        while(!TimerFlag);
        TimerFlag = 0;
    }
    return 1;
}