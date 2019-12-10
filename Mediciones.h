/*
 * Mediciones.h
 *
 *  Created on: 3 dic 2019
 *  D.F.R. / R.G.P.
*/

#ifndef MEDICIONES_H_
#define MEDICIONES_H_

#include <stdint.h>
#include <stdio.h>
#include "GPIO.h"
#include "MK64F12.h"

typedef float My_float_Medicion;

#define avance_15cm_cada_vuelta 15
uint8_t Mediciones_distancia(void);

#endif /* MEDICIONES_H_ */
