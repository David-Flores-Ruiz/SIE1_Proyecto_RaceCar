/*
 * @file:			RTC.h
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */


#ifndef RTC_H_
#define RTC_H_


#include <stdint.h>
#include <stdio.h>
#include "I2C.h"

#define SYSTEM_CLOCK (10500000U)
#define BAUD_RATE (9600U)

#define RTC_ADDRESS_WRITE (0xDE)	//** The last bit = 0, means Write */
#define RTC_ADDRESS_READ  (0xDF)	//** The last bit = 1, means Reade */

#define Enable_OSC   (0x80)	//** Para no leer el oscillator bit */
#define NOT_LEAP_YR  (0x20)	//** Para no leer el bit de anio bisiesto */
#define INITIAL_0x00 (0x00) //** Para inicializar los registros de tiempo y fecha */

#define RTC_SEC  (0x00)
#define RTC_MIN  (0x01)
#define RTC_HOUR (0x02)

#define RTC_DATE  (0x04)
#define RTC_MONTH (0x05)
#define RTC_YEAR  (0x06)

//** Macros for propose to debug and modified the initial value of the Time registers */
#define HOURS_23_hex   (0x23)
#define MINUTES_59_hex (0x59)
#define SECONDS_30_hex (0x30)

#define DATE_21_hex  (0x31)
#define MONTH_11_hex (0x12)
#define YEAR_19_hex  (0x19)

typedef enum {
	DATE, MONTH, YEAR, HOUR, MIN, SEC
} Specific_RTC_Register_t;

void RTC_write_Seconds(void); //**Inicializa los segundos*/
void RTC_read_Seconds(void);  //**Lee el registro de los segundos*/
uint8_t RTC_Get_Seconds (void); //** In Decimal format*/

void RTC_write_Minutes(void); //**Inicializa los minutos*/
void RTC_read_Minutes(void);  //**Lee el registro de los minutos*/
uint8_t RTC_Get_Minutes (void); //** In Decimal format*/

void RTC_write_Hours(void);   //**Inicializa las horas*/
void RTC_read_Hours(void);	  //**Lee el registro de las horas*/
uint8_t RTC_Get_Hours (void);	//** In Decimal format*/

void RTC_write_DATE(void);	  //**Inicializa el dia*/
void RTC_read_DATE(void);	  //**Lee el registro de los dias*/
uint8_t RTC_Get_DATE (void);	//** In Decimal format*/

void RTC_write_MONTH(void);	  //**Inicializa el mes*/
void RTC_read_MONTH(void);	  //**Lee el registro de los meses*/
uint8_t RTC_Get_MONTH(void);	//** In Decimal format*/

void RTC_write_YEAR(void);	  //**Inicializa el anio*/
void RTC_read_YEAR(void);	  //**Lee el registro del anio*/
uint8_t RTC_Get_YEAR(void);		//** In Decimal format*/

void RTC_Print_in_MCUXpresso_Console(void);	//**Only for my own Debug*/



#endif /* RTC_H_ */
