/*
 * @file:			RTC.c
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */


#include "RTC.h"
#include "TeraTerm.h"

	uint8_t g_SEC = 0;	// Listo para convertir a cadena con Time_to_String()
	uint8_t g_MIN = 0;
	uint8_t g_HR  = 0;

	uint8_t g_DATE  = 0;
	uint8_t g_MONTH = 0;
	uint8_t g_YEAR  = 0;

void RTC_write_Seconds(void)
{
	uint8_t* ptr_modified_seconds = Get_modified_seconds(); // Horas en ASCII equivalente en Decimal

	uint8_t modified_DEC = 0;
	uint8_t modified_UNI = 0;
	uint8_t new_SECONDS_hex = 0;

	modified_DEC = (uint8_t)*(ptr_modified_seconds + 0);
	modified_UNI = (uint8_t)*(ptr_modified_seconds + 1);

	modified_DEC = (modified_DEC - 48) << 4;	//** Para llegar al inicio de la tabla ASCII*/
	modified_UNI = (modified_UNI - 48) << 0; 	//** Para llegar al inicio de la tabla ASCII*/

	new_SECONDS_hex = modified_DEC + modified_UNI;


	uint8_t acknowledge = 0xF0;
	I2C_start();//** It configures de I2C in transmitting mode and generates the start signal */

	I2C_write_byte(RTC_ADDRESS_WRITE);//** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK
	 */

	I2C_write_byte( RTC_SEC);	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK

	 */
	I2C_write_byte(Enable_OSC | new_SECONDS_hex);	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();// Waiting for the acknowledge, this function is able to detect
	I2C_stop();	//** Generating stop signal */
}

void RTC_read_Seconds(void)
{
	uint8_t aux_Unit = 0;
	uint8_t aux_Tens = 0;
	uint8_t acknowledge = 0xF0;

	uint8_t dataFrom_MCP7940M_RTC = 0;
	I2C_start();//** It configures de I2C in transmitting mode and generates the start signal */

	I2C_write_byte(RTC_ADDRESS_WRITE);//** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();

	I2C_write_byte( RTC_SEC );	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();
	// Return 0: if an acknowledge was received!!!

	I2C_repeted_start();	// Generating a new start
	I2C_write_byte(RTC_ADDRESS_READ);//** Writing slave in order to read the previous register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK
	 */
	I2C_tx_rx_mode(I2C_RX_mode);	//** Changing I2C module to receiver mode */

	I2C_nack_or_ack(Nacknowledge);	//** Generating not acknowledge */
	dataFrom_MCP7940M_RTC = I2C_read_byte();	//** Dummy read */
	I2C_wait();	//** Checking if the I2C module is busy */

	I2C_stop();	//** Generating stop signal */

	dataFrom_MCP7940M_RTC = I2C_read_byte();	  //** Reading the true value */
	aux_Unit = dataFrom_MCP7940M_RTC & (~Enable_OSC); //** Delete MSB from oscillator */
	aux_Tens = aux_Unit;
	aux_Unit = (aux_Unit >> 0) & (0x0F); //** Units of Seconds*/
	aux_Tens = (aux_Tens >> 4) & (0x0F); //** Tens of Seconds */

	g_SEC = (aux_Tens * 10) + (aux_Unit * 1);
	//** g_SEC: Bit 6 - 4 = Contains a value from 0 to 5 */
	//**		Bit 3 - 0 = Contains a value from 0 to 9 */
}

uint8_t RTC_Get_Seconds (void) {
	uint8_t Seconds_in_decimal = g_SEC;
	return (Seconds_in_decimal);
}

void RTC_write_Minutes(void)
{
	uint8_t* ptr_modified_minutes = Get_modified_minutes(); // Horas en ASCII equivalente en Decimal

	uint8_t modified_DEC = 0;
	uint8_t modified_UNI = 0;
	uint8_t new_MINUTES_hex = 0;

	modified_DEC = (uint8_t)*(ptr_modified_minutes + 0);
	modified_UNI = (uint8_t)*(ptr_modified_minutes + 1);

	modified_DEC = (modified_DEC - 48) << 4;	//** Para llegar al inicio de la tabla ASCII*/
	modified_UNI = (modified_UNI - 48) << 0; 	//** Para llegar al inicio de la tabla ASCII*/

	new_MINUTES_hex = modified_DEC + modified_UNI;


	uint8_t acknowledge = 0xF0;
	I2C_start();//** It configures de I2C in transmitting mode and generates the start signal */

	I2C_write_byte(RTC_ADDRESS_WRITE);//** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK
	 */

	I2C_write_byte( RTC_MIN );	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK

	 */
	I2C_write_byte(INITIAL_0x00 | new_MINUTES_hex);	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();// Waiting for the acknowledge, this function is able to detect
	I2C_stop();	//** Generating stop signal */
}

