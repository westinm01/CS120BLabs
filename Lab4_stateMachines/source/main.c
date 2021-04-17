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

unsigned char pa0;
unsigned char pa1;
unsigned char cdisplay;
void TickFct(){
	switch(state){
		case init:
			if(pa0 && !pa1){
				state=inc;
			}
			else if (!pa0 && pa1){
				state=dec;
			}
			else if(pa0 && pa1){
				state=reset;
			}
			else{
				state=init;
			}
		break;
		case inc:
			if(!pa0 && pa1){
                                state=dec;
                        }
			else if(pa0 && pa1){
                                state=reset;
                        }			
			/*else if(PINC==0x08){
				state=max;
			}*/
			else if (pa0 && !pa1){
				state=inc;
			}
			else{
				state=wait;
			}
		break;	
		case dec:
			if (pa0 && !pa1){
                                state=inc;
                        }
			else if( (PINC==0x00)||(pa0 && pa1)){
				state=reset;
			}
			
			else if(!pa0 && pa1){
				state=dec;
			}
			else{
				state=wait;
			}
		break;
		case wait:
			if(pa0 && pa1){
				state=reset;
			}
			else if(pa0 && !pa1){
				state=inc;
			}
			else if(!pa0 && pa1){
				state=dec;
			}
			else{
				state=wait;
			}
		break;
		case max:
			if(!pa0 && pa1){
				state=dec;
			}
			else if(pa0 && pa1){
				state=reset;
			}
			else{
				state=max;
			}
		break;
		case reset:
			if(pa0 && !pa1){
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
			if(PINC<0x08){
				PORTC=PINC+0x01;
			}
		break;
		case dec:
			if(PINC>0x00){
				PORTC=PINC-0x01;
			}
		break;
		case wait:
			
		break;
		case max:
			PORTC=8;
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
	DDRC=0xFF; PORTC=0x07;	
	state= init;
    /* Insert your solution below */
    while (1) {
	pa0=PINA & 0x01;
	pa1=(PINA>>1)&0x01;
	TickFct();
	cdisplay=PINC;
    }
    return 1;
}
