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
#include "stdio.h"

void Seguidor_linea_init(void){
	uint8_t sensor_izquierdo=0;
	uint8_t sensor_derecho=0;
	FlexTimer_update_channel_value(0x5B0, FTM0_CH1);//motor puente H llanta izquierda cable naranja
	FlexTimer_update_channel_value(0x5B0, FTM0_CH2);//motor puente H llanta derecha cable blanco
	sensor_derecho = ADC_result_1(ADC_1);
	sensor_izquierdo = ADC_result(ADC_0);

	printf("%d %d\n", sensor_izquierdo, sensor_derecho);

	if (sensor_derecho <= 80) {
		while (1) {
			FlexTimer_update_channel_value(0xB0, FTM0_CH0); //Vuelta Izquierda
			FlexTimer_update_channel_value(0x5B0, FTM0_CH1); //motor puente H llanta izquierda cable naranja
			FlexTimer_update_channel_value(0x5B0, FTM0_CH2); //motor puente H llanta derecha cable blanco
			sensor_derecho = ADC_result_1(ADC_1);
			if (sensor_derecho >= 80) {
				break;
			}
		}
	} else if (sensor_izquierdo <= 80) {
		while (1) {
		FlexTimer_update_channel_value(0xFF, FTM0_CH0);		//Vuelta Derecha
		FlexTimer_update_channel_value(0x5B0, FTM0_CH1);	//motor puente H llanta izquierda cable naranja
		FlexTimer_update_channel_value(0x5B0, FTM0_CH2);//motor puente H llanta derecha cable blanco
		sensor_izquierdo = ADC_result(ADC_0);
		if (sensor_izquierdo >= 80) {
			break;
		}
	}
		//FlexTimer_update_channel_value(0xE0, FTM0_CH0);
		//delay(550);
	}else {
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
