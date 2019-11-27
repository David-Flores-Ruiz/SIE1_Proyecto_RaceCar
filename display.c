/*
 * dispaly.c
 *
 *  Created on: 13 nov 2019
 *      Author: pacas
 */
#include "display.h"

const uint8_t posiciones_primer_cubo[]  = {
		pos_0, 	 pos_1,   pos_2,   pos_3,   pos_4,   pos_5,   pos_6,   pos_7,   };

const uint8_t posiciones_segundo_cubo[] = {
		pos_0_2, pos_1_2, pos_2_2, pos_3_2, pos_4_2, pos_5_2, pos_6_2, pos_7_2, };

static uint8_t flag1 = 1;
static uint8_t flag2 = 0;
static uint8_t cont_primero = 0;
static uint8_t cont_segundo = 0;


void display_clear(void) {
	I2C_start(); //** It configures de I2C in transmitting mode and generates the start signal */
	I2C_write_byte(DISPLAY_ADDRESS_WRITE);
	I2C_wait();
	I2C_write_byte(0x00);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_write_byte(0);
	I2C_wait();
	I2C_stop();
}

void display_init(void) {
	I2C_start(); //** It configures de I2C in transmitting mode and generates the start signal */
	I2C_write_byte(DISPLAY_ADDRESS_WRITE); //** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	I2C_write_byte(0x21);
	I2C_wait();
	//I2C_stop();

	//I2C_start(); //** It configures de I2C in transmitting mode and generates the start signal */
	I2C_write_byte(0xE0); //** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	I2C_write_byte(0x81);
	I2C_wait();

	//I2C_start(); //** It configures de I2C in transmitting mode and generates the start signal */
	I2C_write_byte(0xE0); //** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	I2C_write_byte(0xEF);
	I2C_wait();
	I2C_stop();
	I2C_start();
	I2C_write_byte(DISPLAY_ADDRESS_WRITE);
	I2C_wait();
	I2C_write_byte(0x81);
	I2C_wait();
	I2C_stop();
	//acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	// Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK
}

void display_instruccion_debug_minutos(uint8_t array2[]) {
	if (flag2 == TRUE)
	{
		I2C_start();
		I2C_write_byte(DISPLAY_ADDRESS_WRITE);
		I2C_wait();
		I2C_write_byte(posiciones_segundo_cubo[cont_segundo]);
		I2C_wait();
		I2C_write_byte(array2[cont_segundo]);
		cont_segundo++;
		I2C_wait();
		I2C_stop();
	}

	if (cont_segundo == 8)
	{
		flag1 = TRUE;
		flag2 = FALSE;
		cont_segundo = 0;
	}
}

void display_instruccion_debug_horas(uint8_t array1[]) {
	if (flag1 == TRUE) {
		I2C_start();
		I2C_write_byte(DISPLAY_ADDRESS_WRITE); // 0xE0
		I2C_wait();
		I2C_write_byte(posiciones_primer_cubo[cont_primero]); //direccion de fila de led
		I2C_wait();
		I2C_write_byte(array1[cont_primero]);
		cont_primero++;
		I2C_wait();
		I2C_stop();
	}

	if (cont_primero == 8) {
		flag1 = TRUE;
		flag2 = TRUE;
		cont_primero = 0;
	}

}
