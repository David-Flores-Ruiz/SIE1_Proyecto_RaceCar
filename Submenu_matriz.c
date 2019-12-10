/*
 * FSM_submenu_matriz.c
 *
 *  Created on: 16 nov 2019
 *      Author:
 */

#include "Submenu_matriz.h"

const uint8_t letra_A[] = { 0x00, 0x3F, 0x7F, 0xCC, 0xCC, 0x7F, 0x3F, 0x00 };
const uint8_t letra_B[] = { 0x00, 0xff, 0xff, 0xc9, 0xc9, 0x49, 0x36, 0x00 };
const uint8_t letra_C[] = { 0x00, 0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0x00 };
const uint8_t letra_D[] = { 0x00, 0xff, 0xff, 0xc3, 0xc3, 0x7e, 0x3c, 0x00 };
const uint8_t letra_E[] = { 0x00, 0xFF, 0xFF, 0xDB, 0xDB, 0xC3, 0xC3, 0x00 };
const uint8_t letra_F[] = { 0x00, 0xff, 0xff, 0x33, 0x33, 0x03, 0x03, 0x00 };
const uint8_t letra_G[] = { 0x00, 0xff, 0xff, 0xdb, 0xdb, 0xfb, 0xfb, 0x00 };
const uint8_t letra_H[] = { 0x00, 0xff, 0xff, 0x18, 0x18, 0xff, 0xff, 0x00 };
const uint8_t letra_I[] = { 0x00, 0xC3, 0xC3, 0xFF, 0xFF, 0xC3, 0xC3, 0x00 };
const uint8_t letra_J[] = { 0x00, 0x03, 0x7f, 0xff, 0x83, 0xc3, 0x63, 0x00 };
const uint8_t letra_K[] = { 0x00, 0xff, 0xff, 0x18, 0x3c, 0x66, 0xc3, 0x00 };
const uint8_t letra_L[] = { 0x00, 0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0x00 };
const uint8_t letra_M[] = { 0x00, 0xff, 0xfc, 0x08, 0x08, 0xfc, 0xff, 0x00 };
const uint8_t letra_N[] = { 0x00, 0xff, 0x06, 0x0c, 0x18, 0x30, 0xff, 0x00 };
const uint8_t letra_O[] = { 0x00, 0xFF, 0xFF, 0xC3, 0xC3, 0xFF, 0xFF, 0x00 };
const uint8_t letra_P[] = { 0x00, 0xff, 0xff, 0x09, 0x09, 0x09, 0x0f, 0x00 };
const uint8_t letra_Q[] = { 0x00, 0x7f, 0x41, 0x41, 0x71, 0x71, 0xff, 0xc0 };
const uint8_t letra_R[] = { 0x00, 0xff, 0xff, 0x19, 0x39, 0x69, 0xcf, 0x00 };
const uint8_t letra_S[] = { 0x00, 0xdf, 0xdf, 0xdb, 0xdb, 0xdb, 0xfb, 0x00 };
const uint8_t letra_T[] = { 0x00, 0xC0, 0xC0, 0xFF, 0xFF, 0xC0, 0xC0, 0x00 };
const uint8_t letra_U[] = { 0x00, 0xff, 0xff, 0xc0, 0xc0, 0xff, 0xff, 0x00 };
const uint8_t letra_V[] = { 0x00, 0x3f, 0x7f, 0xc0, 0xc0, 0xff, 0x3f, 0x00 };
const uint8_t letra_W[] = { 0x00, 0x7f, 0xe0, 0xf0, 0xf0, 0xe0, 0x7f, 0x00 };
const uint8_t letra_X[] = { 0x00, 0xe3, 0x36, 0x1c, 0x1c, 0x36, 0xe3, 0x00 };
const uint8_t letra_Y[] = { 0x00, 0x07, 0x0c, 0xf8, 0xf8, 0x0c, 0x07, 0x00 };
const uint8_t letra_Z[] = { 0x00, 0xfb, 0xfb, 0xdb, 0xdb, 0xdf, 0xdf, 0x00 };

