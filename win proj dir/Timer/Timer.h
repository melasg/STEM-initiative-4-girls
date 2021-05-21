#ifndef __Timer_h__
#define __Timer_h__
#include <avr/io.h>
#include <avr/interrupt.h>

void TimerOn();
void Timer0ff();
void TimerISR();
void TimerSet(unsigned long M);
unsigned char TimerStart(unsigned char timer_multiple, char PORTA_singnal_check);
#endif
