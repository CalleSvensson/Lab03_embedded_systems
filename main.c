#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdbool.h>

#include "led.h"
#include "serial.h"
#include "timer.h"
#include "button.h"
#include "adc.h"
volatile unsigned int adc_val = 0;
ISR(TIMER2_COMPA_vect)
{
	ADCSRA |= (1 << ADSC); //start single conversion mode
	OCR0A = adc_val;
}

ISR(ADC_vect)
{
	adc_val = ADCH;
}
void main (void) 
{
	button_init();
	LED_init();
	uart_init();
	timer_init();
	adc_init();
	while (1) 
	{
		printf_P(PSTR("%d\n"), adc_val);

		button_click();
	}
}