const uint8_t minutos_00[] = { 0x0, 0xff, 0x81, 0xff, 0x0, 0xff, 0x81, 0xff };
const uint8_t minutos_01[] = { 0x0, 0xff, 0x81, 0xff, 0x0, 0xff, 0x0 , 0x0  };
const uint8_t minutos_02[] = { 0x0, 0xff, 0x81, 0xff, 0x0, 0x8f, 0x89, 0xf9 };
const uint8_t minutos_03[] = { 0x0, 0xff, 0x81, 0xff, 0x0, 0x89, 0x89, 0xff };
const uint8_t minutos_04[] = { 0x0, 0xff, 0x81, 0xff, 0x0, 0xf0, 0x10, 0xff };
const uint8_t minutos_05[] = { 0x0, 0xff, 0x81, 0xff, 0x0, 0xf9, 0x89, 0x8f };
const uint8_t minutos_06[] = { 0x0, 0xff, 0x81, 0xff, 0x0, 0xff, 0x89, 0xcf };
const uint8_t minutos_07[] = { 0x0, 0xff, 0x81, 0xff, 0x0, 0x80, 0x80, 0xff };
const uint8_t minutos_08[] = { 0x0, 0xff, 0x81, 0xff, 0x0, 0xff, 0x89, 0xff };
const uint8_t minutos_09[] = { 0x0, 0xff, 0x81, 0xff, 0x0, 0xf1, 0x91, 0xff };

const uint8_t minutos_10[] = { 0x0, 0xff, 0x0, 0x0, 0x0, 0xff, 0x81, 0xff };
const uint8_t minutos_11[] = { 0x0, 0xff, 0x0, 0x0, 0x0, 0xff, 0x0,  0x0  };
const uint8_t minutos_12[] = { 0x0, 0xff, 0x0, 0x0, 0x0, 0x8f, 0x89, 0xf9 };
const uint8_t minutos_13[] = { 0x0, 0xff, 0x0, 0x0, 0x0, 0x89, 0x89, 0xff };
const uint8_t minutos_14[] = { 0x0, 0xff, 0x0, 0x0, 0x0, 0xf0, 0x10, 0xff };
const uint8_t minutos_15[] = { 0x0, 0xff, 0x0, 0x0, 0x0, 0xf9, 0x89, 0x8f };
const uint8_t minutos_16[] = { 0x0, 0xff, 0x0, 0x0, 0x0, 0xff, 0x89, 0xcf };
const uint8_t minutos_17[] = { 0x0, 0xff, 0x0, 0x0, 0x0, 0x80, 0x80, 0xff };
const uint8_t minutos_18[] = { 0x0, 0xff, 0x0, 0x0, 0x0, 0xff, 0x89, 0xff };
const uint8_t minutos_19[] = { 0x0, 0xff, 0x0, 0x0, 0x0, 0xf1, 0x91, 0xff };

const uint8_t minutos_20[] = { 0x0, 0x8f, 0x89, 0xf9, 0x0, 0xff, 0x81, 0xff };
const uint8_t minutos_21[] = { 0x0, 0x8f, 0x89, 0xf9, 0x0, 0xff, 0x00, 0x00 };
const uint8_t minutos_22[] = { 0x0, 0x8f, 0x89, 0xf9, 0x0, 0x8f, 0x89, 0xf9 };
const uint8_t minutos_23[] = { 0x0, 0x8f, 0x89, 0xf9, 0x0, 0x89, 0x89, 0xff };
const uint8_t minutos_24[] = { 0x0, 0x8f, 0x89, 0xf9, 0x0, 0xf0, 0x10, 0xff };
const uint8_t minutos_25[] = { 0x0, 0x8f, 0x89, 0xf9, 0x0, 0xf9, 0x89, 0x8f };
const uint8_t minutos_26[] = { 0x0, 0x8f, 0x89, 0xf9, 0x0, 0xff, 0x89, 0xcf };
const uint8_t minutos_27[] = { 0x0, 0x8f, 0x89, 0xf9, 0x0, 0x80, 0x80, 0xff };
const uint8_t minutos_28[] = { 0x0, 0x8f, 0x89, 0xf9, 0x0, 0xff, 0x89, 0xff };
const uint8_t minutos_29[] = { 0x0, 0x8f, 0x89, 0xf9, 0x0, 0xf1, 0x91, 0xff };

