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
	//DDRB = 0xFF; // Configure port B's 8 pins as outputs
	//PORTB = 0x00; // Initialize PORTB output to 0s
	DDRC=0xFF;
	PORTC=0x00;
	//unsigned char pa0;
	//unsigned char pa1;
	/*unsigned char car1;
	unsigned char car2;
	unsigned char car3;
	unsigned char car4;
	unsigned char cntavail=4;*/
	while(1){
		/*pa0=PINA & 0x01;
		pa1=PINA&0x02;
		if(pa0==0x00 &&pa1==0x02){
			PORTB=0x01;
		}
		else{
			PORTB=0x00;
		}*/
		unsigned char aTemp=PINA;
		unsigned char cntavail=0x00;
		unsigned char i;
		for(i=0;i<4;i++){

			if(!(aTemp & 0x01)){
				cntavail++;
			}
			aTemp=aTemp>>1;
		}

		PORTC=cntavail;

	}
	return 1;
}
