#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdbool.h>

#include "led.h"
#include "serial.h"
#include "timer.h"
#include "button.h"

void main (void) 
{
	button_init();
	LED_init();
	uart_init();
	timer_init();

	while (1) 
	{
		button_click();
		//button_print();
	}
}

