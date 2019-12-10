/*
 * @file:			Mediciones.c
 * @company:			ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#include "Mediciones.h"

uint8_t Mediciones_distancia(void) {
	uint8_t distancia = 0;
	distancia = GPIO_get_PORT_distancia_hoyo() * .468;
	printf("distancia %dcm\n", distancia);
	return (distancia);
}

