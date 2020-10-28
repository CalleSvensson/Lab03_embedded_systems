#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void timer_init() 
{
	TCCR0A = 0;
	TCCR0A |= (1 << WGM01) | (1 << WGM00); // set to fast PWM mode with TOP 0xFF by default
	TCCR0A |= (1 << COM0A1); //non- inverting mode
	TCCR0B |= (1 << CS01) | (1 << CS00); // set 64 prescaler. 

	TCCR2A |= (1 << WGM21); // timer2 in CTC mode
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // prescaler 1024
	OCR2A = 155; //16000000/ (1024)*(0,01)-1
	TIMSK2 |= (1 << OCIE2A);  // enable interrupts
	sei();
}

