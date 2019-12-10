/*
 * @file:			UART.c
 * @company:			ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#include "UART_driver.h"
#include "bits.h"

 uart_mail_box_t g_mail_box_uart_0;
 uart_mail_box_t g_mail_box_uart_3;
 uart_mail_box_t g_mail_box_uart_4;

extern uint8_t g_key_UART3_CONTROL; //** From Bluetooth in Control */
uint8_t one_time = FALSE;

void UART0_RX_TX_IRQHandler( )
{
	while (!(UART0->S1 & UART_S1_RDRF_MASK))
	{
		// Codigo Bloqueante
	}
	g_mail_box_uart_0.mailBox = UART0->D;
	g_mail_box_uart_0.flag = 1;
}

void UART3_RX_TX_IRQHandler( )
{
	while (!(UART3->S1 & UART_S1_RDRF_MASK))
	{
		// Codigo Bloqueante
	}
	g_mail_box_uart_3.mailBox = UART3->D;
	g_mail_box_uart_3.flag = 1;
}

void UART4_RX_TX_IRQHandler( )
{
	while (!(UART4->S1 & UART_S1_RDRF_MASK))
	{
		// Codigo Bloqueante
	}
	g_mail_box_uart_4.mailBox = UART4->D;
	g_mail_box_uart_4.flag = 1;
}

void UART_init(uart_channel_t uart_channel, uint32_t system_clk, uart_baud_rate_t baud_rate)
{
	if (UART_0 == uart_channel) {

		/**Enables the clock of PortB in order to configures TX and RX of UART peripheral*/
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
		/**Configures the pin control register of pin16 in PortB as UART RX*/
		PORTB->PCR[16] = PORT_PCR_MUX(3);
		/**Configures the pin control register of pin16 in PortB as UART TX*/
		PORTB->PCR[17] = PORT_PCR_MUX(3);
		/**Configures UART 0 to transmit/receive at 11520 bauds with a 21 MHz of clock core*/

		SIM->SCGC4 |= 0x0400;
		UART0->C2 &= ~(UART_C2_TE_MASK);
		UART0->C2 &= ~(UART_C2_RE_MASK);
		UART0->BDH |= 0x00;
		UART0->BDL = 0x0B; //seleccion de baudrate con el uso de las tablas
		UART0->C4 |= 0x0D; // BRFA
		UART0->C2 |= UART_C2_TE_MASK | UART_C2_RE_MASK; //encendido para transmitir y recibir
	}
	if (UART_1 == uart_channel) {}
	if (UART_2 == uart_channel) {}
	if (UART_3 == uart_channel) {

		/**Enables the clock of PortB in order to configures TX and RX of UART peripheral*/
		SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
		/**Configures the pin control register of pin16 in PortB as UART RX*/
		PORTC->PCR[16] = PORT_PCR_MUX(3);
		/**Configures the pin control register of pin16 in PortB as UART TX*/
		PORTC->PCR[17] = PORT_PCR_MUX(3);
		/**Configures UART 0 to transmit/receive at 11520 bauds with a 21 MHz of clock core*/

		SIM->SCGC4 |= 0x2000;
		UART3->C2 &= ~(UART_C2_TE_MASK);
		UART3->C2 &= ~(UART_C2_RE_MASK);
		UART3->BDH |= 0x00;
		UART3->BDL = 0x88; //82 - 85 para 9600 //seleccion de baudrate con el uso de las tablas
		UART3->C4 |= 0x17; // BRFA
		UART3->C2 |= UART_C2_TE_MASK | UART_C2_RE_MASK; //encendido para transmitir y recibir
	}
	if (UART_4 == uart_channel) {

		/**Enables the clock of PortB in order to configures TX and RX of UART peripheral*/
		SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
		/**Configures the pin control register of pin16 in PortB as UART RX*/
		PORTE->PCR[25] = PORT_PCR_MUX(3); //** PTE25 = RX */
		/**Configures the pin control register of pin16 in PortB as UART TX*/
		PORTE->PCR[24] = PORT_PCR_MUX(3); //** PTE24 = TX */
		/**Configures UART 0 to transmit/receive at 11520 bauds with a 21 MHz of clock core*/

		SIM->SCGC1 |= 0x0400;
		UART4->C2 &= ~(UART_C2_TE_MASK);
		UART4->C2 &= ~(UART_C2_RE_MASK);
		UART4->BDH |= 0x00;
		UART4->BDL = 0x88; //seleccion de baudrate con el uso de las tablas
		UART4->C4 |= 0x17; // BRFA
		UART4->C2 |= UART_C2_TE_MASK | UART_C2_RE_MASK; //encendido para transmitir y recibir
	}
	if (UART_5 == uart_channel) {}
}