void RTC_read_Minutes(void)
{
	uint8_t aux_Unit = 0;
	uint8_t aux_Tens = 0;
	uint8_t acknowledge = 0xF0;

	uint8_t dataFrom_MCP7940M_RTC = 0;
	I2C_start();//** It configures de I2C in transmitting mode and generates the start signal */

	I2C_write_byte(RTC_ADDRESS_WRITE);//** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();

	I2C_write_byte( RTC_MIN );	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();
	// Return 0: if an acknowledge was received!!!

	I2C_repeted_start();	// Generating a new start
	I2C_write_byte(RTC_ADDRESS_READ);//** Writing slave in order to read the previous register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK
	 */
	I2C_tx_rx_mode(I2C_RX_mode);	//** Changing I2C module to receiver mode */

	I2C_nack_or_ack(Nacknowledge);	//** Generating not acknowledge */
	dataFrom_MCP7940M_RTC = I2C_read_byte();	//** Dummy read */
	I2C_wait();	//** Checking if the I2C module is busy */

	I2C_stop();	//** Generating stop signal */

	dataFrom_MCP7940M_RTC = I2C_read_byte();	  //** Reading the true value */
	aux_Unit = dataFrom_MCP7940M_RTC; //** Read the BCD value */
	aux_Tens = aux_Unit;
	aux_Unit = (aux_Unit >> 0) & (0x0F); //** Units of Minutes*/
	aux_Tens = (aux_Tens >> 4) & (0x0F); //** Tens of Minutes */

	g_MIN = (aux_Tens * 10) + (aux_Unit * 1);
	//** g_MIN: Bit 6 - 4 = Contains a value from 0 to 5 */
	//**		Bit 3 - 0 = Contains a value from 0 to 9 */
}

uint8_t RTC_Get_Minutes (void) {
	uint8_t Minutes_in_decimal = g_MIN;
	return (Minutes_in_decimal);
}

void RTC_write_Hours(void)
{
	uint8_t* ptr_modified_hours = Get_modified_hours(); // Horas en ASCII equivalente en Decimal

	uint8_t modified_DEC = 0;
	uint8_t modified_UNI = 0;
	uint8_t new_HOURS_hex = 0;

	modified_DEC = (uint8_t)*(ptr_modified_hours + 0);
	modified_UNI = (uint8_t)*(ptr_modified_hours + 1);

	modified_DEC = (modified_DEC - 48) << 4;	//** Para llegar al inicio de la tabla ASCII*/
	modified_UNI = (modified_UNI - 48) << 0; 	//** Para llegar al inicio de la tabla ASCII*/

	new_HOURS_hex = modified_DEC + modified_UNI;


	uint8_t acknowledge = 0xF0;
	I2C_start();//** It configures de I2C in transmitting mode and generates the start signal */

	I2C_write_byte(RTC_ADDRESS_WRITE);//** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK
	 */

	I2C_write_byte( RTC_HOUR );	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK

	 */
	I2C_write_byte(INITIAL_0x00 | new_HOURS_hex);	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();// Waiting for the acknowledge, this function is able to detect
	I2C_stop();	//** Generating stop signal */
}

