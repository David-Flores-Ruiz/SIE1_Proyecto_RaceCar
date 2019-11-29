
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
#include "seguidor_linea.h"
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


/*
 * PTC1 -> Control de Servomotor
 * PTC2 -> Control de Puente H
 *
 * PTC0 -> ADC_0 Sensor derecho
 * PTB11-> ADC_1 Sensor izquierdo
 *
 */
int main(void) {
	GPIO_clock_gating( GPIO_C);	// sw2
	PIT_init();
	ADC_init(&g_ADC_config);
	ADC_init(&g_ADC_1_config);

	/**Configuration function for FlexTimer for PWM: FTM0_ch0_ch1_ch2*/
	FlexTimer_Init(&g_FTM0_config);

	FlexTimer_update_channel_value(0xE0, FTM0_CH0);//inicializa eje en el centro
	delay(200);
    while(1) {
    	Seguidor_linea_init();
    }
    return 0 ;
}