const uint8_t minutos_30[] = { 0x0, 0x89, 0x89, 0xff, 0x0, 0xff, 0x81, 0xff };
const uint8_t minutos_31[] = { 0x0, 0x89, 0x89, 0xff, 0x0, 0xff, 0x00, 0x00 };
const uint8_t minutos_32[] = { 0x0, 0x89, 0x89, 0xff, 0x0, 0x8f, 0x89, 0xf9 };
const uint8_t minutos_33[] = { 0x0, 0x89, 0x89, 0xff, 0x0, 0x89, 0x89, 0xff };
const uint8_t minutos_34[] = { 0x0, 0x89, 0x89, 0xff, 0x0, 0xf0, 0x10, 0xff };
const uint8_t minutos_35[] = { 0x0, 0x89, 0x89, 0xff, 0x0, 0xf9, 0x89, 0x8f };
const uint8_t minutos_36[] = { 0x0, 0x89, 0x89, 0xff, 0x0, 0xff, 0x89, 0xcf };
const uint8_t minutos_37[] = { 0x0, 0x89, 0x89, 0xff, 0x0, 0x80, 0x80, 0xff };
const uint8_t minutos_38[] = { 0x0, 0x89, 0x89, 0xff, 0x0, 0xff, 0x89, 0xff };
const uint8_t minutos_39[] = { 0x0, 0x89, 0x89, 0xff, 0x0, 0xf1, 0x91, 0xff };

const uint8_t minutos_40[] = { 0x0, 0xf0, 0x10, 0xff, 0x0, 0xff, 0x81, 0xff };
const uint8_t minutos_41[] = { 0x0, 0xf0, 0x10, 0xff, 0x0, 0xff, 0x00, 0x00 };
const uint8_t minutos_42[] = { 0x0, 0xf0, 0x10, 0xff, 0x0, 0x8f, 0x89, 0xf9 };
const uint8_t minutos_43[] = { 0x0, 0xf0, 0x10, 0xff, 0x0, 0x89, 0x89, 0xff };
const uint8_t minutos_44[] = { 0x0, 0xf0, 0x10, 0xff, 0x0, 0xf0, 0x10, 0xff };
const uint8_t minutos_45[] = { 0x0, 0xf0, 0x10, 0xff, 0x0, 0xf9, 0x89, 0x8f };
const uint8_t minutos_46[] = { 0x0, 0xf0, 0x10, 0xff, 0x0, 0xff, 0x89, 0xcf };
const uint8_t minutos_47[] = { 0x0, 0xf0, 0x10, 0xff, 0x0, 0x80, 0x80, 0xff };
const uint8_t minutos_48[] = { 0x0, 0xf0, 0x10, 0xff, 0x0, 0xff, 0x89, 0xff };
const uint8_t minutos_49[] = { 0x0, 0xf0, 0x10, 0xff, 0x0, 0xf1, 0x91, 0xff };

const uint8_t minutos_50[] = { 0x0, 0xf9, 0x89, 0x8f, 0x0, 0xff, 0x81, 0xff };
const uint8_t minutos_51[] = { 0x0, 0xf9, 0x89, 0x8f, 0x0, 0xff, 0x00, 0x00 };
const uint8_t minutos_52[] = { 0x0, 0xf9, 0x89, 0x8f, 0x0, 0x8f, 0x89, 0xf9 };
const uint8_t minutos_53[] = { 0x0, 0xf9, 0x89, 0x8f, 0x0, 0x89, 0x89, 0xff };
const uint8_t minutos_54[] = { 0x0, 0xf9, 0x89, 0x8f, 0x0, 0xf0, 0x10, 0xff };
const uint8_t minutos_55[] = { 0x0, 0xf9, 0x89, 0x8f, 0x0, 0xf9, 0x89, 0x8f };
const uint8_t minutos_56[] = { 0x0, 0xf9, 0x89, 0x8f, 0x0, 0xff, 0x89, 0xcf };
const uint8_t minutos_57[] = { 0x0, 0xf9, 0x89, 0x8f, 0x0, 0x80, 0x80, 0xff };
const uint8_t minutos_58[] = { 0x0, 0xf9, 0x89, 0x8f, 0x0, 0xff, 0x89, 0xff };
const uint8_t minutos_59[] = { 0x0, 0xf9, 0x89, 0x8f, 0x0, 0xf1, 0x91, 0xff };

