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

enum STATES {init, inc, dec, wait, max, reset} state;

unsigned char PA0;
unsigned char PA1;

void TickFct(){
	switch(state){
		case init:
			if(PA0 && !PA1){
				state=inc;
			}
			else if (!PA0 && PA1){
				state=dec;
			}
			else{
				state=init;
			}
		break;
		case inc:
			if(PINC==0x09){
				state=max;
			}
			else if (PA0 && !PA1){
				state=inc;
			}
			else if(PA0 && PA1){
				state=reset;
			}
			else if(!PA0 && PA1){
				state=dec;
			}
			else{
				state=wait;
			}
		break;	
		case dec:
			if(PINC==0x00 || (PA0 && PA1)){
				state=reset;
			}
			else if (PA0 && !PA1){
				state=inc;
			}
			else if(!PA0 && PA1){
				state=dec;
			}
			else{
				state=wait;
			}
		break;
		case wait:
			if(PA0 && PA1){
				state=reset;
			}
			else if(PA0&&!PA1){
				state=inc;
			}
			else if(!PA0 && PA1){
				state=dec;
			}
			else{
				state=wait;
			}
		break;
		case max:
			if(!PA0 && PA1){
				state=dec;
			}
			if(PA0 && PA1){
				state=reset;
			}
			else{
				state=max;
			}
		break;
		case reset:
			if(PA0 && !PA1){
				state=inc;
			}
			else{
				state=reset;
			}
		break;
		default:
			state=init;
		break;
	}
	switch(state){
		case init:
			PORTC=0x07;
		break;
		case inc:
			if(PINC<0x09){
				PORTC=PINC+1;
			}
		break;
		case dec:
			if(PINC>0x00){
				PORTC=PINC-1;
			}
		break;
		case wait:
			PORTC=PINC;
		break;
		case max:
			PORTC=9;
		break;
		case reset:
			PORTC=0;
		break;
		default:
		break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA=0x00; PORTA=0xFF;
	DDRC=0xFF; PORTC=0x00;	
	state= init;
    /* Insert your solution below */
    while (1) {
	PA0=PINA & 0x01;
	PA1=PINA & 0x02;
	TickFct();
    }
    return 1;
}
