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
static int state = 0;
volatile bool doState = false;

ISR(TIMER2_COMPA_vect)
{
	button_click(&state);
	doState = true;
	//ADCSRA |= (1 << ADSC); //start single conversion mode
	OCR0A = adc_val;
}


ISR(ADC_vect)
{
	adc_val = set_pot_value();
}


void state_executer()
{
	if (state == 0)
	{
		if (!(TCCR0A |= (1 << COM0A1))) // checks if Fast PWM is turned off
		{
			(TCCR0A |= (1 << COM0A1));
		}
		OCR0A = simple_ramp();
	}
	else if (state == 1)
	{
		start_single_conversion();
	}
	else if (state == 2)
	{
		TCCR0A &= ~(1 << COM0A1); // turn off fast PWM to get the led to toggle and turn off
		LED_toggle();
	}
	else if (state == 3)
	{
		led_off();
	}
	else
	{
		state = 0;
	}
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
		if (doState)
		{
			state_executer();
			doState = false;
		}
		printf_P(PSTR("%d\n"), adc_val);
		//ADCSRA |= (1 << ADSC); //single conversion mode
		//while (ADCSRA & (1 << ADSC)); //wait for end of conversion
		//button_click();
	}
}

