/*	Author: wmont012
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum STATES {on0A, on0B,on1A, on1B} state;

void TickFct(){
	switch(state){
		case on0A:
			if(PINA & 0x01){
				state=on0A;
			}
			else{
				state=on0B;
			}
		break;
		case on0B:
			if(PINA & 0x01){
				state=on1A;
			}
			else{
				state=on0B;
			}
		break;	
		case on1A:
			if(PINA & 0x01){
				state=on1A;
			}
			else{
				state=on1B;
			}
		break;
		case on1B:
			if(PINA & 0x01){
				state=on0A;
			}
			else{
				state=on1B;
		}
		default:
			state=on0B;
		break;
	}
	switch(state){
		case on0A:
		case on0B:
			PORTB=0x01;
		break;
		case on1A:
		case on1B:
			PORTB=0x02;
		break;
		default:
		break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA=0x00; PORTA=0xFF;
	DDRB=0xFF; PORTB=0x00;
	
	state= on0B;
    /* Insert your solution below */
    while (1) {
	TickFct();
    }
    return 1;
}
