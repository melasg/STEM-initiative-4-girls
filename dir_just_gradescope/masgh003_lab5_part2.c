/*	Author: Melody Asghari
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *   Buttons are connected to P_A0 and P_A1. Output for PORTC is initially 0. Pressing P_A0 increments PORTC (stopping at 9). Pressing P_A1 decrements PORTC (stopping at 0). If both buttons are depressed (even if not initially simultaneously), PORTC resets to 0. If a reset occurs, both buttons should be fully released before additional increments or decrements are allowed to happen. Use LEDs (and resistors) on PORTC. Use a state machine (not synchronous) captured in C. 
 *	I acknowledge all content contained herein, excluding template or example 
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//state machine constants:
#define tempA (~PINA & 0x03)
// if ((PINA & (1 << P_A0)) == 0) checks if P_A0 is pressed
// if ((PINA & (1 << P_A1)) == 0) checks if P_A0 is pressed
unsigned char tempC; //PORTC

enum PushedState {INIT, START, INC, REL1, REL2, DEC, RESET, WAIT} ostan; // REVISE FOR 3 WAIT -> ARROWS ...

void process() {
	switch (ostan) {
		case INIT:
		ostan = START;
		break;
		case START:
			ostan = WAIT;
		break;
		//press = P_A0 increments PORTC stops at 9 
		case INC:
		ostan = START; //checks in starting sm state
		break;
		//Press P_A1 decrements PORTC stops at 0 
		case DEC:
		ostan = START;
		break;
		// If both buttons are depressed (not simultaneously) PORTC = 0
		case RESET:
		if (!tempA == 0) {
			ostan = WAIT;
		} else {
			tempC = 0;
			ostan = RESET;
		}
		break;
		case WAIT:
		if (tempA == 1 && tempC < 9) {
			ostan = INC;
		} else if (tempA == 0x02 && tempC > 0) {
			ostan = DEC;
		} else if (tempA == 3) {
			ostan = RESET;
		} else {
			ostan = WAIT;
		}
		break;
		case REL1:
		//INCREASE
		if (tempA == 0) {
			ostan = WAIT;
		} else if (tempA == 3) {
			ostan = RESET;
		} else {
			ostan = REL1;
		}
		break;
		case REL2:
		//DECREASE
		if (tempA == 0) {
			ostan = WAIT;
		} else if (tempA == 3) {
			ostan = RESET;
		} else {
			ostan = REL2;
		}
		break;

	}
	switch (ostan) {
		case INIT:
		break;
		case START:
		tempC = 0;
		break;
		//press = P_A0 increments PORTC stops at 9 
		case INC:
		tempC++;
		break;
		//Press P_A1 decrements PORTC stops at 0 
		case DEC:
		tempC--;
		break;
		// If both buttons are depressed (not simultaneously) PORTC = 0
		case RESET:
		//tempC = 0;
		break;
		case WAIT:
		break;
		case REL1:
		break;
		case REL2:
		break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; //a0 is dumpframe
	PORTA = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00; //portc is output
    /* Insert your solution below */
	ostan = INIT;

    while (1) {
		process();
		PORTC = tempC;
    }
    return 1;
}
