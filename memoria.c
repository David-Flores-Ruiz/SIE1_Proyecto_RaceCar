/*
 * memoria.c
 *
 *  Created on: 15 nov 2019
 *      Author: pacas
 */

#include "memoria.h"

#define ARRAY_dataFromMemory_1 &datafrommemmory_1[0]
#define ARRAY_dataFromMemory_2 &datafrommemmory_2[0]
#define ARRAY_dataFromMemory_3 &datafrommemmory_3[0]
#define ARRAY_dataFromMemory_4 &datafrommemmory_4[0]
#define ARRAY_dataFromMemory_5 &datafrommemmory_5[0]

uint8_t g_mensaje_1_array_read[30] = { '1', ' ' };
uint8_t g_mensaje_2_array_read[30] = { '2', ' ' };
uint8_t g_mensaje_3_array_read[30] = { '3', ' ' };
uint8_t g_mensaje_4_array_read[30] = { '4', ' ' };
uint8_t g_mensaje_5_array_read[30] = { '5', ' ' };

uint8_t datafrommemmory_1[30] = { 0 };
uint8_t datafrommemmory_2[30] = { 0 };
uint8_t datafrommemmory_3[30] = { 0 };
uint8_t datafrommemmory_4[30] = { 0 };
uint8_t datafrommemmory_5[30] = { 0 };


static uint8_t g_flag_array = 0;


void memoria_write(void) {
	I2C_start(); //** It configures de I2C in transmitting mode and generates the start signal */
	I2C_write_byte(MEMMORY_WRITE);
	I2C_wait();
	I2C_write_byte(0x00); //ADDRESS HIGH
	I2C_wait();
	I2C_write_byte(0x30); //ADDRESS HIGH
	I2C_wait();
	I2C_write_byte(0xBB);
	I2C_wait();
	I2C_stop();
}

void memoria_write_mensaje_to_memmory(uint8_t num_mensaje) {
	static uint8_t index_data = 0;

	uint8_t* ptr_Message_1 = Get_mensaje_1();

	uint8_t* ptr_Message_2 = Get_mensaje_2();

	uint8_t* ptr_Message_3 = Get_mensaje_3();

	uint8_t* ptr_Message_4 = Get_mensaje_4();

	uint8_t* ptr_Message_5 = Get_mensaje_5();

	switch (num_mensaje)
	{
		case mensaje_1:
			I2C_start(); //** It configures de I2C in transmitting mode and generates the start signal */
			I2C_write_byte(MEMMORY_WRITE);
			I2C_wait();
			I2C_write_byte(0x00); //ADDRESS HIGH
			I2C_wait();
			I2C_write_byte(0x00); //ADDRESS LOW
			I2C_wait();

			while (1) {
				I2C_write_byte(ptr_Message_1[index_data]);
				I2C_wait();

				if (ptr_Message_1[index_data] == '\0') {
					index_data = 0;
					I2C_stop();
					break;
				}

				index_data++;

				if (index_data == MAX) {
					index_data = 0;
					I2C_stop();
					break;
				}
			}
			break;

		case mensaje_2:
			I2C_start(); //** It configures de I2C in transmitting mode and generates the start signal */
			I2C_write_byte(MEMMORY_WRITE);
			I2C_wait();
			I2C_write_byte(0x00); //ADDRESS HIGH
			I2C_wait();
			I2C_write_byte(0x30); //ADDRESS LOW
			I2C_wait();

			while (1) {
				I2C_write_byte(ptr_Message_2[index_data]);
				I2C_wait();

				if (ptr_Message_2[index_data] == '\0') {
					index_data = 0;
					I2C_stop();
					break;
				}

				index_data++;

				if (index_data == MAX) {
					index_data = 0;
					I2C_stop();
					break;
				}
			}
			break;

		case mensaje_3:
			I2C_start(); //** It configures de I2C in transmitting mode and generates the start signal */
			I2C_write_byte(MEMMORY_WRITE);
			I2C_wait();
			I2C_write_byte(0x00); //ADDRESS HIGH
			I2C_wait();
			I2C_write_byte(0x60); //ADDRESS LOW
			I2C_wait();

			while (1) {
				I2C_write_byte(g_mensaje_3_array_read[index_data]);
				I2C_wait();

				if (g_mensaje_3_array_read[index_data] == '\0') {
					index_data = 0;
					I2C_stop();
					break;
				}

				index_data++;

				if (index_data == MAX) {
					index_data = 0;
					I2C_stop();
					break;
				}
			}
			break;

		case mensaje_4:
			I2C_start(); //** It configures de I2C in transmitting mode and generates the start signal */
			I2C_write_byte(MEMMORY_WRITE);
			I2C_wait();
			I2C_write_byte(0x00); //ADDRESS HIGH
			I2C_wait();
			I2C_write_byte(0x90); //ADDRESS LOW
			I2C_wait();

			while (1) {
				I2C_write_byte(g_mensaje_4_array_read[index_data]);
				I2C_wait();

				if (g_mensaje_4_array_read[index_data] == '\0') {
					index_data = 0;
					I2C_stop();
					break;
				}

				index_data++;

				if (index_data == MAX) {
					index_data = 0;
					I2C_stop();
					break;
				}
			}
			break;

		case mensaje_5:
			I2C_start(); //** It configures de I2C in transmitting mode and generates the start signal */
			I2C_write_byte(MEMMORY_WRITE);
			I2C_wait();
			I2C_write_byte(0x00); //ADDRESS HIGH
			I2C_wait();
			I2C_write_byte(0xC0); //ADDRESS LOW
			I2C_wait();

			while (1) {
				I2C_write_byte(g_mensaje_5_array_read[index_data]);
				I2C_wait();
				if (g_mensaje_5_array_read[index_data] == '\0') {
					index_data = 0;
					I2C_stop();
					break;
				}

				index_data++;

				if (index_data == MAX) {
					index_data = 0;
					I2C_stop();
					break;
				}
			}
			break;

	} // switch (num_mensaje)
}

