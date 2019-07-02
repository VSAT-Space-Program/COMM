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
#include "stdint.h"
#include <stdio.h>
#include <inttypes.h>


#include <avr/io.h>
#include <util/delay.h>
#include "SX1276.h"
#include "Usart.h"
#include "MS5607.h"
#include <string.h>

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

	if(!LoRa.Initialize(&USART,2,0x0F))
		printf(PSTR("Lora Fail\n"));
	else
		printf_P(PSTR("Lora ok\n"));


	DDRB   = ~(1<<PB4);
	uint8_t status[50];
	strcpy_P((char*)status,PSTR("Waiting the power up procedures to finish\n"));
	while((PORTB & (1<<PB4))==0){
		LoRa.Send(1,0x08,status,sizeof(status));
		printf((const char*)status);
		_delay_ms(1000);
	}

	strcpy_P((char*)status,PSTR("Ready to fly \n"));
	printf((const char*)status);


//	stdout = fdevopen(Std_putchar, NULL);
	printf_P(PSTR("Setup Finished\n"));


}

void loop(){

	uint8_t dados[10]={'o','i',0};
	uint8_t tamanho=3;
	LoRa.Send(1,0x08,dados,tamanho);

}

int main(void)
{
	setup();

	for (;;)
		loop();

	return 0;
}
