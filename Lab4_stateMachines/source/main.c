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

enum STATES {on0,on1} state;

void TickFct(){
	switch(state){
		case on0:
			if(PINA & 0x01){
				state=on1;
			}
		break;
		case on1:
			if(PINA & 0x01){
				state=on0;
			}
		break;
		default:
			state=on0;
		break;
	}
	switch(state){
		case on0:
			PORTB=0x01;
		break;
		case on1:
			PORTB=0x02;
		break;
		default:
		break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA=0xFF; PORTA=0x00;
	DDRB=0x00; PORTB=0xFF;
	
	state= on0;
    /* Insert your solution below */
    while (1) {
	TickFct();
    }
    return 1;
}
