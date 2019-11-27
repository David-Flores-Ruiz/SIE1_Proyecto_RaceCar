/*
 * ADC.h
 *
 *  Created on: 27 oct 2019
 *      Author: pacas
 */

#ifndef ADC_H_
#define ADC_H_
#include <MK64F12.h>
#include "stdint.h"
#include "GPIO.h"
#include "PIT.h"

typedef enum {ADC_0,
			  ADC_1,
			  } adc_channel_t;

/*Type for MODE configuration*/
typedef enum {res_8bits, res_12bits, res_10bits, res_16bits} adc_resolution_SE_t;

/*Type for ADICLK configuration*/
typedef enum {bus_clock, alt_clk_2, alt_clk, asin_clk} adc_input_clk_select_t;

/*Type that is used for SPI configuration, It contains all the information needed for a SPI module*/
typedef struct {
	adc_channel_t ADC_channel;
	adc_resolution_SE_t ADC_resolution;
	adc_input_clk_select_t ADC_input_clk;
} adc_config_t;

//* It enable the clock module of the ADC by modifying the SIM_SCGC6 bits */
void ADC_clk(adc_channel_t channel);

//** Modo de operacion, fuente de reloj, Divisor del Reloj y Low Power */
void ADC_conversion_mode(adc_channel_t channel, adc_resolution_SE_t resolution, adc_input_clk_select_t clk_select);

//** Enable el Promediador por Hardware */
void ADC_calibration(adc_channel_t channel);

void ADC_input_channel_select(adc_channel_t chanel_select);

//** Como single ended */
void ADC_differential_mode_disable(adc_channel_t channel);

/*It configures the ADC for Read Analog Values of the POTENCIOMETER, this function as arguments receives a pointer to a constant structure where are all
 * the configuration parameters*/
void ADC_init(const adc_config_t* config_struct);


uint8_t ADC_result(adc_channel_t channel);
uint8_t ADC_result_1(adc_channel_t channel);




#endif /* ADC_H_ */
