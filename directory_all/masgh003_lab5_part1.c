/*	Author: Melody Asghari
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *  A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full). A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level. If the fuel level is 1 or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light. 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..C1. 13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less. Use buttons on PA3..PA0 and mimic the fuel-level sensor with presses. 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#define button (~PINA & 0x0F)

/* From zybooks for my reference  
Figure 1.12.4: Example using SetBit() function.
unsigned char i, val;
val = A0;  
for (i = 0; i < 4; i++) {
   B = SetBit(B, i, val);
}

inline unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
   return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
}

*/

unsigned char SetBit(char pin, char bit_position, char bit_value) {
	return (bit_value ? pin | (0x01 << bit_position)
			: pin & ~(0x01 << bit_position));
}
/* From zybooks for my reference 
Figure 1.12.5: GetBit() function to get a particular bit.
unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);

unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}

*/
unsigned char GetBit(char port, char bit_position) {
	return ( (port >> bit_position) & 0x01 );
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0x00;
    PORTB = 0x00;
    DDRC = 0xFF;
    PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
		//modeled off the code for the first program in the lab specifications
        //Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less.
			if ((button >= 0x0D) && (button <= 0x0F)) {  //PC0
				PORTC = 0x3F;
			}
			else if ((button >= 0x0A) && (button <= 0x0C)) { //PC1
				PORTC = 0x3E;
			}
			else if ((button >= 0x07) && (button <= 0x09)) { //PC2
				PORTC = 0x3C;
			}
			else if ((button >= 0x05) && (button <= 0x06)) { //PC3
				PORTC = 0x38;
			}
			else if ((button >= 0x03) && (button <= 0x04)) { //PC4
				PORTC = 0x70;
			}
			else if ((button >= 0x01) && (button <= 0x02)) {  //PC5
				PORTC = 0x60;
			}
    }
    return 1;
}
