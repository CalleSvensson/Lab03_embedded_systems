#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "serial.h"
#include "led.h"

int ledblinkcounter = 0;
void LED_init() 
{
	DDRD |= (1 << PD6); // set pin 6 on Arduino board to output(AIN0/OC0A)
}
void LED_toggle()
{
	static uint8_t ledblinkcounter = 0;
	ledblinkcounter++;

	if(ledblinkcounter == 100)  // count to 100 to blink led every second
	{
		PORTD ^= (1 << PD6);  // flip LED bit ON/OFF
		ledblinkcounter = 0;
	}	
}

void led_off()
{
	PORTD &= ~(1 << PD6); // turn led off
}

uint8_t simple_ramp() 
{
	static uint8_t count = 0;
	static bool countUp = false;
	if (countUp)
	{
		count++;
		if (count == 255) countUp = false;
		return count;
	}
	else
	{
		count--;
		if (count == 0) countUp = true;
		return count;
	}
}