void memoria_read_byte(uint8_t num_mensaje) {
	static uint8_t index_low = 0;
	static uint8_t addres_mensaje0 = 0x00;
	static uint8_t addres_mensaje1 = 0x30;
	static uint8_t addres_mensaje2 = 0x60;
	static uint8_t addres_mensaje3 = 0x90;
	static uint8_t addres_mensaje4 = 0xC0;
	switch (num_mensaje)
	{
		case mensaje_1:
			I2C_start();
			I2C_write_byte(MEMMORY_WRITE);
			I2C_wait();
			I2C_write_byte(0x00);
			I2C_wait();
			I2C_write_byte(addres_mensaje0);
			I2C_wait();
			I2C_repeted_start();
			I2C_write_byte(MEMMORY_READ);
			I2C_wait();

			I2C_tx_rx_mode(I2C_RX_mode);
			I2C_nack_or_ack(Nacknowledge);

			datafrommemmory_1[index_low] = I2C_read_byte(); //dummy read
			I2C_wait();
			I2C_stop();
			datafrommemmory_1[index_low] = I2C_read_byte(); //dato read

			if (datafrommemmory_1[index_low] == '\0') {
				index_low = 0;
				g_flag_array = TRUE;
				addres_mensaje0 = 0x00;
				break;
			}

			index_low++;
			addres_mensaje0++;
			break;

		case mensaje_2:
			I2C_start();
			I2C_write_byte(MEMMORY_WRITE);
			I2C_wait();
			I2C_write_byte(0x00);
			I2C_wait();
			I2C_write_byte(addres_mensaje1);
			I2C_wait();
			I2C_repeted_start();
			I2C_write_byte(MEMMORY_READ);
			I2C_wait();

			I2C_tx_rx_mode(I2C_RX_mode);
			I2C_nack_or_ack(Nacknowledge);

			datafrommemmory_2[index_low] = I2C_read_byte(); //dummy read
			I2C_wait();
			I2C_stop();
			datafrommemmory_2[index_low] = I2C_read_byte(); //dato read

			if (datafrommemmory_2[index_low] == '\0') {
				index_low = 0;
				g_flag_array = TRUE;
				addres_mensaje1 = 0x30;
				break;
			}

			index_low++;
			addres_mensaje1++;
			break;

		case mensaje_3:
			I2C_start();
			I2C_write_byte(MEMMORY_WRITE);
			I2C_wait();
			I2C_write_byte(0x00);
			I2C_wait();
			I2C_write_byte(addres_mensaje2);
			I2C_wait();
			I2C_repeted_start();
			I2C_write_byte(MEMMORY_READ);
			I2C_wait();

			I2C_tx_rx_mode(I2C_RX_mode);
			I2C_nack_or_ack(Nacknowledge);

			datafrommemmory_3[index_low] = I2C_read_byte(); //dummy read
			I2C_wait();
			I2C_stop();
			datafrommemmory_3[index_low] = I2C_read_byte(); //dato read

			if (datafrommemmory_3[index_low] == '\0') {
				index_low = 0;
				addres_mensaje2 = 0x60;
				g_flag_array = TRUE;
				break;
			}

			index_low++;
			addres_mensaje2++;
			break;

		case mensaje_4:
			I2C_start();
			I2C_write_byte(MEMMORY_WRITE);
			I2C_wait();
			I2C_write_byte(0x00);
			I2C_wait();
			I2C_write_byte(addres_mensaje3);
			I2C_wait();
			I2C_repeted_start();
			I2C_write_byte(MEMMORY_READ);
			I2C_wait();

			I2C_tx_rx_mode(I2C_RX_mode);
			I2C_nack_or_ack(Nacknowledge);

			datafrommemmory_4[index_low] = I2C_read_byte(); //dummy read
			I2C_wait();
			I2C_stop();
			datafrommemmory_4[index_low] = I2C_read_byte(); //dato read

			if (datafrommemmory_4[index_low] == '\0') {
				index_low = 0;
				g_flag_array = TRUE;
				addres_mensaje3 = 0x90;
				break;
			}

			index_low++;
			addres_mensaje3++;
			break;

		case mensaje_5:
			I2C_start();
			I2C_write_byte(MEMMORY_WRITE);
			I2C_wait();
			I2C_write_byte(0x00);
			I2C_wait();
			I2C_write_byte(addres_mensaje4);
			I2C_wait();
			I2C_repeted_start();
			I2C_write_byte(MEMMORY_READ);
			I2C_wait();

			I2C_tx_rx_mode(I2C_RX_mode);
			I2C_nack_or_ack(Nacknowledge);

			datafrommemmory_5[index_low] = I2C_read_byte(); //dummy read
			I2C_wait();
			I2C_stop();
			datafrommemmory_5[index_low] = I2C_read_byte(); //dato read

			if (datafrommemmory_5[index_low] == '\0') {
				index_low = 0;
				addres_mensaje4 = 0xC0;
				g_flag_array = TRUE;
				break;
			}

			index_low++;
			addres_mensaje4++;
			break;

	} // switch (num_mensaje)
}

