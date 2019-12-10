/*
 * @file:			PROYECTO - CARRITO.c
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 * @contact:		ie717807@iteso.mx
 */

#include "MK64F12.h"
#include <stdint.h>
#include <stdio.h>
#include <string_driver.h>
#include "UART_driver.h"
#include "I2C.h"
#include "memoria.h"
#include "bits.h"
#include "NVIC.h"
#include "GPIO.h"
#include "RGB.h"
#include "display.h"	//* 8 x 16 LED matrix */
#include "TeraTerm.h"
#include "Accel_FXOS8700CQ.h"

#define SYSTEM_CLOCK_2 (21000000U)
#define BUS_CLOCK (10500000U)
#define BAUD_RATE (9600U)

extern uint8_t g_key_UART3_CONTROL; //** From Bluetooth in Control */

int main(void)
{
	//**			RX	-	TX	*/
	//** UART4 -> PTE25 - PTE24 */	-	SLAVE
	//** UART3 -> PTC16 - PTC17 */	-	MASTER
	//** UART0 -> PTB16 - PTB17 */	- 	TERATERM

	UART_init (UART_4,  BUS_CLOCK, 	  BD_9600);
	UART_init (UART_3,  BUS_CLOCK, 	  BD_9600);
	UART_init (UART_0,  SYSTEM_CLOCK_2, BD_115200);

	printf("UART3 and UART0 is configured");

	RGB_init();
	SW_init();

	/**Enables the UART 0 interrupt*/
	UART_interrupt_enable(UART_4);
	UART_interrupt_enable(UART_3);
	UART_interrupt_enable(UART_0);
	/**Enables the UART 0 interrupt in the NVIC*/
	NVIC_enable_interrupt_and_priotity(UART4_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(UART3_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(UART0_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ, PRIORITY_10);	// sw2
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ, PRIORITY_10);	// sw3

	/**Enables interrupts*/
	NVIC_global_enable_interrupts;


	I2C_init_Accel(I2C_0, BUS_CLOCK, BAUD_RATE);
	Accel_Init();	/** Configurado para Inicializar el chip FXOS8700CQ del acelerometro*/

	TeraTerm_Menu();

	uint8_t statusINT_sw2 = 0;
	static int8_t sw2_veces = 0;
	uint8_t one_time = FALSE;
	uint8_t distancia_total = 0;
	uint8_t* ptr_distancia = 0;

	while (1) {

		TeraTerm_Echo_UART0();

		statusINT_sw2 = GPIO_get_irq_status(GPIO_C);

		switch (sw2_veces) {
			case CERO:
				TeraTerm_Echo_UART3();

				encender_LED(RED_ON);	// Prende ROJO
				apagar_LED(GREEN_OFF);
				apagar_LED(BLUE_OFF);
				UART_put_char(UART_3,'1');	// MASTER - dice: STOP
				one_time = FALSE;
				delay(100);

				if (g_key_UART3_CONTROL != '1') {
					UART_put_string(UART_0, "\033[40;25H");
					ASCII_for_Print_UART0();
					delay(100);
				}
				break;

			case UNO:

				apagar_LED(RED_OFF);	// Prende VERDE
				encender_LED(GREEN_ON);
				apagar_LED(BLUE_OFF);
				UART_put_char(UART_3, '2');	// MASTER - dice: SEGUIDOR
				delay(1000);
				break;

			case DOS:

				if (one_time == FALSE) {
					apagar_LED(RED_OFF);	// Prende AZUL
					apagar_LED(GREEN_OFF);
					encender_LED(BLUE_ON);
					UART_put_char(UART_3, '3');	// MASTER - dice: CONTROL
					one_time = TRUE;
					delay(1000);
					break;
				}

				Accel_READ_XYZ();
				FSM_ACELEROMETRO();
				delay(100);
				break;

			default:
				//** Aqui no debe entrar :) */
				delay(1000);
				break;
		}

		if (statusINT_sw2) {
			sw2_veces++;
			GPIO_clear_irq_status(GPIO_C);
		}

		if (sw2_veces == 3) {
			sw2_veces = CERO_N;
		}

	}// END WHILE( 1 )

    return 0 ;
}