void Submenu_matriz_horas(uint8_t current_state){
	switch (current_state)
	{
		case h00_m0:
			display_instruccion_debug_horas(minutos_00);
			break;

		case h1_m0:
			display_instruccion_debug_horas(minutos_01);
			break;

		case h2_m0:
			display_instruccion_debug_horas(minutos_02);
			break;

		case h3_m0:
			display_instruccion_debug_horas(minutos_03);
			break;

		case h4_m0:
			display_instruccion_debug_horas(minutos_04);
			break;

		case h5_m0:
			display_instruccion_debug_horas(minutos_05);
			break;

		case h6_m0:
			display_instruccion_debug_horas(minutos_06);
			break;

		case h7_m0:
			display_instruccion_debug_horas(minutos_07);
			break;

		case h8_m0:
			display_instruccion_debug_horas(minutos_08);
			break;

		case h9_m0:
			display_instruccion_debug_horas(minutos_09);
			break;

		case h10_m0:
			display_instruccion_debug_horas(minutos_10);
			break;

		case h11_m0:
			display_instruccion_debug_horas(minutos_11);
			break;

		case h12_m0:
			display_instruccion_debug_horas(minutos_12);
			break;

		case h13_m0:
			display_instruccion_debug_horas(minutos_13);
			break;

		case h14_m0:
			display_instruccion_debug_horas(minutos_14);
			break;

		case h15_m0:
			display_instruccion_debug_horas(minutos_15);
			break;

		case h16_m0:
			display_instruccion_debug_horas(minutos_16);
			break;

		case h17_m0:
			display_instruccion_debug_horas(minutos_17);
			break;

		case h18_m0:
			display_instruccion_debug_horas(minutos_18);
			break;

		case h19_m0:
			display_instruccion_debug_horas(minutos_19);
			break;

		case h20_m0:
			display_instruccion_debug_horas(minutos_20);
			break;

		case h21_m0:
			display_instruccion_debug_horas(minutos_21);
			break;

		case h22_m0:
			display_instruccion_debug_horas(minutos_22);
			break;

		case h23_m0:
			display_instruccion_debug_horas(minutos_23);
			break;

	}
}

