#include <avr/io.h>
#include <avr/interrupt.h>

#include "adc.h"

void adc_init()
{
	//ADMUX &= ~(1 << REFS1)| (1 << REFS0); // Vcc reference 
	ADMUX = 0x00; // chanel ACDC0
	ADMUX |= (1 << REFS0); // Vcc reference 
	ADMUX |= (1 << ADLAR); // set to left adjusted
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0); // prescaler 8
	//ADMUX &= ~(1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0); // set to chanel ADC0
	ADCSRA |= (1 << ADEN); // enable adc
	ADCSRA |= (1 << ADIE);//enable, interrupt on completion
	sei();
}

int read_adc()
{
	int ADCval;
	ADCSRA |= (1 << ADSC); //single conversion mode
	while (ADCSRA & (1 << ADSC)); //wait for end of conversion
	//return ADCH;
	ADCval = ADCH;
	//ADCval = (ADCH << 8) + ADCval;
	return ADCval;
}