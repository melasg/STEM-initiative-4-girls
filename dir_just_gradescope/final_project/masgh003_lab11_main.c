/*	Author: home
 *  Partner(s) Name: Melody Asghari
 *	Lab Section: 022
 *	Assignment: Lab # 11 Exercise #
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 * YES! I acknowledge this. Put too much blood, sweat, and tears in this!
* video link: 
* 
 */

 #include "../../mac proj dir/includes/io.h"
 //#include <../../mac proj dir/avr-headers/avr/io.h>
#include <../../mac proj dir/includes/util/delay.h>
#include <../../mac proj dir/includes/avr/interrupt.h>
//#include "../../mac proj dir/lcd/io.h"
#include "dir_just_gradescope/final_project/LCD_driver.h"
#include "dir_just_gradescope/final_project/LCD_AVR_8b.c"
#include <stdlib.h>
#include <time.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "scheduler.h"
#include "bit.h"
#include "timer.h"
#endif
// atmega1284s.bootloader.file=ATmegaBOOT_168_atmega1284p.hex
#define F_CPU 20000000L
// move validation
bool isMoveable; //binary choice
int waitcount, check1a, check2a, check1b, check2b;
enum states_players { busy, canmove, input, pressed_directional } ostan1;
enum states_buttons { btn_1, btn_2 } ostan2;
enum states_world { direction_N, direction_E, direction_S, direction_W } ostan3;
enum states_screen {init, reset, write_text} ostan4;

void player_check();
void controller_screen();
//int vectors
int main(void) {
    //initialize stack pointer
    
    //initialize LCD
    lcd_init_8d(void);
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0x0f;
    DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    //initalize PORTD for the inputs
	DDRD = 0x00; PORTD = 0xFF;
    //main program
    while(1) {

    }
    //text start up on screen LCD

    //player controller
    void lcd_write_string_8d(uint8_t *);
    //wait for button press or interrupt signal

    //
//reset screen!
    lcd_Clear();
}

void player_check() {
    switch(states_players) {
        case pressed_directional:
            break;
        case canmove:
            break;
        case input:
            break;
        case busy:
            break;
    }
    switch(states_players) {
        case pressed_directional:
            break;
        case canmove:
            break;
        case input:
            break;
        case busy:
            break;
    }
}
void controller_screen() {
    switch(states_screen) {
        case init:
            break;
        case reset:
            break;
        case write_text:
            break;
    }
    switch(states_screen) {
switch(states_screen) {
        case init:
        ostan4 = init;
            break;
        case reset:
        ostan4 = write_text;
            break;
        case write_text:
        while (!reset){
        void lcd_write_string_8d(uint8_t *);
        } else {
            ostan4 = reset;
        }
            break;
    }
}