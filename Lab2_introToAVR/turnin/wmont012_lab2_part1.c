/*	Author: wmont012
 *  Partner(s) Name: none
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

int main(void){
	DDRA=0x00;
	PORTA=0xFF;
	DDRB = 0xFF; // Configure port B's 8 pins as outputs
	PORTB = 0x00; // Initialize PORTB output to 0s
	
	while(1){
		//unsigned char pa0 = PINA & 0x03;
		if((PINA & 0x03)==0x01){
			PORTB=0x01;
		}
		else{
			PORTB=0x00;
		}
	}
	return 1;
}