void UART_interrupt_enable(uart_channel_t uart_channel)
{
	if (UART_0 == uart_channel) {
		UART0->C2 |= UART_C2_RIE_MASK;//habilitacion de interrupcion
	}
	if (UART_1 == uart_channel) {}
	if (UART_2 == uart_channel) {}
	if (UART_3 == uart_channel) {
		UART3->C2 |= UART_C2_RIE_MASK;//habilitacion de interrupcion
	}
	if (UART_4 == uart_channel) {
		UART4->C2 |= UART_C2_RIE_MASK;//habilitacion de interrupcion
	}
	if (UART_5 == uart_channel) {}
}

void UART_put_char (uart_channel_t uart_channel, uint8_t character)
{
	if (UART_0 == uart_channel) {
		while (!(UART0->S1 & UART_S1_TC_MASK))//utilizamos el codigo bloqueante para que  termine de transmitir
		{
			// Codigo Bloqueante
		}
		UART0->D = character;

	}
	if (UART_1 == uart_channel) {}
	if (UART_2 == uart_channel) {}
	if (UART_3 == uart_channel) {
		while (!(UART3->S1 & UART_S1_TC_MASK)) //utilizamos el codigo bloqueante para que  termine de transmitir
		{
			// Codigo Bloqueante
		}
		UART3->D = character;
	}
	if (UART_4 == uart_channel) {
		while (!(UART4->S1 & UART_S1_TC_MASK)) //utilizamos el codigo bloqueante para que  termine de transmitir
		{
			// Codigo Bloqueante
		}
		UART4->D = character;
	}
	if (UART_5 == uart_channel) {}
}

void UART_put_string(uart_channel_t uart_channel, uint8_t* string)
{
	uint8_t contador = 0;
	if (UART_0 == uart_channel) {
		while (1) {
			if (string[contador] == '\0') //enviado de caracter  con variable contador qque ayuda a movernos sobre el string
			{
				break;
			}
			UART_put_char(uart_channel, string[contador]);
			contador++;
		}
	}
		if (UART_1 == uart_channel) {}
		if (UART_2 == uart_channel) {}
		if (UART_3 == uart_channel) {
			while (1) {
				if (string[contador] == '\0') //enviado de caracter  con variable contador qque ayuda a movernos sobre el string
						{
					break;
				}
				UART_put_char(uart_channel, string[contador]);
				contador++;
			}
		}
	if (UART_4 == uart_channel) {
		while (1) {
			if (string[contador] == '\0') //enviado de caracter  con variable contador qque ayuda a movernos sobre el string
					{
				break;
			}
			UART_put_char(uart_channel, string[contador]);
			contador++;
		}
	}
		if (UART_5 == uart_channel) {}
}

