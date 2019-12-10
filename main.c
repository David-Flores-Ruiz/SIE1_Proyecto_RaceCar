/*
 * @file:			Seguidor_de_linea y Control Remoto.c
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
#include "ADC.h"
#include "FlexTimer.h"
#include "memoria.h"
#include "bits.h"
#include "NVIC.h"
#include "GPIO.h"
//#include "RTC.h"
#include "RGB.h"
#include "display.h"	//* 8 x 16 LED matrix */
#include "TeraTerm.h"
#include "Accel_FXOS8700CQ.h"
#include "seguidor_linea.h"
#include "Mediciones.h"

#define SYSTEM_CLOCK_2 (21000000U)
#define BUS_CLOCK (10500000U)
#define BAUD_RATE (9600U)

const adc_config_t g_ADC_config = {
					ADC_0,
					res_8bits,
					bus_clock };
const adc_config_t g_ADC_1_config = {
					ADC_1,
					res_8bits,
					bus_clock };

const FTM_config_t g_FTM0_config = {
					FTM_0,
					FTM_DISABLE_WPDIS,
					FTM_DISABLE_FTMEN,
					0x0FFF,						// MOD = 255d para cuenta de Reinicio
					FTM_PWM_EdgeAligned_High,	// CnSC y CnV asigna a FTM0_CH0, FTM0_CH1, FTM0_CH2
					GPIO_MUX4,
					{GPIO_C, bit_1, bit_2, bit_3} }; 	// PTC1, PTC2, PTC3

extern uint8_t g_key_UART4_CARRO; //** From Bluetooth in Control */

/*
 * PTC1 -> Control de Servomotor
 * PTC2 -> Control de Puente H llanta derecha hacia adelante	//	bit 0 de puente H
 * PTC3 -> Control de Puente H llanta Izquierda hacia adelante	//	bit 3 de puente H
 *
 * PTC0 -> ADC_0 Sensor derecho
 * PTB11-> ADC_1 Sensor izquierdo
 * PTB20-> Sensor de herradura -Medicion de velocidad
 *
 */

