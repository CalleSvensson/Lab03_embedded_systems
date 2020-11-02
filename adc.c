#include <avr/io.h>
#include <avr/interrupt.h>

#include "adc.h"

void adc_init()
{
	ADMUX = 0x00; // chanel ACDC0
	ADMUX |= (1 << REFS0); // Vcc reference 
	ADMUX |= (1 << ADLAR); // set to left adjusted
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0); // prescaler 8
	ADCSRA |= (1 << ADEN); // enable adc
	ADCSRA |= (1 << ADIE);//enable, interrupt on completion
	sei();
}

int read_adc()
{
	ADCSRA |= (1 << ADSC); //single conversion mode
	while (ADCSRA & (1 << ADSC)); //wait for end of conversion
	return ADCH;
}

void start_single_conversion()
{
	ADCSRA |= (1 << ADSC); 
}

int set_pot_value()
{
	if (ADCH < 10)  // check if ADC is lower then 10 to make up for irregularities in ADC (bad hardware)
	{
		TCCR0A &= ~(1 << COM0A1); // turn fast PWM off to turn led off
		return 0;
	}
	else
	{
		TCCR0A |= (1 << COM0A1);
		return ADCH;
	}
}