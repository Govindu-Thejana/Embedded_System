#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
	/* Replace with your application code */
	
	ADMUX &= ~((1<<REFS1)|(1<<REFS0)); //AREF, External voltage
	ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3)); // A0 selection
	
	//enable ADC
	ADCSRA |= ((1<<ADEN)|(1<<ADPS0) |(1<<ADPS1) |(1<<ADPS2) ); // ADC enable, 128 pre scalar value
	DDRD = 0B11111111;
	
	while (1)
	{
		ADCSRA |= (1<<ADSC); // start conversion
		while(ADCSRA & (1<<ADSC)); // Checking when ADSC becomes 0
		PORTD = ADC;
	}

}