void RTC_read_Hours(void)
{
	uint8_t aux_Unit = 0;
	uint8_t aux_Tens = 0;
	uint8_t acknowledge = 0xF0;

	uint8_t dataFrom_MCP7940M_RTC = 0;
	I2C_start();//** It configures de I2C in transmitting mode and generates the start signal */

	I2C_write_byte(RTC_ADDRESS_WRITE);//** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();

	I2C_write_byte( RTC_HOUR );	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();
	// Return 0: if an acknowledge was received!!!

	I2C_repeted_start();	// Generating a new start
	I2C_write_byte(RTC_ADDRESS_READ);//** Writing slave in order to read the previous register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK
	 */
	I2C_tx_rx_mode(I2C_RX_mode);	//** Changing I2C module to receiver mode */

	I2C_nack_or_ack(Nacknowledge);	//** Generating not acknowledge */
	dataFrom_MCP7940M_RTC = I2C_read_byte();	//** Dummy read */
	I2C_wait();	//** Checking if the I2C module is busy */

	I2C_stop();	//** Generating stop signal */

	dataFrom_MCP7940M_RTC = I2C_read_byte();	  //** Reading the true value */
	aux_Unit = dataFrom_MCP7940M_RTC; //** Read the BCD value */
	aux_Tens = aux_Unit;
	aux_Unit = (aux_Unit >> 0) & (0x0F); //** Units of Hours*/
	aux_Tens = (aux_Tens >> 4) & (0x0F); //** Tens of Hours */

	g_HR = (aux_Tens * 10) + (aux_Unit * 1);
	//** g_HR:  Bit 5 - 4 = Contains a value from 0 to 2 */
	//**		Bit 3 - 0 = Contains a value from 0 to 9 */
}

uint8_t RTC_Get_Hours (void) {
	uint8_t Hours_in_decimal = g_HR;
	return (Hours_in_decimal);
}

void RTC_write_DATE(void)
{
	uint8_t* ptr_modified_date = Get_modified_date(); // Horas en ASCII equivalente en Decimal

	uint8_t modified_DEC = 0;
	uint8_t modified_UNI = 0;
	uint8_t new_DATE_hex = 0;

	modified_DEC = (uint8_t)*(ptr_modified_date + 0);
	modified_UNI = (uint8_t)*(ptr_modified_date + 1);

	modified_DEC = (modified_DEC - 48) << 4;	//** Para llegar al inicio de la tabla ASCII*/
	modified_UNI = (modified_UNI - 48) << 0; 	//** Para llegar al inicio de la tabla ASCII*/

	new_DATE_hex = modified_DEC + modified_UNI;


	uint8_t acknowledge = 0xF0;
	I2C_start();//** It configures de I2C in transmitting mode and generates the start signal */

	I2C_write_byte(RTC_ADDRESS_WRITE);//** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK
	 */

	I2C_write_byte( RTC_DATE );	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK

	 */
	I2C_write_byte(INITIAL_0x00 | new_DATE_hex);	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();// Waiting for the acknowledge, this function is able to detect
	I2C_stop();	//** Generating stop signal */
}

void RTC_read_DATE(void)
{
	uint8_t aux_Unit = 0;
	uint8_t aux_Tens = 0;
	uint8_t acknowledge = 0xF0;

	uint8_t dataFrom_MCP7940M_RTC = 0;
	I2C_start();//** It configures de I2C in transmitting mode and generates the start signal */

	I2C_write_byte(RTC_ADDRESS_WRITE);//** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();

	I2C_write_byte( RTC_DATE );	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();
	// Return 0: if an acknowledge was received!!!

	I2C_repeted_start();	// Generating a new start
	I2C_write_byte(RTC_ADDRESS_READ);//** Writing slave in order to read the previous register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK
	 */
	I2C_tx_rx_mode(I2C_RX_mode);	//** Changing I2C module to receiver mode */

	I2C_nack_or_ack(Nacknowledge);	//** Generating not acknowledge */
	dataFrom_MCP7940M_RTC = I2C_read_byte();	//** Dummy read */
	I2C_wait();	//** Checking if the I2C module is busy */

	I2C_stop();	//** Generating stop signal */

	dataFrom_MCP7940M_RTC = I2C_read_byte();	  //** Reading the true value */
	aux_Unit = dataFrom_MCP7940M_RTC; //** Read the BCD value */
	aux_Tens = aux_Unit;
	aux_Unit = (aux_Unit >> 0) & (0x0F); //** Units of Hours*/
	aux_Tens = (aux_Tens >> 4) & (0x0F); //** Tens of Hours */

	g_DATE = (aux_Tens * 10) + (aux_Unit * 1);
	//** g_DATE:  Bit 5 - 4 = Contains a value from 0 to 3 */
	//**		  Bit 3 - 0 = Contains a value from 0 to 9 */
}