void Submenu_matriz_minutos(uint8_t current_state) {
	switch (current_state)
	{
		case h0_m0:
			display_instruccion_debug_minutos(minutos_00);
			break;
		case h0_m1:
			display_instruccion_debug_minutos(minutos_01);
			break;
		case h0_m2:
			display_instruccion_debug_minutos(minutos_02);
			break;
		case h0_m3:
			display_instruccion_debug_minutos(minutos_03);
			break;
		case h0_m4:
			display_instruccion_debug_minutos(minutos_04);
			break;
		case h0_m5:
			display_instruccion_debug_minutos(minutos_05);
			break;
		case h0_m6:
			display_instruccion_debug_minutos(minutos_06);
			break;
		case h0_m7:
			display_instruccion_debug_minutos(minutos_07);
			break;
		case h0_m8:
			display_instruccion_debug_minutos(minutos_08);
			break;
		case h0_m9:
			display_instruccion_debug_minutos(minutos_09);
			break;
		case h0_m10:
			display_instruccion_debug_minutos(minutos_10);
			break;
		case h0_m11:
			display_instruccion_debug_minutos(minutos_11);
			break;
		case h0_m12:
			display_instruccion_debug_minutos(minutos_12);
			break;
		case h0_m13:
			display_instruccion_debug_minutos(minutos_13);
			break;
		case h0_m14:
			display_instruccion_debug_minutos(minutos_14);
			break;
		case h0_m15:
			display_instruccion_debug_minutos(minutos_15);
			break;
		case h0_m16:
			display_instruccion_debug_minutos(minutos_16);
			break;
		case h0_m17:
			display_instruccion_debug_minutos(minutos_17);
			break;
		case h0_m18:
			display_instruccion_debug_minutos(minutos_18);
			break;
		case h0_m19:
			display_instruccion_debug_minutos(minutos_19);
			break;
		case h0_m20:
			display_instruccion_debug_minutos(minutos_20);
			break;
		case h0_m21:
			display_instruccion_debug_minutos(minutos_21);
			break;
		case h0_m22:
			display_instruccion_debug_minutos(minutos_22);
			break;
		case h0_m23:
			display_instruccion_debug_minutos(minutos_23);
			break;
		case h0_m24:
			display_instruccion_debug_minutos(minutos_24);
			break;
		case h0_m25:
			display_instruccion_debug_minutos(minutos_25);
			break;
		case h0_m26:
			display_instruccion_debug_minutos(minutos_26);
			break;
		case h0_m27:
			display_instruccion_debug_minutos(minutos_27);
			break;
		case h0_m28:
			display_instruccion_debug_minutos(minutos_28);
			break;
		case h0_m29:
			display_instruccion_debug_minutos(minutos_29);
			break;
		case h0_m30:
			display_instruccion_debug_minutos(minutos_30);
			break;
		case h0_m31:
			display_instruccion_debug_minutos(minutos_31);
			break;
		case h0_m32:
			display_instruccion_debug_minutos(minutos_32);
			break;
		case h0_m33:
			display_instruccion_debug_minutos(minutos_33);
			break;
		case h0_m34:
			display_instruccion_debug_minutos(minutos_34);
			break;
		case h0_m35:
			display_instruccion_debug_minutos(minutos_35);
			break;
		case h0_m36:
			display_instruccion_debug_minutos(minutos_36);
			break;
		case h0_m37:
			display_instruccion_debug_minutos(minutos_37);
			break;
		case h0_m38:
			display_instruccion_debug_minutos(minutos_38);
			break;
		case h0_m39:
			display_instruccion_debug_minutos(minutos_39);
			break;
		case h0_m40:
			display_instruccion_debug_minutos(minutos_40);
			break;
		case h0_m41:
			display_instruccion_debug_minutos(minutos_41);
			break;
		case h0_m42:
			display_instruccion_debug_minutos(minutos_42);
			break;
		case h0_m43:
			display_instruccion_debug_minutos(minutos_43);
			break;
		case h0_m44:
			display_instruccion_debug_minutos(minutos_44);
			break;
		case h0_m45:
			display_instruccion_debug_minutos(minutos_45);
			break;
		case h0_m46:
			display_instruccion_debug_minutos(minutos_46);
			break;
		case h0_m47:
			display_instruccion_debug_minutos(minutos_47);
			break;
		case h0_m48:
			display_instruccion_debug_minutos(minutos_48);
			break;
		case h0_m49:
			display_instruccion_debug_minutos(minutos_49);
			break;
		case h0_m50:
			display_instruccion_debug_minutos(minutos_50);
			break;
		case h0_m51:
			display_instruccion_debug_minutos(minutos_51);
			break;
		case h0_m52:
			display_instruccion_debug_minutos(minutos_52);
			break;
		case h0_m53:
			display_instruccion_debug_minutos(minutos_53);
			break;
		case h0_m54:
			display_instruccion_debug_minutos(minutos_54);
			break;
		case h0_m55:
			display_instruccion_debug_minutos(minutos_55);
			break;
		case h0_m56:
			display_instruccion_debug_minutos(minutos_56);
			break;
		case h0_m57:
			display_instruccion_debug_minutos(minutos_57);
			break;
		case h0_m58:
			display_instruccion_debug_minutos(minutos_58);
			break;
		case h0_m59:
			display_instruccion_debug_minutos(minutos_59);
			break;

	}
}

void Submenu_matriz_horas_minutos(uint8_t current_state_horas, uint8_t current_state_minutos) {
	Submenu_matriz_minutos(current_state_minutos);
	Submenu_matriz_horas(current_state_horas);
}
