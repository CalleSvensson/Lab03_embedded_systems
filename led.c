#include <avr/io.h>
#include <stdbool.h>
#include "led.h"
uint8_t count;
bool countUp = false;
void LED_init() 
{
	DDRD |= (1 << PD6); // set pin 6 on Arduino board to output(AIN0/OC0A)
}
void LED_toggle()
{
	PORTD ^= (1 << PD6); // flip LED bit
	//PORTD ^= (1 << PD6); // flip LED bit
}

uint8_t simple_ramp() 
{

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
