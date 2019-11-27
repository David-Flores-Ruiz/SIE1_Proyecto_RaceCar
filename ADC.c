/*
 * ADC.c
 *
 *  Created on: 27 oct 2019
 *      Author: pacas
 */

#include "ADC.h"
#include "PIT.h"
#include <stdint.h>

void ADC_clk(adc_channel_t channel){
	switch (channel) {
	case ADC_0:
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK; /* Bit_27 - 0x8000000*/
	break;
	case ADC_1:
	SIM->SCGC3 |= SIM_SCGC3_ADC1_MASK; /* Bit_27 - 0x8000000*/
	break;
	}
}

void ADC_conversion_mode(adc_channel_t channel, adc_resolution_SE_t resolution, adc_input_clk_select_t clk_select){
	switch (channel) {
	case ADC_0:
	ADC0->CFG1 |= ADC_CFG1_MODE(resolution);		// Seleccion de modo de 8 bits dato = 00
	ADC0->CFG1 |= ADC_CFG1_ADIV(3);		// Divide el (input clock) / 8
	ADC0->CFG1 |= ADC_CFG1_ADLSMP_MASK; // Long Sample Time
	ADC0->CFG1 |= ADC_CFG1_ADICLK(clk_select);	// 00 - Select Bus Clock
	break;
	case ADC_1:
	ADC1->CFG1 |= ADC_CFG1_MODE(resolution);		// Seleccion de modo de 8 bits dato = 00
	ADC1->CFG1 |= ADC_CFG1_ADIV(3);		// Divide el (input clock) / 8
	ADC1->CFG1 |= ADC_CFG1_ADLSMP_MASK; // Long Sample Time
	ADC1->CFG1 |= ADC_CFG1_ADICLK(clk_select);	// 00 - Select Bus Clock
	break;
	}
}

void ADC_calibration(adc_channel_t channel){
	switch (channel) {
	case ADC_0:
	ADC0->SC3 |= ADC_SC3_AVGE_MASK; // Enable el Hardware Average function of ADC
	ADC0->SC3 |= ADC_SC3_AVGS(1); 	// 01 - Promedia con 8 muestras el ADC result
	break;
	case ADC_1:
	ADC1->SC3 |= ADC_SC3_AVGE_MASK; // Enable el Hardware Average function of ADC
	ADC1->SC3 |= ADC_SC3_AVGS(1); 	// 01 - Promedia con 8 muestras el ADC result
	break;
	}
}

void ADC_input_channel_select(adc_channel_t chanel_select){
	switch (chanel_select) {
	case ADC_0:
	ADC0->SC1[0] = ADC_SC1_ADCH(14);	/* Select PTC_0 como input de ADC */
	break;
	case ADC_1:
	ADC1->SC1[0] = ADC_SC1_ADCH(15);	/* Select PTB_11 como input de ADC */
	break;
	}
}

void ADC_differential_mode_disable(adc_channel_t channel){
	switch (channel) {
	case ADC_0:
	ADC0->SC1[0] &= ~( ADC_SC1_DIFF_MASK); /* Single Ended */
	break;
	case ADC_1:
	ADC1->SC1[0] &= ~( ADC_SC1_DIFF_MASK); /* Single Ended */
	break;
	}
}

void ADC_init(const adc_config_t* config_struct){
	ADC_clk(config_struct->ADC_channel);
	ADC_conversion_mode(config_struct->ADC_channel, config_struct->ADC_resolution, config_struct->ADC_input_clk);
	ADC_calibration(config_struct->ADC_channel);
	ADC_differential_mode_disable(config_struct->ADC_channel);
}

uint8_t ADC_result(adc_channel_t channel){
	 uint8_t adcResult = 0;
	 ADC_input_channel_select(channel);
	 //** Codigo Bloqueante para saber que la conversion fue terminada */
	 while(0 == (ADC0->SC1[0] & ADC_SC1_COCO_MASK));
	 adcResult = (0xFF) & (ADC0->R[0]); // AL leer impia flag de SC1_COCO
	 return (adcResult);
}
uint8_t ADC_result_1(adc_channel_t channel){
	 uint8_t adcResult = 0;
	 ADC_input_channel_select(channel);
	 //** Codigo Bloqueante para saber que la conversion fue terminada */
	 while(0 == (ADC1->SC1[0] & ADC_SC1_COCO_MASK));
	 adcResult = (0xFF) & (ADC1->R[0]); // AL leer impia flag de SC1_COCO
	 return (adcResult);
}

