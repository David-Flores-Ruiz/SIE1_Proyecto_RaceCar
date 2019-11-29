/*
 * seguidor_linea.c
 *
 *  Created on: 28 nov 2019
 *      Author: pacas
 */
#include "ADC.h"
#include "MK64F12.h"
#include "FlexTimer.h"
#include "GPIO.h"
#include "bits.h"
void Seguidor_linea_init(void){
	uint8_t sensor_izquierdo=0;
		uint8_t sensor_derecho=0;
	FlexTimer_update_channel_value(0xF00, FTM0_CH1);//motor puente H
	sensor_derecho = ADC_result_1(ADC_1);
	sensor_izquierdo = ADC_result(ADC_0);

	printf("%d %d\n", sensor_izquierdo, sensor_derecho);

	if (sensor_derecho <= 80) {
		FlexTimer_update_channel_value(0xB0, FTM0_CH0);
		delay(200);
		//FlexTimer_update_channel_value(0xE0, FTM0_CH0);
		//delay(550);
	}else if (sensor_izquierdo <= 80) {
		FlexTimer_update_channel_value(0xFF, FTM0_CH0);
		delay(200);
		//FlexTimer_update_channel_value(0xE0, FTM0_CH0);
		//delay(550);
	}
	else {
		FlexTimer_update_channel_value(0xE0, FTM0_CH0);
		delay(250);
	}

/*    	FlexTimer_update_channel_value(0xA0, FTM0_CH0);//esta es la funcion que saca valores a traves del puerto probablemente PTC1
	delay(950);
	FlexTimer_update_channel_value(0xE0, FTM0_CH0);
	delay(950);
	FlexTimer_update_channel_value(0x10F, FTM0_CH0);
	delay(950);*/
}
void delay(uint16_t delay) {
	volatile uint16_t j, i;

	for (j = delay; j > 0; j--) {
		for (i = 0; i < 1000; ++i) {
			__asm("nop");
		}

	}
}