int main(void)
{
	//**			RX	-	TX	*/
	//** UART4 -> PTE25 - PTE24 */ 		SLAVE
	//** UART3 -> PTC16 - PTC17 */		MASTER
	//** UART0 -> PTB16 - PTB17 */		TeraTerm

	UART_init (UART_4,  BUS_CLOCK, 	  BD_9600);
	UART_init (UART_3,  BUS_CLOCK, 	  BD_9600);
	//UART_init (UART_0,  SYSTEM_CLOCK_2, BD_115200);

	printf("UART4 is configured");

	RGB_init();
	PIT_init();
	ADC_init(&g_ADC_config);
	ADC_init(&g_ADC_1_config);

	//NVIC_set_basepri_threshold(PRIORITY_10);
	/**Enables the UART 0 interrupt*/
	UART_interrupt_enable(UART_4);
	UART_interrupt_enable(UART_3);
	//UART_interrupt_enable(UART_0);
	/**Enables the UART 0 interrupt in the NVIC*/
	NVIC_enable_interrupt_and_priotity(UART4_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(UART3_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PORTB_IRQ, PRIORITY_10);
	//NVIC_enable_interrupt_and_priotity(UART0_IRQ, PRIORITY_10);
	//NVIC_enable_interrupt_and_priotity(PORTC_IRQ, PRIORITY_10);	// sw2
	//NVIC_enable_interrupt_and_priotity(PORTA_IRQ, PRIORITY_10);	// sw3

	/**Enables interrupts*/
	NVIC_global_enable_interrupts;

	apagar_LED(RGB_OFF);
	encender_LED(YELLOW_ON);	// Prende AMARILLO
	delay(1000);

	/**Configuration function for FlexTimer for PWM: FTM0_ch0_ch1_ch2*/
	FlexTimer_Init(&g_FTM0_config);
	FlexTimer_update_channel_value(0xE0, FTM0_CH0);	//inicializa eje en el centro
	delay(200);

	uint8_t distancia_total = 0;
	uint8_t* ptr_String_distance = 0;

	while (1) {

		//TeraTerm_Echo_UART0();
		TeraTerm_Echo_UART3();
		TeraTerm_Echo_UART4();

		switch (g_key_UART4_CARRO) {
			case '1':
				distancia_total = Mediciones_distancia();	// Siempre esta midiendo la distancia que reccorre
				//Float_to_String(distancia_total);
				//ptr_String_distance = Get_String_Distance();
				UART_put_char(UART_4, distancia_total);		// Se actualizara - ok!
				encender_LED(RED_ON);	// Prende ROJO
				apagar_LED(GREEN_OFF);
				apagar_LED(BLUE_OFF);
				delay(1000);

				break;

			case '2':

				apagar_LED(RED_OFF);	// Prende VERDE
				encender_LED(GREEN_ON);
				apagar_LED(BLUE_OFF);
				Seguidor_linea_init(); // SEGUIDOR DE LINEA
				delay(1000);
				break;

			case '3':

				apagar_LED(RED_OFF);	// Prende AZUL
				apagar_LED(GREEN_OFF);
				encender_LED(BLUE_ON);
				// RECIBE DATOS DEL MAESTRO PARA MOVERSE
				// CONTROL REMOTO
				delay(1000);
				break;

			case 'A':

				FlexTimer_update_channel_value(0xE0,  FTM0_CH0);
				delay(200);
				GPIO_clear_pin(GPIO_B, bit_2);	// OFF
				GPIO_clear_pin(GPIO_B, bit_3);	// OFF
				FlexTimer_update_channel_value(0xA00, FTM0_CH1);
				FlexTimer_update_channel_value(0xA00, FTM0_CH2);
				//delay();
				break;

			case 'F':

				FlexTimer_update_channel_value(0xE0,  FTM0_CH0);
				delay(200);
				GPIO_clear_pin(GPIO_B, bit_2);	// OFF
				GPIO_clear_pin(GPIO_B, bit_3);	// OFF
				FlexTimer_update_channel_value(0x00, FTM0_CH1);
				FlexTimer_update_channel_value(0x00, FTM0_CH2);
				//delay();
				break;

			case 'R':
				FlexTimer_update_channel_value(0xE0,  FTM0_CH0);
				delay(200);
				GPIO_set_pin(GPIO_B, bit_2);	// ON
				GPIO_set_pin(GPIO_B, bit_3);	// ON
				FlexTimer_update_channel_value(0x00, FTM0_CH1);
				FlexTimer_update_channel_value(0x00, FTM0_CH2);
				break;

			case 'D':
				FlexTimer_update_channel_value(0xFF,  FTM0_CH0);
				delay(200);
				GPIO_clear_pin(GPIO_B, bit_2);	// OFF
				GPIO_clear_pin(GPIO_B, bit_3);	// OFF
				FlexTimer_update_channel_value(0xA00, FTM0_CH1);
				FlexTimer_update_channel_value(0xA00, FTM0_CH2);
				//delay();
				break;

			case 'I':
				FlexTimer_update_channel_value(0xB0,  FTM0_CH0);
				delay(200);
				GPIO_clear_pin(GPIO_B, bit_2);	// OFF
				GPIO_clear_pin(GPIO_B, bit_3);	// OFF
				FlexTimer_update_channel_value(0xA00, FTM0_CH1);
				FlexTimer_update_channel_value(0xA00, FTM0_CH2);
				//delay();
				break;

			default:
				//** Aqui no debe entrar :) */
				apagar_LED(RGB_OFF);
				encender_LED(PURPLE_ON);
				delay(1000);
				break;
		}

	}// END WHILE( 1 )

    return 0 ;
}



