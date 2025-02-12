/*
 * Lab3.c
 *
 * Created: 2/10/2025 1:58:20 PM
 * Author : Govindu
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void initHardware(void);
void initADC(void);
int readADC(uint8_t adc_input_pin);
void display(int value);

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

void initHardware(void) {
	DDRA |= 0xFF;  // Set PORTA as output
	DDRC |= 0xFF;  // Set PORTC as output
}

void initADC(void) {
	ADMUX |= (1<<REFS0);  // Use AVCC as reference
	ADCSRA |= (1<<ADEN);  // Enable ADC
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);  // Set prescaler to 128
}

int readADC(uint8_t adc_input_pin) {
	ADMUX = (ADMUX & 0xF0) | (adc_input_pin & 0x0F);  // Select ADC channel
	ADCSRA |= (1<<ADSC);  // Start the ADC conversion
	while (ADCSRA & (1<<ADSC));  // Wait for conversion to complete
	return ADC;
}

void display(int value) {
	int thousands = (value / 1000) % 10;
	int hundreds = (value / 100) % 10;
	int tens = (value / 10) % 10;
	int ones = value % 10;

	// Display on PORTA (thousands & hundreds) and PORTC (tens & ones)
	PORTA = (thousands << 4) | hundreds;
	PORTC = (tens << 4) | ones;
}
