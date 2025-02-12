/*
 * ADC_with_Interrupt.c
 *
 * Created: 2/12/2025 4:14:45 PM
 * Author : Govindu
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "util/delay.h"
#include <avr/interrupt.h>
#define CHANNEL 0B00000000

void ConfigureADC(void);

int main(void)
{
	DDRD = 0B11111111;
	DDRB = 0B00100000;
	
	ConfigureADC();
	
	//conversion begin
	ADCSRA |=0B01000000;
	
	while (1)
	{
		//main function that to model normal process
		PORTB |= 0B00100000;
		_delay_ms(600);
		PORTB &= 0B11011111;
		_delay_ms(600);
	}
}

void ConfigureADC(void){
	ADCSRA |= (1<<ADEN); //to enable ADC
	ADCSRA |= 0B00000111; //pre scalar 128
	ADMUX  &= 0B00111111; //enable AREF
	
	//add channel number
	ADMUX = (ADMUX & 0B11110000) | CHANNEL;
	
	//interrupt on
	ADCSRA |= (1<<ADIE);
	
	//free run mode
	ADCSRA |= (1<<ADATE);
	ADCSRB &= 0B11111000;
	
	sei();
}

ISR (ADC_vect){
	PORTD = ADC;
}