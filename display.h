/*
 * display.h
 *
 *  Created on: 13 nov 2019
 *      Author: pacas
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_


#include <stdio.h>
#include "bits.h"
#include "MK64F12.h"
#include "I2C.h"


#define DISPLAY_ADDRESS_WRITE (0xE0)


typedef enum {
	pos_0 = 0,
	pos_1 = 2,
	pos_2 = 4,
	pos_3 = 6,
	pos_4 = 8,
	pos_5 = 10,
	pos_6 = 12,
	pos_7 = 14,
} Posicion_primer_cuadrado;

typedef enum {
	pos_0_2 = 1,
	pos_1_2 = 3,
	pos_2_2 = 5,
	pos_3_2 = 7,
	pos_4_2 = 9,
	pos_5_2 = 11,
	pos_6_2 = 13,
	pos_7_2 = 15,
} Posicion_segundo_cuadrado;


void display_init(void);
void display_instruccion_debug_horas(uint8_t array1[]);
void display_instruccion_debug_minutos(uint8_t array2[]);
void display_clear(void);


#endif /* DISPLAY_H_ */