uint8_t RTC_Get_DATE (void) {
	uint8_t DATE_in_decimal = g_DATE;
	return (DATE_in_decimal);
}

void RTC_write_MONTH(void)
{
	uint8_t* ptr_modified_month = Get_modified_month(); // Horas en ASCII equivalente en Decimal

	uint8_t modified_DEC = 0;
	uint8_t modified_UNI = 0;
	uint8_t new_MONTH_hex = 0;

	modified_DEC = (uint8_t)*(ptr_modified_month + 0);
	modified_UNI = (uint8_t)*(ptr_modified_month + 1);

	modified_DEC = (modified_DEC - 48) << 4;	//** Para llegar al inicio de la tabla ASCII*/
	modified_UNI = (modified_UNI - 48) << 0; 	//** Para llegar al inicio de la tabla ASCII*/

	new_MONTH_hex = modified_DEC + modified_UNI;


	uint8_t acknowledge = 0xF0;
	I2C_start();//** It configures de I2C in transmitting mode and generates the start signal */

	I2C_write_byte(RTC_ADDRESS_WRITE);//** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK
	 */

	I2C_write_byte( RTC_MONTH );	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK

	 */
	I2C_write_byte(INITIAL_0x00 | new_MONTH_hex);	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();// Waiting for the acknowledge, this function is able to detect
	I2C_stop();	//** Generating stop signal */
}

void RTC_read_MONTH(void)
{
	uint8_t aux_Unit = 0;
	uint8_t aux_Tens = 0;
	uint8_t acknowledge = 0xF0;

	uint8_t dataFrom_MCP7940M_RTC = 0;
	I2C_start();//** It configures de I2C in transmitting mode and generates the start signal */

	I2C_write_byte(RTC_ADDRESS_WRITE);//** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();

	I2C_write_byte( RTC_MONTH );	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();
	// Return 0: if an acknowledge was received!!!

	I2C_repeted_start();	// Generating a new start
	I2C_write_byte(RTC_ADDRESS_READ);//** Writing slave in order to read the previous register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK
	 */
	I2C_tx_rx_mode(I2C_RX_mode);	//** Changing I2C module to receiver mode */

	I2C_nack_or_ack(Nacknowledge);	//** Generating not acknowledge */
	dataFrom_MCP7940M_RTC = I2C_read_byte();	//** Dummy read */
	I2C_wait();	//** Checking if the I2C module is busy */

	I2C_stop();	//** Generating stop signal */

	dataFrom_MCP7940M_RTC = I2C_read_byte();	  //** Reading the true value */
	aux_Unit = dataFrom_MCP7940M_RTC & (~NOT_LEAP_YR); //** Delete bit from LPYR */
	aux_Tens = aux_Unit;
	aux_Unit = (aux_Unit >> 0) & (0x0F); //** Units of Hours*/
	aux_Tens = (aux_Tens >> 4) & (0x0F); //** Tens of Hours */

	g_MONTH = (aux_Tens * 10) + (aux_Unit * 1);
	//** g_MONTH:  Bit   4   = Contains a value from 0 to 1 */
	//**		   Bit 3 - 0 = Contains a value from 0 to 9 */
}

uint8_t RTC_Get_MONTH (void) {
	uint8_t MONTH_in_decimal = g_MONTH;
	return (MONTH_in_decimal);
}

void RTC_write_YEAR(void)
{
	uint8_t* ptr_modified_year = Get_modified_year(); // Horas en ASCII equivalente en Decimal

	uint8_t modified_DEC = 0;
	uint8_t modified_UNI = 0;
	uint8_t new_YEAR_hex = 0;

	modified_DEC = (uint8_t)*(ptr_modified_year + 0);
	modified_UNI = (uint8_t)*(ptr_modified_year + 1);

	modified_DEC = (modified_DEC - 48) << 4;	//** Para llegar al inicio de la tabla ASCII*/
	modified_UNI = (modified_UNI - 48) << 0; 	//** Para llegar al inicio de la tabla ASCII*/

	new_YEAR_hex = modified_DEC + modified_UNI;


	uint8_t acknowledge = 0xF0;
	I2C_start();//** It configures de I2C in transmitting mode and generates the start signal */

	I2C_write_byte(RTC_ADDRESS_WRITE);//** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK
	 */

	I2C_write_byte( RTC_YEAR );	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK

	 */
	I2C_write_byte(INITIAL_0x00 | new_YEAR_hex);	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();// Waiting for the acknowledge, this function is able to detect
	I2C_stop();	//** Generating stop signal */
}

