/*
 * @file:			Accel_FXOS8700CQ.h
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#ifndef ACCEL_FXOS8700CQ_H_
#define ACCEL_FXOS8700CQ_H_

#include <stdint.h>

#define MAX_enX 9000	//** Con resolucion en 14 bits
#define MAX_enY 9000	//** + Prueba experimental 		*/

#define X_Motion_Threshold 4000	//** Valor que puede ser +- 9000 para
#define Y_Motion_Threshold 3200 //** aumentar sensibilidad del control */


//** Estructura que controla movimientos de la K64 sujetandola */
//** como control si el Ethernet esta mas cecarno a ti */
typedef struct
{
	uint8_t flag_Arriba 	: 1;
	uint8_t flag_Abajo 		: 1;
	uint8_t flag_STOP		: 1;
	uint8_t flag_Izquierda  : 1;
	uint8_t flag_Derecha 	: 1;
} Accel_flags_t;

typedef enum {
	Move_ARRIBA, Move_ABAJO, Move_STOP, Move_IZQ, Move_DER
} State_Accel_t;

//** The next code it is from PDF: "User Guide FRDM-K64F" */


//** Example 1. */

// FXOS8700CQ I2C address-default page13 User Guide FRDM-K64F
//#define FXOS8700CQ_SLAVE_ADDR 0x1E // with pins  SA1=0, SA0=0
  #define FXOS8700CQ_SLAVE_ADDR 0x1D // with pins  SA1=0, SA0=1
//#define FXOS8700CQ_SLAVE_ADDR 0x1C // with pins  SA1=1, SA0=0
//#define FXOS8700CQ_SLAVE_ADDR 0x1F // with pins  SA1=1, SA0=1

#define ACCEL_ADDRESS_WRITE (0x3A)	// (0x1D) << 1 + "0" for WRITE
#define ACCEL_ADDRESS_READ	(0x3B)	// (0x1D) << 1 + "1" for READ


//** Example 2. */

// FXOS8700CQ internal register addresses
#define FXOS8700CQ_STATUS 0x00
#define OUT_X_MSB_REG 0x01  // [7:0] are 8 MSBs of 14-bit acceleration data for X-axis
#define OUT_X_LSB_REG 0x02  // [7:2] are the 6 LSB of 14-bit acceleration data for X-axis
#define OUT_Y_MSB_REG 0x03  // [7:0] are 8 MSBs of 14-bit acceleration data for Y-axis
#define OUT_Y_LSB_REG 0x04  // [7:2] are the 6 LSB of 14-bit acceleration data for Y-axis
#define OUT_Z_MSB_REG 0x05  // [7:0] are 8 MSBs of 14-bit acceleration data for Z-axis
#define OUT_Z_LSB_REG 0x06  // [7:2] are the 6 LSB of 14-bit acceleration data for Z-axis

#define FXOS8700CQ_WHOAMI 0x0D
#define FXOS8700CQ_XYZ_DATA_CFG 0x0E
#define FXOS8700CQ_CTRL_REG1 0x2A
#define FXOS8700CQ_M_CTRL_REG1 0x5B
#define FXOS8700CQ_M_CTRL_REG2 0x5C
#define FXOS8700CQ_WHOAMI_VAL 0xC7



/*
 *	The reference driver code shown in this example does a block read of the FXOS8700CQ
 *	status byte and three 16-bit accelerometer channels plus three 16-bit magnetometer
 *	channels for a total of 13 bytes in a single I2C read operation.
 */

//** Example 3. */

// number of bytes to be read from the FXOS8700CQ
#define FXOS8700CQ_READ_LEN 13 // status plus 6 channels = 13 bytes


/*  The high and low bytes of the three accelerometer and three magnetometer channels are
 *  placed into a structure of type SRAWDATA containing three signed short integers.
 */

//** Example 4. */

typedef struct {
	int16_t x;
	int16_t y;
	int16_t z;
} SRAWDATA;


void Accel_Init(void);
void Accel_Read(void);
void Accel_READ_XYZ(void);

State_Accel_t Accel_GET_MOVE(void);
void FSM_ACELEROMETRO(void);

#endif /* ACCEL_FXOS8700CQ_H_ */
