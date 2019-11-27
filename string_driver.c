/*
 * @file:			string.c
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */


#include "string_driver.h"

uint8_t g_decenas  = 0;
uint8_t g_unidades = 0;

#define STRING_SECONDS &string_time_secs[0]	// Direccion del arreglo de Segundos
#define STRING_MINUTES &string_time_mins[0] // Direccion de minutos
#define STRING_HOURS   &string_time_hrs[0]  // Direccion de horas

#define STRING_DATE  &string_date_day[0]   // Direccion del arreglo ded dia
#define STRING_MONTH &string_date_month[0] // Direccion de mes
#define STRING_YEAR  &string_date_year[0]  // Direccion de anio

uint8_t string_time_hrs[4] =  "DU:";
uint8_t string_time_mins[4] = "DU:";
uint8_t string_time_secs[3] = "DU";


uint8_t string_date_day[4]  =  "DU/";
uint8_t string_date_month[4] = "DU/";
uint8_t string_date_year[3] =  "DU";

uint8_t string_dummy[ ] = "";


void Time_to_String(uint32_t tiempo, Specific_RTC_Register_t TIPO_REG)
{
	g_decenas = tiempo / 10;
	g_unidades = (tiempo - (g_decenas * 10)) / 1;

	if (TIPO_REG == SEC) {
		string_time_secs[0] = Number_to_Char(g_decenas);
		string_time_secs[1] = Number_to_Char(g_unidades);
	}

	if (TIPO_REG == MIN) {
		string_time_mins[0] = Number_to_Char(g_decenas);
		string_time_mins[1] = Number_to_Char(g_unidades);
	}

	if (TIPO_REG == HOUR) {
		string_time_hrs[0] = Number_to_Char(g_decenas);
		string_time_hrs[1] = Number_to_Char(g_unidades);
	}

	if (TIPO_REG == DATE) {
		string_date_day[0] = Number_to_Char(g_decenas);
		string_date_day[1] = Number_to_Char(g_unidades);
	}

	if (TIPO_REG == MONTH) {
		string_date_month[0] = Number_to_Char(g_decenas);
		string_date_month[1] = Number_to_Char(g_unidades);
	}

	if (TIPO_REG == YEAR) {
		string_date_year[0] = Number_to_Char(g_decenas);
		string_date_year[1] = Number_to_Char(g_unidades);
	}

}

uint8_t* Get_String_Time(Specific_RTC_Register_t TIPO_REG)
{
	uint8_t* ptr_String = 0x00;

	if (TIPO_REG == SEC) {
		ptr_String = STRING_SECONDS;
	}

	if (TIPO_REG == MIN) {
		ptr_String = STRING_MINUTES;
	}

	if (TIPO_REG == HOUR) {
		ptr_String = STRING_HOURS;
	}

	if (TIPO_REG == DATE) {
		ptr_String = STRING_DATE;
	}

	if (TIPO_REG == MONTH) {
		ptr_String = STRING_MONTH;
	}

	if (TIPO_REG == YEAR) {
		ptr_String = STRING_YEAR;
	}

	return (ptr_String);
}

uint8_t Number_to_Char(uint8_t entero)
{
	switch (entero)
	{
		case CERO:
			string_dummy[0] = '0';
			break;
		case UNO:
			string_dummy[0] = '1';
			break;
		case DOS:
			string_dummy[0] = '2';
			break;
		case TRES:
			string_dummy[0] = '3';
			break;
		case CUATRO:
			string_dummy[0] = '4';
			break;
		case CINCO:
			string_dummy[0] = '5';
			break;
		case SEIS:
			string_dummy[0] = '6';
			break;
		case SIETE:
			string_dummy[0] = '7';
			break;
		case OCHO:
			string_dummy[0] = '8';
			break;
		case NUEVE:
			string_dummy[0] = '9';
			break;
		default:
			break;
	}
	return string_dummy[0];
}
