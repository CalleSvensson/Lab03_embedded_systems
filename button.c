#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <stdbool.h>
#include <stdio.h>

#include "button.h"
#include "serial.h"

bool buttonState = false;
bool lastButtonState = false;
void button_init() 
{
	DDRD &= ~(1 << PD2); // PD2 button input
}

void button_click(int *state)
{
	if (PIND & (1 << PD2))
	{
		buttonState = true;
		//button_print();
	}
	else
	{
		buttonState = false;
		if (buttonState == false && lastButtonState == true) *state+=1;
		//button_print();
	}
	lastButtonState = buttonState;
}
void button_print()
{
	if (buttonState == true && lastButtonState == false)
	{
		printf_P(PSTR("pushed\r\n"));
	}
	else if (buttonState == false && lastButtonState == true)
	{
		printf_P(PSTR("released\r\n"));
	}
}
