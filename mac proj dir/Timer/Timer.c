#include "Timer.h"

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

//Internal variables for mapping AVR'S ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; //Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer__cntcurr = 0; //Current internal count of 1ms ticks.

void TimerOn(){
    // AVR timer/counter controller register TCCR1
    TCCR1B = 0x0B;    // bit3 = 0: CTC mode (clear timer on compare)
    // bit2bit1bit0 = 011: pre-scaler /64
    // 00001011: 0x0B;
    //So, 8 MHz clock or 8,000,000/64 = 125,000 ticks/s
    //Thus, TCNT1 Register will count at 125,000 ticks/s
    // AVR output compare resister OCR1A
    OCR1A = 125;
    //We want a 1 ms tick. 0.001 s*125,000 ticks/s = 125
    //So when TCNT1 register equals 125,
    //1 ms has passed. Thus, we compare to 125.
    // AVR timer interrupt mask register
    TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt
    
    //Initialize avr counter
    TCNT1 = 0;
    
    _avr_timer__cntcurr = _avr_timer_M;
    // TimerISR will be called every_avr_timer_cntcurr milliseconds
    
    //Enable global interrupts
    SREG |= 0x80; // 0x80: 1000000
}
void Timer0ff(){
    TCCR1B = 0x00; //bit3bit1bit0 =000: timer off
}
void TimerISR(){
    TimerFlag = 1;
}
// In our approach, the c programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect){
    //CPU automatically calls when TCNT1 - 0CR1 (every 1 ms per TimerOn settings)
    _avr_timer__cntcurr--;    //count down to 0 rather than up to TOP.
    if(_avr_timer__cntcurr == 0){ //results in a more efficient compare
        TimerISR(); // call the isr that the user uses
        _avr_timer__cntcurr = _avr_timer_M;
    }
}
// set TimerISR() to tick every M ms
void TimerSet(unsigned long M){
    _avr_timer_M = M;
    _avr_timer__cntcurr = _avr_timer_M;
}
unsigned char TimerStart(unsigned char timer_multiple, char PORTA_singnal_check){
    unsigned char check = 0x00;
    TimerSet(50);
    TimerOn();
    for(unsigned char i = 0; i < timer_multiple; i++)
    {
        while(!TimerFlag){
            switch (PORTA_singnal_check) {
                case '0' :
                    if(check == 0x00){
                        check = ~PINA & 0x01;
                    }
                    
                    break;
                case '1' :
                    if(check == 0x00){
                        check = ~PINA & 0x02;
                    }
                    break;
                case '2' :
                    if(check == 0x00){
                        check = ~PINA & 0x04;
                    }
                    break;
                case '3' :
                    if(check == 0x00){
                        check = ~PINA & 0x08;
                    }
                    break;
                case '4' :
                    if(check == 0x00){
                        check = ~PINA & 0x10;
                    }
                    break;
                case '5' :
                    if(check == 0x00){
                        check = ~PINA & 0x20;
                    }
                    break;
                case '6' :
                    if(check == 0x00){
                        check = ~PINA & 0x40;
                    }
                    break;
                case '7' :
                    if(check == 0x00){
                        check = ~PINA & 0x80;
                    }
                    break;
                default:
                    break;
            }
        }
        TimerFlag = 0;
    }
    Timer0ff();
    return check;
}

