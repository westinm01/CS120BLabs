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

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA=0x00; PORTA=0xFF;
	DDRB=0x00; PORTB=0xFF;
	DDRC=0xFF; PORTC=0x00;
    /* Insert your solution below */
    while (1) {
	unsigned char i;
	unsigned char count=0x00;
	unsigned char tempA=PINA;
	unsigned char tempB=PINB;
	for(i=0;i<8;i++){
		if((tempA & 0x01)){
			count++;
		}
		if((tempB & 0x01)){
			count++;
		}
		tempA=tempA>>1;
		tempB=tempB>>1;
	}
	PORTC=count;
    }
    return 1;
}
