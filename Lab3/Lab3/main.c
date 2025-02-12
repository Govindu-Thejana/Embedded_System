/*
 * Lab3.c
 *
 * Created: 2/12/2025 10:06:04 AM
 * Author : Govindu
 */
 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


void initHardware(void);
void initADC(void);
int readADC(uint8_t);
void display(int);

int main(void)
{
	int adcValue;
	// Initialize hardware and ADC
	initHardware();
	initADC();
	while (1)
	{
		// Read ADC value from channel 0
		adcValue = readADC(0);
		// Display the ADC value
		display(adcValue);
		// Delay for 1 second
		_delay_ms(1000);
	}
	return 0;
}
 void initHardware() {
	 	 
	 // Configure PORTA or PORTC as output 
	 DDRA |= 0xFF;  // Set PORTA as output 
	 DDRC |= 0xFF;  // Set PORTC as output 
 }
 
void initADC(void){// initializing the ADC
	ADCSRA |= (1<<ADEN);// enable ADC conversion
	ADCSRA |= (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);//Enable ADC, pre scalar 128
}

// Function to read the ADC value from a specified channel
int readADC(uint8_t adc_input_pin)
{
	ADMUX = (ADMUX & 0xF0) | adc_input_pin; // Input selection
	ADMUX &= ~((1 << REFS1) | (1 << REFS0)); // External AREF
	ADCSRA |= (1 << ADSC); // Start the ADC conversion
	while (ADCSRA & (1 << ADSC)); // Polling

	return ADC;
}

void display (int value){
	int ones;
	int tens;
	int hundreds;
	int thousands;
	
	thousands = value/1000;
	hundreds = (value/100)%10;
	tens = (value/10)%10;
	ones = value % 10;
	
	PORTC = (thousands << 4)| hundreds;
	PORTA = (tens << 4)| ones;
	
}