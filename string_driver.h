/*
 * @file:			string.h
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */


#ifndef STRING_DRIVER_H_
#define STRING_DRIVER_H_

#include <stdint.h>
#include "RTC.h"

typedef enum {
	CERO,  UNO,  DOS,   TRES, CUATRO,
	CINCO, SEIS, SIETE, OCHO, NUEVE,
} Index_array_t;

//* For print in Tera Term the string of the Time value */
void Time_to_String(uint32_t tiempo, Specific_RTC_Register_t TIPO_REG);

//* Return the string of the time that you want to show */
uint8_t* Get_String_Time(Specific_RTC_Register_t TIPO_REG);

//* Get the char of the respect number of the Time */
uint8_t Number_to_Char(uint8_t entero);


#endif /* STRING_DRIVER_H_ */
