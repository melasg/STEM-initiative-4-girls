/*	Author: home
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #8  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *   Using the ATmega1284’s built in PWM functionality, design a system where a short, five-second melody, is played when a button is pressed.
 *  When the button is pressed, the melody should play until completion
 *  Pressing the button again in the middle of the melody should do nothing
 *  If the button is pressed and held, when the melody finishes, it should not repeat until the button is released and pressed again
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#define button (~PINA & 0x01)
enum PWM_states { INIT, START, PLAY, STOP} ostan;
double library[9] = {
    261.63, //C4
    293.66, //D4
    329.63, //E4
    349.23, //F4
    392.00, //G4
    440.00, //A4
    493.88, //B4
    523.25}; //C5
unsigned char key = 9;

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
            ostan = PLAY;
            break;
        } else {
            ostan = START;
        }
        break;
        case PLAY:
        break;
        case STOP:
        ostan = PLAY;
        break;
    }
    switch(ostan) {
        case INIT:
        break;
        case START:
        set_PWM(0);
        break;
        case PLAY:
        if (key > 0){
            set_PWM(tone[key]);
            key--;
            ostan = STOP;
        }
        break;
        case STOP:
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