void RTC_read_YEAR(void)
{
	uint8_t aux_Unit = 0;
	uint8_t aux_Tens = 0;
	uint8_t acknowledge = 0xF0;

	uint8_t dataFrom_MCP7940M_RTC = 0;
	I2C_start();//** It configures de I2C in transmitting mode and generates the start signal */

	I2C_write_byte(RTC_ADDRESS_WRITE);//** Writing RTC address in the data register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();

	I2C_write_byte( RTC_YEAR );	//** Writing the Register Address */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack();
	// Return 0: if an acknowledge was received!!!

	I2C_repeted_start();	// Generating a new start
	I2C_write_byte(RTC_ADDRESS_READ);//** Writing slave in order to read the previous register */
	I2C_wait();	//** Checking if the I2C module is busy */
	acknowledge = I2C_get_ack_or_nack(); /* Waiting for the acknowledge, this function is able to detect
	 // Return 0: if an acknowledge was received!!!	 * if an acknowledge was received by checking the RXAK
	 */
	I2C_tx_rx_mode(I2C_RX_mode);	//** Changing I2C module to receiver mode */

	I2C_nack_or_ack(Nacknowledge);	//** Generating not acknowledge */
	dataFrom_MCP7940M_RTC = I2C_read_byte();	//** Dummy read */
	I2C_wait();	//** Checking if the I2C module is busy */

	I2C_stop();	//** Generating stop signal */

	dataFrom_MCP7940M_RTC = I2C_read_byte();	  //** Reading the true value */
	aux_Unit = dataFrom_MCP7940M_RTC; 	//** BCD value */
	aux_Tens = aux_Unit;
	aux_Unit = (aux_Unit >> 0) & (0x0F); //** Units of Hours*/
	aux_Tens = (aux_Tens >> 4) & (0x0F); //** Tens of Hours */

	g_YEAR = (aux_Tens * 10) + (aux_Unit * 1);
	//** g_YEAR:  Bit 7 - 4 = Contains a value from 0 to 9 */
	//**		  Bit 3 - 0 = Contains a value from 0 to 9 */
}

uint8_t RTC_Get_YEAR (void) {
	uint8_t YEAR_in_decimal = g_YEAR;
	return (YEAR_in_decimal);
}

void RTC_Print_in_MCUXpresso_Console(void) {
	uint8_t RTC_Decimal_seconds = 0;
	uint8_t RTC_Decimal_minutes = 0;
	uint8_t RTC_Decimal_hours = 0;

	uint8_t RTC_Decimal_date = 0;
	uint8_t RTC_Decimal_month = 0;
	uint8_t RTC_Decimal_year = 0;

	RTC_read_DATE();	//** Lee el dia (fecha) del RTC */
	RTC_Decimal_date = RTC_Get_DATE(); 	 	 //** In Decimal Format */
	printf("Dia: %d - ", RTC_Decimal_date);

	RTC_read_MONTH();	//** Lee el mes del RTC */
	RTC_Decimal_month = RTC_Get_MONTH(); 	 //** In Decimal Format */
	printf("Mes: %d - ", RTC_Decimal_month);

	RTC_read_YEAR();	//** Lee el anio del RTC */
	RTC_Decimal_year = RTC_Get_YEAR(); 	 	 //** In Decimal Format */
	printf("Anio: %d - ", RTC_Decimal_year);

	RTC_read_Hours();	//** Lee las horas del RTC */
	RTC_Decimal_hours = RTC_Get_Hours(); 	 //** In Decimal Format */
	printf("Horas: %d - ", RTC_Decimal_hours);

	RTC_read_Minutes(); //** Lee los minutos del RTC */
	RTC_Decimal_minutes = RTC_Get_Minutes(); //** In Decimal Format */
	printf("Minutos: %d - ", RTC_Decimal_minutes);

	RTC_read_Seconds();	//** Lee los segundos del RTC */
	RTC_Decimal_seconds = RTC_Get_Seconds(); //** In Decimal Format */
	printf("Segundos: %d \n", RTC_Decimal_seconds);
}

