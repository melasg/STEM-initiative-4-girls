/*	Author: home
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 * To the previous exercise's implementation, connect your speaker's red wire to PB4 and black wire to ground. Add a third task that toggles PB4 on for 2 ms and off for 2 ms as long as a switch on PA2 is in the on position. Don’t use the PWM for this task.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
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
unsigned char P_1;
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
		default:
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
		default:
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
		default:
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
		default:
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
		default:
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
		default:
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
    unsigned long num1 = 300;
    unsigned long num2 = 1000;
    TimerSet(500);
    TimerOn();
    SM_1 = B_0;
SM_2 = b_2p2;
    SM_3 = INIT;
    while (1) {
      P_1 = ~PINA;
      if (num1 >= 300) {
        //initialize
        state_1();
        num1 = 0;
      }
      if (num2 >= 1000) {
        //initialize
        state_2();
        num2 = 0;
      }
      state_3();
      while(!TimerFlag);
      TimerFlag=0;
      //counter
      num1 += 100;
      num2 += 100;
    }
    return 1;
}

