/*
 * @file:			Accel_FXOS8700CQ.c
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */


#include "Accel_FXOS8700CQ.h"
#include "I2C.h"
#include <stdio.h>

//#define DEBUG_ON	 	//** For debugging purposes */


static SRAWDATA g_ACC_XYZ = {0};
static int32_t g_ACC_X_promedio = 0;
static int32_t g_ACC_Y_promedio = 0;
volatile int16_t g_MOVE_X = 0;
volatile int16_t g_MOVE_Y = 0;


/*	This function configures the FXOS8700CQ for 200-Hz hybrid mode meaning that both
 *  accelerometer and magnetometer data are provided at the 200-Hz rate. The code is
 *  self-explanatory and can be easily customized for different settings.
 */

//** Example 5. */

//** function configures FXOS8700CQ combination accelerometer and magnetometer sensor */
void Accel_Init(void)
{
		// read and check the FXOS8700CQ WHOAMI register
//* Start: low level I2C driver code for READ byte */
	uint8_t databyte = 0;

	// Parameters for function:	   Para escribir,	Nombre Registro,	 Que quiero LEER;
	databyte = I2C_READ_byte_routine(ACCEL_ADDRESS_WRITE, FXOS8700CQ_WHOAMI, ACCEL_ADDRESS_READ);
	if (databyte == FXOS8700CQ_WHOAMI_VAL) {
#ifdef DEBUG_ON
		printf("\nAqui estoy! FXOS8700CQ... acelerometro de la K64 \n");
#endif
	}
	// WHO_AM_I, result should be 0xC7
//** End: READ I2C byte */

	// write 0000 0000 = 0x00 to accelerometer control register 1 to place FXOS8700CQ into
	// standby
	// [7-1] = 0000 000
	// [0]: active=0

	databyte = 0x00;
	I2C_WRITE_byte_routine(ACCEL_ADDRESS_WRITE, FXOS8700CQ_CTRL_REG1, databyte);

	// write 0000 0001= 0x01 to XYZ_DATA_CFG register
	// [7]: reserved
	// [6]: reserved
	// [5]: reserved
	// [4]: hpf_out=0
	// [3]: reserved
	// [2]: reserved
	// [1-0]: fs=01 for accelerometer range of +/-4g range with 0.488mg/LSB
	databyte = 0x01;
	I2C_WRITE_byte_routine(ACCEL_ADDRESS_WRITE, FXOS8700CQ_XYZ_DATA_CFG, databyte);

	// write 0000 1101 = 0x0D to accelerometer control register 1
	// [7-6]: aslp_rate=00
	// [5-3]: dr=001 for 400Hz data rate (when is in Only mode)
	// [2]: lnoise=1 for low noise mode
	// [1]: f_read=0 for normal 16 bit reads
	// [0]: active=1 to take the part out of standby and enable sampling
	databyte = 0x0D;
	// databyte = 0x37;
	I2C_WRITE_byte_routine(ACCEL_ADDRESS_WRITE, FXOS8700CQ_CTRL_REG1, databyte);
}

void Accel_READ_XYZ(void)
{
	static uint8_t cont_avg = 0;

													   //** READ "X" AXIS */
	g_ACC_XYZ.x =  I2C_READ_byte_routine(ACCEL_ADDRESS_WRITE, OUT_X_MSB_REG, ACCEL_ADDRESS_READ);
	g_ACC_XYZ.x =  (g_ACC_XYZ.x << 8);
	g_ACC_XYZ.x |= I2C_READ_byte_routine(ACCEL_ADDRESS_WRITE, OUT_X_LSB_REG, ACCEL_ADDRESS_READ);

													   //** READ "Y" AXIS */
	g_ACC_XYZ.y =  I2C_READ_byte_routine(ACCEL_ADDRESS_WRITE, OUT_Y_MSB_REG, ACCEL_ADDRESS_READ);
	g_ACC_XYZ.y =  (g_ACC_XYZ.y << 8);
	g_ACC_XYZ.y |= I2C_READ_byte_routine(ACCEL_ADDRESS_WRITE, OUT_Y_LSB_REG, ACCEL_ADDRESS_READ);


	g_ACC_X_promedio = (g_ACC_X_promedio + g_ACC_XYZ.x);
	g_ACC_Y_promedio = (g_ACC_Y_promedio + g_ACC_XYZ.y);
	cont_avg ++;

	if (cont_avg == 8){
		g_ACC_X_promedio = g_ACC_X_promedio >> 3;
		g_ACC_Y_promedio = g_ACC_Y_promedio >> 3;

		g_MOVE_X = g_ACC_X_promedio;
		g_MOVE_Y = g_ACC_Y_promedio;

#ifdef DEBUG_ON
		printf("Fuerza g en eje X: %d  ", g_MOVE_X);
		printf("----- Fuerza g en eje Y: %d \n", g_MOVE_Y);
#endif

		cont_avg = 0;
		g_ACC_X_promedio = 0;
		g_ACC_Y_promedio = 0;
	}
}

State_Accel_t Accel_GET_MOVE(void)
{
	static State_Accel_t MOVE_ACTUAL = Move_STOP;

	//** Detecta movimiento en eje X ¿Derecha o Izquierda? */
	if (g_MOVE_X >  5000 && g_MOVE_X  <  10000)
		MOVE_ACTUAL = Move_DER;
	else if (g_MOVE_X < -5000 && g_MOVE_X < -10000)
		MOVE_ACTUAL = Move_IZQ;

	//** Detecta movimiento en eje Y ¿Arriba o Abajo? */
	else if (g_MOVE_Y >  5000 && g_MOVE_Y <  10000)
		MOVE_ACTUAL = Move_ABAJO;
	else if (g_MOVE_Y < -5000 && g_MOVE_Y < -10000)
		MOVE_ACTUAL = Move_ARRIBA;

	//** No se esta moviendo lo suficiente en X ni en Y */
	else
		MOVE_ACTUAL = Move_STOP;

	return (MOVE_ACTUAL);
}