void ASCII_for_Print_UART0(void) {
	uint8_t char_ASCCI = 0;
	char_ASCCI = g_key_UART3_CONTROL;
	static uint8_t cuenta_metros = 0;

	switch (char_ASCCI % 100) {
		case 0:
			UART_put_string(UART_0, "0 cm");
			one_time = FALSE;
			break;

		case 1:
			UART_put_string(UART_0, "1 cm");
			one_time = FALSE;
			break;

		case 2:
			UART_put_string(UART_0, "2 cm");
			one_time = FALSE;
			break;

		case 3:
			UART_put_string(UART_0, "3 cm");
			one_time = FALSE;
			break;

		case 4:
			UART_put_string(UART_0, "4 cm");
			one_time = FALSE;
			break;

		case 5:
			UART_put_string(UART_0, "5 cm");
			break;

		case 6:
			UART_put_string(UART_0, "6 cm");
			break;

		case 7:
			UART_put_string(UART_0, "7 cm");
			break;

		case 8:
			UART_put_string(UART_0, "8 cm");
			break;

		case 9:
			UART_put_string(UART_0, "9 cm");
			break;

		case 10:
			UART_put_string(UART_0, "10 cm");
			break;

		case 11:
			UART_put_string(UART_0, "11 cm");
			break;

		case 12:
			UART_put_string(UART_0, "12 cm");
			break;

		case 13:
			UART_put_string(UART_0, "13 cm");
			break;

		case 14:
			UART_put_string(UART_0, "14 cm");
			break;

		case 15:
			UART_put_string(UART_0, "15 cm");
			break;

		case 16:
			UART_put_string(UART_0, "16 cm");
			break;

		case 17:
			UART_put_string(UART_0, "17 cm");
			break;

		case 18:
			UART_put_string(UART_0, "18 cm");
			break;

		case 19:
			UART_put_string(UART_0, "19 cm");
			break;

		case 20:
			UART_put_string(UART_0, "20 cm");
			break;

		case 21:
			UART_put_string(UART_0, "21 cm");
			break;

		case 22:
			UART_put_string(UART_0, "22 cm");
			break;

		case 23:
			UART_put_string(UART_0, "23 cm");
			break;

		case 24:
			UART_put_string(UART_0, "24 cm");
			break;

		case 25:
			UART_put_string(UART_0, "25 cm");
			break;

		case 26:
			UART_put_string(UART_0, "26 cm");
			break;

		case 27:
			UART_put_string(UART_0, "27 cm");
			break;

		case 28:
			UART_put_string(UART_0, "28 cm");
			break;

		case 29:
			UART_put_string(UART_0, "29 cm");
			break;

		case 30:
			UART_put_string(UART_0, "30 cm");
			break;

		case 31:
			UART_put_string(UART_0, "31 cm");
			break;

		case 32:
			UART_put_string(UART_0, "32 cm");
			break;

		case 33:
			UART_put_string(UART_0, "33 cm");
			break;

		case 34:
			UART_put_string(UART_0, "34 cm");
			break;

		case 35:
			UART_put_string(UART_0, "35 cm");
			break;

		case 36:
			UART_put_string(UART_0, "36 cm");
			break;

		case 37:
			UART_put_string(UART_0, "37 cm");
			break;

		case 38:
			UART_put_string(UART_0, "38 cm");
			break;

		case 39:
			UART_put_string(UART_0, "39 cm");
			break;

		case 40:
			UART_put_string(UART_0, "40 cm");
			break;

		case 41:
			UART_put_string(UART_0, "41 cm");
			break;

		case 42:
			UART_put_string(UART_0, "42 cm");
			break;

		case 43:
			UART_put_string(UART_0, "43 cm");
			break;

		case 44:
			UART_put_string(UART_0, "44 cm");
			break;

		case 45:
			UART_put_string(UART_0, "45 cm");
			break;

		case 46:
			UART_put_string(UART_0, "46 cm");
			break;

		case 47:
			UART_put_string(UART_0, "47 cm");
			break;

		case 48:
			UART_put_string(UART_0, "48 cm");
			break;

		case 49:
			UART_put_string(UART_0, "49 cm");
			break;

		case 50:
			UART_put_string(UART_0, "50 cm");
			break;

		case 51:
			UART_put_string(UART_0, "51 cm");
			break;

		case 52:
			UART_put_string(UART_0, "52 cm");
			break;

		case 53:
			UART_put_string(UART_0, "53 cm");
			break;

		case 54:
			UART_put_string(UART_0, "54 cm");
			break;

		case 55:
			UART_put_string(UART_0, "55 cm");
			break;

		case 56:
			UART_put_string(UART_0, "56 cm");
			break;

		case 57:
			UART_put_string(UART_0, "57 cm");
			break;

		case 58:
			UART_put_string(UART_0, "58 cm");
			break;

		case 59:
			UART_put_string(UART_0, "59 cm");
			break;

		case 60:
			UART_put_string(UART_0, "60 cm");
			break;

		case 61:
			UART_put_string(UART_0, "61 cm");
			break;

		case 62:
			UART_put_string(UART_0, "62 cm");
			break;

		case 63:
			UART_put_string(UART_0, "63 cm");
			break;

		case 64:
			UART_put_string(UART_0, "64 cm");
			break;

		case 65:
			UART_put_string(UART_0, "65 cm");
			break;

		case 66:
			UART_put_string(UART_0, "66 cm");
			break;

		case 67:
			UART_put_string(UART_0, "67 cm");
			break;

		case 68:
			UART_put_string(UART_0, "68 cm");
			break;

		case 69:
			UART_put_string(UART_0, "69 cm");
			break;

		case 70:
			UART_put_string(UART_0, "70 cm");
			break;

		case 71:
			UART_put_string(UART_0, "71 cm");
			break;

		case 72:
			UART_put_string(UART_0, "72 cm");
			break;

		case 73:
			UART_put_string(UART_0, "73 cm");
			break;

		case 74:
			UART_put_string(UART_0, "74 cm");
			break;

		case 75:
			UART_put_string(UART_0, "75 cm");
			break;

		case 76:
			UART_put_string(UART_0, "76 cm");
			break;

		case 77:
			UART_put_string(UART_0, "77 cm");
			break;

		case 78:
			UART_put_string(UART_0, "78 cm");
			break;

		case 79:
			UART_put_string(UART_0, "79 cm");
			break;

		case 80:
			UART_put_string(UART_0, "80 cm");
			break;

		case 81:
			UART_put_string(UART_0, "81 cm");
			break;

		case 82:
			UART_put_string(UART_0, "82 cm");
			break;

		case 83:
			UART_put_string(UART_0, "83 cm");
			break;

		case 84:
			UART_put_string(UART_0, "84 cm");
			break;

		case 85:
			UART_put_string(UART_0, "85 cm");
			break;

		case 86:
			UART_put_string(UART_0, "86 cm");
			break;

		case 87:
			UART_put_string(UART_0, "87 cm");
			break;

		case 88:
			UART_put_string(UART_0, "88 cm");
			break;

		case 89:
			UART_put_string(UART_0, "89 cm");
			break;

		case 90:
			UART_put_string(UART_0, "90 cm");
			break;

		case 91:
			UART_put_string(UART_0, "91 cm");
			break;

		case 92:
			UART_put_string(UART_0, "92 cm");
			break;

		case 93:
			UART_put_string(UART_0, "93 cm");
			break;

		case 94:
			UART_put_string(UART_0, "94 cm");
			break;

		case 95:
			UART_put_string(UART_0, "00 cm");
			if (one_time == FALSE) {
				cuenta_metros++;			 // Tolerancia
				one_time = TRUE;
			}
			break;

		case 96:
			UART_put_string(UART_0, "00 cm");
			if (one_time == FALSE) {
				cuenta_metros++;			 // Tolerancia
				one_time = TRUE;
			}
			break;

		case 97:
			UART_put_string(UART_0, "00 cm");
			if (one_time == FALSE) {
				cuenta_metros++;			 // Tolerancia
				one_time = TRUE;
			}
			break;

		case 98:
			UART_put_string(UART_0, "00 cm");
			if (one_time == FALSE) {
				cuenta_metros++;			 // Tolerancia
				one_time = TRUE;
			}
			break;

		case 99:
			UART_put_string(UART_0, "00 cm");
			if (one_time == FALSE) {
				cuenta_metros++;			 // Suma 1 metro a la distancia
				one_time = TRUE;
			}
			break;

		default:
			UART_put_string(UART_0, "N/A");
			break;
	}//end: switch(char_ASCCI)

	if (cuenta_metros == 0) {
		UART_put_string(UART_0, "\033[40;10H");
		UART_put_string(UART_0, "0 metros con ");
	}

	if (cuenta_metros == 1) {
		UART_put_string(UART_0, "\033[40;10H");
		UART_put_string(UART_0, "1 metro  con ");
	}

	if (cuenta_metros == 2) {
		UART_put_string(UART_0, "\033[40;10H");
		UART_put_string(UART_0, "2 metros  con ");
	}

	if (cuenta_metros == 3){
		UART_put_string(UART_0, "\033[40;10H");
		UART_put_string(UART_0, "3 metros  con ");
	}

	if (cuenta_metros == 4){
		UART_put_string(UART_0, "\033[40;10H");
		UART_put_string(UART_0, "4 metros  con ");
	}

	if (cuenta_metros == 5){
		UART_put_string(UART_0, "\033[40;10H");
		UART_put_string(UART_0, "5 metros  con ");
	}
}
