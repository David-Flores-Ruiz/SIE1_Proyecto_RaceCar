/*
 * FSM_submenu_matriz_print.h
 *
 *  Created on: 16 nov 2019
 *      Author: pacas
 */

#ifndef SUBMENU_MATRIZ_H_
#define SUBMENU_MATRIZ_H_

#include "MK64F12.h"
#include "bits.h"
#include "display.h"


typedef enum {
	h0_m0,
	h0_m1,
	h0_m2,
	h0_m3,
	h0_m4,
	h0_m5,
	h0_m6,
	h0_m7,
	h0_m8,
	h0_m9,

	h0_m10,
	h0_m11,
	h0_m12,
	h0_m13,
	h0_m14,
	h0_m15,
	h0_m16,
	h0_m17,
	h0_m18,
	h0_m19,

	h0_m20,
	h0_m21,
	h0_m22,
	h0_m23,
	h0_m24,
	h0_m25,
	h0_m26,
	h0_m27,
	h0_m28,
	h0_m29,

	h0_m30,
	h0_m31,
	h0_m32,
	h0_m33,
	h0_m34,
	h0_m35,
	h0_m36,
	h0_m37,
	h0_m38,
	h0_m39,

	h0_m40,
	h0_m41,
	h0_m42,
	h0_m43,
	h0_m44,
	h0_m45,
	h0_m46,
	h0_m47,
	h0_m48,
	h0_m49,

	h0_m50,
	h0_m51,
	h0_m52,
	h0_m53,
	h0_m54,
	h0_m55,
	h0_m56,
	h0_m57,
	h0_m58,
	h0_m59,
} minutos;

typedef enum {
	h00_m0,
	h1_m0,
	h2_m0,
	h3_m0,
	h4_m0,
	h5_m0,
	h6_m0,
	h7_m0,
	h8_m0,
	h9_m0,
	h10_m0,
	h11_m0,

	h12_m0,
	h13_m0,
	h14_m0,
	h15_m0,
	h16_m0,
	h17_m0,
	h18_m0,
	h19_m0,
	h20_m0,
	h21_m0,
	h22_m0,
	h23_m0,
} horas;


void Submenu_matriz_horas(uint8_t minutos);
void Submenu_matriz_minutos(uint8_t current_state);
void Submenu_matriz_horas_minutos(uint8_t current_state_minutos, uint8_t current_state_horas);


#endif /* SUBMENU_MATRIZ_H_ */
