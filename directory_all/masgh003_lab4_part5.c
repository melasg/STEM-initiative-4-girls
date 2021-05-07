/*	Author: home
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

unsigned char a1 = 0x00;
unsigned char a2 = 0x00;
unsigned char  a3 = 0x00;
unsigned char  a4 = 0x00;
unsigned char a5 = 0x00;
//using code #-X-Y-X
unsigned char key = 0x00;
unsigned char code[4] = {4, 1, 2, 1};
enum lockSys {START, KEY_HASH, KEY_Y, LOCK, WAIT, P} ostan;
void lock();
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;
    /* Insert your solution below */
    ostan = START;
	a1 = (~PINA & 0x04);
    a2 =(~PINA & 0x01);
  a3 =(~PINA & 0x02);
  a4 =(~PINA & 0x80);
a5 =(~PINA & 0x87);
    while (1) {
        lock();
    }
    return 1;
}


void lock() {
switch(ostan) {
    case START:
			PORTC = 0x00;
			if(PINA==code[key]){
				ostan = KEY_HASH;
				if (key == 3 && PORTC == 0x01){
					state = LOCK;
				}
				if(key == 3 && PORTC == 0x00){
					ostan = KEY_Y; 
				}
				key = 0x00;
				break;
			}
			else if(PINA == 0x00){
				ostan = START;
				break;
			}
			else{
				key = 0x00;
				if(a4 &&  PORTC == 0x01){
					ostan = LOCK;
				}
				break;
			}
			if(a4 == 0x80){
				ostan = LOCK; 
				break;
			}
			else{
				ostan = START;
				break;
			}
    case KEY_HASH:
    ostan = WAIT;
    break;
    case KEY_Y:
    PORTC = 0x01;
    ostan = P;
    break;
    case LOCK:
    PORTC = 0x00;
    ostan = START;
    break;
    case WAIT:
       if(PINA==code[key]){
                                ostan = WAIT;
                                break;
                        }
                        else if(PINA == 0x00){
                                ostan = START;
                                break;
                        }
                        else{
                                key = 0x00;
                                if(a4 &&  PORTB == 0x01){
                                        ostan = LOCK;
                                }
				break;
                        }
			if(a3 == 0x02){
				ostan = KEY_Y;
				break;
			}
			else if((PORTC & 0x01) == 0x01)
			{
				if(a3 == 0x02){
					ostan = LOCK;
					break;
				}
				else{
					ostan = WAIT;
					break;
				}
				break;
			}
			else if(a4 == 0x80){
				ostan = LOCK;
				break;
			}
			else if(a2 == 0x01){
				ostan = START;	
				break;
			}
			else{
				ostan = WAIT;
				break;
			}
    case P:
    if (a5 == 0x00) {
        ostan = P;
        break;
    } else {
        ostan = START;
        break;
    }
}
}