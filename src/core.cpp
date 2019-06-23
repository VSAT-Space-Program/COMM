/*
 * main.cpp
 *
 *  Created on: 11 de abr de 2019
 *      Author: Eduardo Lacerda Campos
 *
 *	Communication satellite module
 *
 */


#include "stdlib.h"
#include <stdio.h>
#include <inttypes.h>

#include <avr/io.h>
#include <util/delay.h>
#include "SX1276.h"
#include "Usart.h"
#include "MS5607.h"

SX1276 LoRa;
/******************************************************************
 * Define the instruction to the printf or printfP routines
 ******************************************************************/
int Std_putchar(char c, FILE *stream) {
    USART.writeByte(c);
    return 0;
}

void setup(){

	// initialize the digital pin as an output.
	// Pin 13 has an LED connected on most Arduino boards:
	DDRB   = (1<<PB5);
	PORTB &= ~(1<<PB5);

	USART.begin(9600);

	stdout = fdevopen(Std_putchar, NULL);

	//BUG - On the AVR, using the serial port direct can cause a BUG in the stdout
	//TO avoid this BUG, first use the stdout
	printf_P(PSTR("USART OK\n"));

	//Enable the LoRa Tx serial
	DDRB  |= (1<<PB3);
	PORTB |= (1<<PB3);

	if(!LoRa.Initialize(&USART,0))
		printf(PSTR("Lora Fail\n"));
	else
		printf_P(PSTR("Lora ok\n"));


//	stdout = fdevopen(Std_putchar, NULL);
	printf_P(PSTR("Setup Finished\n"));



}

void loop(){

	PORTB &= ~(1<<PB5);
	_delay_ms(1000);
	PORTB |= (1<<PB5);
	_delay_ms(1000);

}

int main(void)
{
	setup();

	for (;;)
		loop();

	return 0;
}
