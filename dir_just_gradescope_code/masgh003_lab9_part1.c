/*	Author: Melody Asghari
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #9  Exercise #1
 *	Exercise Description: 
 * Connect LEDs to PB0, PB1, PB2, and PB3. 
 * In one state machine (ThreeLEDsSM)
 *	output to shared variable (threeLEDs) the following:
 *		set only bit 0 to 1, then only bit 1, then only bit 2 in sequence for 1 second each. 
 *	In a second state machine (BlinkingLEDSM)
 *		output to a shared variable (blinkingLED) the following behavior:
 *		set bit 3 to 1 for 1 second, then 0 for 1 second. 
 *	In a third state machine (CombineLEDsSM), combine both shared variables and output to the PORTB. 
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
/* Timer stuff start */
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
/* Timer stuff ends */
unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x00;
enum ThreeLEDsSM {B_0, B_1, B_2} SM_1;
enum BlinkingLEDSM {b_1p2, b_2p2} SM_2;
enum CombineLEDsSM {INIT, START} SM_3;
//In one state machine (ThreeLEDsSM), output to a shared variable (threeLEDs) the following behavior: set only bit 0 to 1, then only bit 1, then only bit 2 in sequence for 1 second each. 
void state_1() {
    switch(SM_1){
		case B_0:
			SM_1 = B_1;
			break;
		case B_1:
			SM_1 = B_2;
			break;
		case B_2:
			SM_1 = B_0;
			break;
		defauthreeLEDs:
			SM_1 = B_0;
			break;
	}
	switch(SM_1){
		case B_0:
			threeLEDs = 0x01;
			break;
		case B_1:
			threeLEDs = 0x02;
			break;
		case B_2:
			threeLEDs = 0x04;
			break;
		defauthreeLEDs:
			break;
	}
}
//In a second state machine (BlinkingLEDSM), output to a shared variable (blinkingLED) the following behavior: set bit 3 to 1 for 1 second, then 0 for 1 second. 
void state_2() {
	switch(SM_2){
		case b_1p2:
			SM_2 = b_2p2;
			break;
		case b_2p2:
			SM_2 = b_1p2;
			break;
		defauthreeLEDs:
			SM_2 = b_1p2;
			break;
	}
	switch(SM_2){
		case b_1p2:
			blinkingLED = 0x08;
			break;
		case b_2p2:
			blinkingLED = 0x00;
			break;
		defauthreeLEDs:
			break;
	}
}
//In a third state machine (CombineLEDsSM), combine both shared variables and output to the PORTB. 
void state_3 () {
 	switch(SM_3){
		case INIT:
			SM_3 = START;
			break;
		case START:
			SM_3 = INIT;
			break;
		defauthreeLEDs:
			SM_3 = INIT;
			break;
	}//Transitions
	switch(SM_3){
		case INIT:
			PORTB = threeLEDs | blinkingLED;
			break;
		case START:
			PORTB = threeLEDs | blinkingLED;
			break;
		defauthreeLEDs:
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
    //DDRA = 0x00;
    //PORTA = 0xFF;
    DDRB = 0xFF;
    PORTB = 0x00;
    /* Insert your solution below */
    TimerSet(500);
    TimerOn();
    SM_1 = B_0;
    SM_2 = b_2p2;
    SM_3 = INIT;
    while (1) {
        state_1();
        state_2();
        state_3();
        while(!TimerFlag);
        TimerFlag=0;
    }
    return 1;
}