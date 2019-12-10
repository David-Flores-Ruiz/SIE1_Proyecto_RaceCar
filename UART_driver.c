/*
 * @file:			UART.c
 * @company:			ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#include "UART_driver.h"

 uart_mail_box_t g_mail_box_uart_0;
 uart_mail_box_t g_mail_box_uart_3;
 uart_mail_box_t g_mail_box_uart_4;

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

