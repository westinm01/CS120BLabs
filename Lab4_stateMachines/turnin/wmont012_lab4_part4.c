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

enum STATES {init, poundHold, poundRelease, unlocked, unlockedPoundHold, unlockedPoundRelease} state;

unsigned char pa0;	//X
unsigned char pa1;	//Y
unsigned char pa2;	//pound
unsigned char pa7;	//lock

void TickFct(){
	switch(state){
		case init:
			if(pa2 && !pa0 &&!pa1 &&!pa7){
				state=poundHold;
			}
			else{
				state=init;
			}
		break;
		case poundHold:
			if(pa2 && !pa0 && !pa1 && !pa7){
                                state=poundHold;
                        }
			else if(!pa2 && !pa0 && !pa1 && !pa7){
                                state=poundRelease;
                        }
			//else if(!pa2 && !pa0 && pa1 &&!pa7){
			//	state=unlocked;		
			//}	
			else{
				state=init;
			}
		break;	
		case poundRelease:
			if(pa1 && !pa0 && !pa2 &&!pa7){
				state=unlocked;
			}
			else if (!pa1 && !pa0 && !pa2 && !pa7){
				state=poundRelease;
			}
			else{
				state=init;
			}
		break;
		case unlocked:
			if (!pa7){
                                state=unlocked;
                        }
			if(pa2 && !pa0 &&!pa1 && !pa7){
				state=unlockedPoundHold;
			}
			else{
				state=init;
			}
		break;
		case unlockedPoundHold:
			if(pa2 &&!pa0 && !pa1 && !pa7){
				state=unlockedPoundHold;
			}
			else if(!pa2 && !pa0 && !pa1 && !pa7){
				state=unlockedPoundRelease;
			}
			else if(pa7){
				state=init;
			}
			else{
				state=unlocked;
			}
		break;
		case unlockedPoundRelease:
			if(pa1 && !pa0 &&!pa2 ||pa7){
				state=init;//locked
			}
			else if(!pa1 && !pa0 &&!pa2 &&!pa7){
				state=unlockedPoundRelease;
			}
			else{
				state=unlocked;
			}
		break;
		default:
			state=init;
		break;
	}
	switch(state){
		case init:
			PORTC=0x00;
			PORTB=0x00;
		break;
		case poundHold:
			PORTC=0x01;
			PORTB=0x00;
		break;
		case poundRelease:
			PORTC=0x02;
			PORTB=0x00;
		break;
		case unlocked:
			PORTC=0x03;
			PORTB=0x01;
		break;
		case unlockedPoundHold:
			PORTC=0x04;
			PORTB=0x01;
		break;
		case unlockedPoundRelease:
			PORTC=0x05;
			PORTB=0x01;
			
		break;
		default:
		break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA=0x00; PORTA=0xFF;
	DDRB=0xFF; PORTB=0x00;
	DDRC=0xFF; PORTC=0x00;	
	state= init;
    /* Insert your solution below */
    while (1) {
	pa0=PINA & 0x01;
	pa1=(PINA>>1)&0x01;
	pa2=(PINA>>2)&0x01;
	pa7=(PINA>>7)&0x01;
	TickFct();
    }
    return 1;
}