void memoria_FSM(uint8_t num_mensaje) {
	switch (num_mensaje)
	{
		case mensaje_1:
			while (g_flag_array == FALSE) {
				memoria_read_byte(mensaje_1);
			}
			g_flag_array = FALSE;
			break;

		case mensaje_2:
			while (g_flag_array == FALSE) {
				memoria_read_byte(mensaje_2);
			}
			g_flag_array = FALSE;
			break;

		case mensaje_3:
			while (g_flag_array == FALSE) {
				memoria_read_byte(mensaje_3);
			}
			g_flag_array = FALSE;
			break;

		case mensaje_4:
			while (g_flag_array == FALSE) {
				memoria_read_byte(mensaje_4);
			}
			g_flag_array = FALSE;
			break;

		case mensaje_5:
			while (g_flag_array == FALSE) {
				memoria_read_byte(mensaje_5);
			}
			g_flag_array = FALSE;
			break;

	}
}

uint8_t* Get_dataMemory_1(void) {
	uint8_t* ptr_dataMemory_1 = ARRAY_dataFromMemory_1;
	return (ptr_dataMemory_1);
}

uint8_t* Get_dataMemory_2(void) {
	uint8_t* ptr_dataMemory_2 = ARRAY_dataFromMemory_2;
	return (ptr_dataMemory_2);
}

uint8_t* Get_dataMemory_3(void) {
	uint8_t* ptr_dataMemory_3 = ARRAY_dataFromMemory_3;
	return (ptr_dataMemory_3);
}

uint8_t* Get_dataMemory_4(void) {
	uint8_t* ptr_dataMemory_4 = ARRAY_dataFromMemory_4;
	return (ptr_dataMemory_4);
}

uint8_t* Get_dataMemory_5(void) {
	uint8_t* ptr_dataMemory_5 = ARRAY_dataFromMemory_5;
	return (ptr_dataMemory_5);
}
