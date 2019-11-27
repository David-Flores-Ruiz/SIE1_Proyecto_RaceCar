
/**
 * @file    Seguidor_de_linea.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "ADC.h"
#include "MK64F12.h"
#include "FlexTimer.h"
#include "GPIO.h"
#include "bits.h"

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

void delay(uint16_t delay) {
	volatile uint16_t j, i;

	for (j = delay; j > 0; j--) {
		for (i = 0; i < 1000; ++i) {
			__asm("nop");
		}

	}
}
int main(void) {
	GPIO_clock_gating( GPIO_C);	// sw2
	PIT_init();
	ADC_init(&g_ADC_config);
	ADC_init(&g_ADC_1_config);

	/**Configuration function for FlexTimer for PWM: FTM0_ch0_ch1_ch2*/
	FlexTimer_Init(&g_FTM0_config);
	uint8_t sensor_izquierdo=0;
	uint8_t sensor_derecho=0;

    while(1) {
    	sensor_izquierdo=ADC_result_1(ADC_1);
    	sensor_derecho=ADC_result(ADC_0);
    	printf("%d %d\n",sensor_izquierdo,sensor_derecho);

   /* 	FlexTimer_update_channel_value(0xB0, FTM0_CH0);//esta es la funcion que saca valores a traves del puerto probablemente PTC1
    	delay(950);
    	FlexTimer_update_channel_value(0xE0, FTM0_CH0);
    	delay(950);
    	FlexTimer_update_channel_value(0x10F, FTM0_CH0);
    	delay(950);*/
    }
    return 0 ;
}
