/*
 * @file:			TeraTerm.c
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#include "TeraTerm.h"

#define ARRAY_mod_hours   &modified_hours[0]	//Direccion del arreglo de Horas
#define ARRAY_mod_minutes &modified_minutes[0]	//Direccion del arreglo de Minutos
#define ARRAY_mod_seconds &modified_seconds[0]	//Direccion del arreglo de Segundos

#define ARRAY_mod_Date  &modified_Date[0]	//Direccion del arreglo de Dia
#define ARRAY_mod_Month &modified_Month[0]	//Direccion del arreglo de Mes
#define ARRAY_mod_Year  &modified_Year[0]	//Direccion del arreglo de Anio

#define ARRAY_mensaje_1 &mensaje_1[0]
#define ARRAY_mensaje_2 &mensaje_2[0]
#define ARRAY_mensaje_3 &mensaje_3[0]
#define ARRAY_mensaje_4 &mensaje_4[0]
#define ARRAY_mensaje_5 &mensaje_5[0]

static FSM_flags_t g_FSM_status_flags = {0};	//** Banderas de activacion de cada submenu */

/**This is mail box to received the information from the serial port*/
extern uart_mail_box_t g_mail_box_uart_0;
extern uart_mail_box_t g_mail_box_uart_3;
extern uart_mail_box_t g_mail_box_uart_4;

uint8_t g_key_UART0_PC      = '\0'; //** From TeraTerm in PC */
uint8_t g_key_UART3_CONTROL   = '\0'; //** From Bluetooth in RaceCar */
uint8_t g_key_UART4_CARRO = '\0'; //** From Bluetooth in Control */

uint8_t g_new_key_UART0 = FALSE;
static uint8_t UART0_key = '\0';	//** Cuenta el numero de presiones dentro de cada Submenu*/
static uint8_t i_sub1 = 0;	//** Indice de array en submenu 1*/
static uint8_t i_sub2 = 0;	//** Indice de array en submenu 2*/
static uint8_t i_sub5 = 0;	//** Indice de array en submenu 5*/
static uint8_t i_sub6 = 0;	//** Indice de array en submenu 6*/
static uint8_t i_sub7 = 0;	//** Indice de array en submenu 7*/

static uint8_t instruction_1[] = "\033[0;35;43m";

static uint8_t numero_mensaje[3] = "0";
static uint8_t numero_msjMemoria[3] = "0";
static uint8_t mensaje_1[31] = "1) ";
static uint8_t mensaje_2[31] = "2) ";
static uint8_t mensaje_3[31] = "3) ";
static uint8_t mensaje_4[31] = "4) ";
static uint8_t mensaje_5[31] = "5) ";

static uint8_t terminal_1[] = "Terminal 1: ";
static uint8_t terminal_2[] = "Terminal 2: ";

//** String that will be printed in the TeraTerm*/
uint8_t string_hours[4]    = "HH:"; /*! Hours  */
uint8_t string_minutes[4]  = "MM:"; /*! Minutes*/
uint8_t string_seconds[3] = "SS "; /*! Seconds*/

uint8_t string_Date[4]  = "DD/"; /*! Day  */
uint8_t string_Month[4] = "MM/"; /*! Month*/
uint8_t string_Year[3]  = "AA "; /*! Year */

//** Propose to modify the TIME or the DATE actual*/
//** In the beginning will start in the last day of this year (2019)*/
uint8_t modified_hours[4] 	= {'2', '3'};
uint8_t modified_minutes[4] = {'5', '9'};
uint8_t modified_seconds[3] = {'0', '0'};

uint8_t modified_Date[4]  = {'3', '1'};
uint8_t modified_Month[4] = {'1', '2'};
uint8_t modified_Year[3]  = {'1', '9'};

uint8_t matrix_ON[3] 	= {'n', 'o'};

void TeraTerm_Menu(void) {
	/**The following sentences send strings to PC using the UART_put_string function. Also, the string
	 * is coded with terminal code*/
	/**The following sentences send strings to PC using the UART_put_string function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_put_string(UART_0,&instruction_1);
	/*VT100 command for clearing the screen*/
	UART_put_string(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_put_string(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(UART_0,"\033[10;10H");
	UART_put_string(UART_0, "SISTEMAS EMBEBIDOS I\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(UART_0,"\033[11;10H");
	UART_put_string(UART_0, "    ITESO\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(UART_0,"\033[14;10H");
}

void TeraTerm_Echo_UART0(void) {

	/** Modulo de codice que hace la funcion de echo para recibir de
	 *  la terminal de TeraTerm que entra cuando escribes y envia el
	 *  valor ASCII de la tecla que presionaste en TeraTerm */

	if (g_mail_box_uart_0.flag) {
		/**Sends to the PCA the received data in the mailbox*/
		UART_put_char(UART_0, g_mail_box_uart_0.mailBox);

		g_key_UART0_PC = g_mail_box_uart_0.mailBox; //** GET THE ASCII PRESSED */

		/**clear the reception flag*/
		g_mail_box_uart_0.flag = 0;
	}
}

void TeraTerm_Echo_UART3(void) {

	/** Modulo de codice que hace la funcion de echo para recibir de
	 *  la terminal de TeraTerm que entra cuando escribes y envia el
	 *  valor ASCII de la tecla que presionaste en TeraTerm */

	if (g_mail_box_uart_3.flag) {
		/**Sends to the PCA the received data in the mailbox*/
		UART_put_char(UART_3, g_mail_box_uart_3.mailBox);

		g_key_UART3_CONTROL = g_mail_box_uart_3.mailBox; //** GET THE ASCII PRESSED */

		/**clear the reception flag*/
		g_mail_box_uart_3.flag = 0;
	}
}

void TeraTerm_Echo_UART4(void) {

	/** Modulo de codice que hace la funcion de echo para recibir de
	 *  la terminal de TeraTerm que entra cuando escribes y envia el
	 *  valor ASCII de la tecla que presionaste en TeraTerm */

	if (g_mail_box_uart_4.flag) {
		/**Sends to the PCA the received data in the mailbox*/
		UART_put_char(UART_4, g_mail_box_uart_4.mailBox);

		g_key_UART4_CARRO = g_mail_box_uart_4.mailBox; //** GET THE ASCII PRESSED */

		/**clear the reception flag*/
		g_mail_box_uart_4.flag = 0;
	}
}

void TeraTerm_MENU_FSM(void) {

	static State_t current_state = MENU_INICIAL; //** Estado Inicial del Sistema */

	RTC_BCD_TIME_Registers();	//** Actualiza string de los registros del RTC*/
	RTC_BCD_DATE_Registers();	//** Actualiza string de los registros del RTC*/

	TeraTerm_Echo_UART0();	//** HERE I GET THE ASCII THAT WAS PRESSED */

	UART0_key = g_key_UART0_PC; // Actualizo mi current State segun la tecla presionada

	delay(500);	//** Evitar demasiado refresh en TeraTerm mejora
					// 	 la calidad del usuario con la interfaz menu */

	switch (current_state)
	{
		case MENU_INICIAL:		// Aqui inicia la maquina de estados!!!
			TeraTerm_Menu();	// Menu inicial con las 8 opciones del panel electronico

			if (UART0_key == key_1) {
			current_state = sub_1;	//** Transicion al siguiente estado */

			} else if (UART0_key == key_2) {
				current_state = sub_2;	//** Transicion al siguiente estado */

			} else if (UART0_key == key_3) {
				current_state = sub_3;	//** Transicion al siguiente estado */

			} else if (UART0_key == key_4) {
				current_state = sub_4;	//** Transicion al siguiente estado */

			} else if (UART0_key == key_5) {
				current_state = sub_5;	//** Transicion al siguiente estado */

			} else if (UART0_key == key_6) {
				current_state = sub_6;	//** Transicion al siguiente estado */

			} else if (UART0_key == key_7) {
				current_state = sub_7;	//** Transicion al siguiente estado */

			} else if (UART0_key == key_8) {
				current_state = sub_8;	//** Transicion al siguiente estado */

			} else {
				current_state = MENU_INICIAL;	//** No cambia */
			}
			break;

		case sub_1:
			submenu1();

			current_state = CONTROL_FSM;	//** ENTRO A FSM de este submenu */
			g_FSM_status_flags.submenu_1 = TRUE;
			break;

		case sub_2:
			submenu2();

			current_state = CONTROL_FSM;	//** ENTRO A FSM de este submenu */
			g_FSM_status_flags.submenu_2 = TRUE;
			break;

		case sub_3:
			submenu3();
			if (UART0_key == ESC) {
				current_state = MENU_INICIAL;//** Regreso al menu inicial */
			}
			break;

		case sub_4:
			submenu4();
			if (UART0_key == ESC) {
				current_state = MENU_INICIAL;//** Regreso al menu inicial */
			}
			break;

		case sub_5:
			submenu5();

			current_state = CONTROL_FSM;	//** ENTRO A FSM de este submenu */
			g_FSM_status_flags.submenu_5 = TRUE;
			break;

		case sub_6:
			submenu6();

			current_state = CONTROL_FSM;	//** ENTRO A FSM de este submenu */
			g_FSM_status_flags.submenu_6 = TRUE;
			break;

		case sub_7:
			submenu7();

			current_state = CONTROL_FSM;	//** ENTRO A FSM de este submenu */
			g_FSM_status_flags.submenu_7 = TRUE;
			break;

		case sub_8:
			submenu8();

			current_state = CONTROL_FSM;	//** ENTRO A FSM de este submenu */
			g_FSM_status_flags.submenu_8 = TRUE;
			break;

		case CONTROL_FSM:

			// Los submenus 3 y 4 no llegan aqui por constante refresh! :)
			//Permanece en el submenu correspondiente (1, 2 -, -,  5, 6, 7, 8)

			if (g_FSM_status_flags.submenu_1 == TRUE){
				FSM_Submenu_1();
				//** INSERT HERE THE DIFERENT FSM for submenu 1
			}//** END FSM del: if (g.submenu_1 == TRUE)

			if (g_FSM_status_flags.submenu_2 == TRUE){
				FSM_Submenu_2();
				//** INSERT HERE THE DIFERENT FSM for submenu 2
			}//** END FSM del: if (g.submenu_2 == TRUE)

			if (g_FSM_status_flags.submenu_5 == TRUE){
				uint8_t number_message = 0;
				if (g_new_key_UART0 == TRUE){
					i_sub5++;		// Numero de veces que se presiono una tecla
					g_new_key_UART0 = FALSE;
				}

				if (i_sub5 == 1) {
					numero_mensaje[0] = UART0_key;		// ASCII en decimal = numero de msj
				}
				if (numero_mensaje[1] == ENTER){
					switch (numero_mensaje[0])
					{
						case '1':
							mensaje_1[i_sub5 - 3] = UART0_key;		// ASCII en decimal
							break;

						case '2':
							mensaje_2[i_sub5 - 3] = UART0_key;		// ASCII en decimal
							break;

						case '3':
							mensaje_3[i_sub5 - 3] = UART0_key;		// ASCII en decimal
							break;

						case '4':
							mensaje_4[i_sub5 - 3] = UART0_key;		// ASCII en decimal
							break;

						case '5':
							mensaje_5[i_sub5 - 3] = UART0_key;		// ASCII en decimal
							break;

						default:
							//** NO llega hasta aqui :) */
							break;
					}// end switch (numero_mensaje[0])
				}

				if ( (numero_mensaje[1] == ENTER) && (UART0_key == ENTER) ) {
					if ( (i_sub5 >= 3) && (i_sub5 <= 33)) {	// Espera el segundo ENTER
						UART_put_string(UART_0, "\033[18;10H"); // Mueve una fila abajo
						UART_put_string(UART_0, "Su texto ha sido guardado! :)\r");
						UART_put_string(UART_0, "\033[19;10H"); // Mueve una fila abajo

						number_message = ((uint8_t)numero_mensaje[0]);
						memoria_write_mensaje_to_memmory(number_message - 48); // Movernos en la tabla ASCII

						g_new_key_UART0 = FALSE;
						i_sub5 = 0;		//**Reinicio del arreglo de modoficar DATE*/
						g_FSM_status_flags.submenu_5 = FALSE; //** Termina la FSM */
					}
				}
				if (i_sub5 == 2) {
					numero_mensaje[1] = UART0_key; // ASCII en decimal = primer ENTER
					UART_put_string(UART_0, "\033[16;10H"); // Mueve una fila abajo
				}

				//** INSERT HERE THE DIFERENT FSM for submenu 5
			}

			if (g_FSM_status_flags.submenu_6 == TRUE){
				FSM_Submenu_6();
				//** INSERT HERE THE DIFERENT FSM for submenu 6
			}

			if (g_FSM_status_flags.submenu_7 == TRUE){
				uint8_t number_message = 0;

				if (g_new_key_UART0 == TRUE){
					i_sub7++;		// Numero de veces que se presiono una tecla
					g_new_key_UART0 = FALSE;
				}


				if (i_sub7 == 1) {
					numero_msjMemoria[0] = UART0_key;		// ASCII en decimal = numero de msj
				}

				if ( (numero_msjMemoria[1] == ENTER) && (UART0_key == ENTER) ) {
					if ( i_sub7 >= 2) {	// Espera el segundo ENTER
						UART_put_string(UART_0, "\033[22;10H"); // Mueve una fila abajo
						UART_put_string(UART_0, "Mensaje sacado de memoria! :)\r");
						UART_put_string(UART_0, "\033[24;10H"); // Mueve una fila abajo

						number_message = ((uint8_t)numero_msjMemoria[0]);

						uint8_t i = 0;
						for (i = 0; i < 30; ++i) {
							memoria_read_byte(number_message - 48); // Movernos en la tabla ASCII
						}

						uint8_t* ptr_dataMemory_1 = Get_dataMemory_1();

						uint8_t* ptr_dataMemory_2 = Get_dataMemory_2();

						uint8_t* ptr_dataMemory_3 = Get_dataMemory_3();

						uint8_t* ptr_dataMemory_4 = Get_dataMemory_4();

						uint8_t* ptr_dataMemory_5 = Get_dataMemory_5();

						if ( (number_message-48) == 1){
							UART_put_string(UART_0,ptr_dataMemory_1);
						}

						if ( (number_message-48) == 2){
							UART_put_string(UART_0,ptr_dataMemory_2);
						}

						if ( (number_message-48) == 3){
							UART_put_string(UART_0,ptr_dataMemory_3);
						}

						if ( (number_message-48) == 4){
							UART_put_string(UART_0,ptr_dataMemory_4);
						}

						if ( (number_message-48) == 5){
							UART_put_string(UART_0,ptr_dataMemory_5);
						}

						g_new_key_UART0 = FALSE;
						i_sub7 = 0;		//**Reinicio del arreglo de modoficar DATE*/
						g_FSM_status_flags.submenu_7 = FALSE; //** Termina la FSM */
					}
				}

				if (i_sub7 == 2) {
					numero_msjMemoria[1] = UART0_key; // ASCII en decimal = primer ENTER
					UART_put_string(UART_0, "\033[21;10H"); // Mueve una fila abajo
				}
				//** INSERT HERE THE DIFERENT FSM for submenu 7
			}

			if (g_FSM_status_flags.submenu_8 == TRUE){
				//** INSERT HERE THE DIFERENT FSM for submenu 8
			}

			//** ¿Se desea salir del actual submenu?
			if (UART0_key == ESC) {
				current_state = MENU_INICIAL;//** Regreso al menu inicial */
				g_FSM_status_flags.submenu_6 = FALSE; //** Termina la FSM */
			}
			break;

		default:
			//** */
			//NOP
			//** */
			break;
	} //end switch(current state)
}

void RTC_BCD_TIME_Registers(void) {
	uint32_t RTC_Decimal_seconds = 0;
	uint32_t RTC_Decimal_minutes = 0;
	uint32_t RTC_Decimal_hours = 0;

	RTC_read_Hours();	//** Lee las horas del RTC */
	RTC_Decimal_hours = RTC_Get_Hours(); 	 //** In Decimal Format */
	Time_to_String(RTC_Decimal_hours, HOUR);

	RTC_read_Minutes(); //** Lee los minutos del RTC */
	RTC_Decimal_minutes = RTC_Get_Minutes(); //** In Decimal Format */
	Time_to_String(RTC_Decimal_minutes, MIN);

	RTC_read_Seconds();	//** Lee los segundos del RTC */
	RTC_Decimal_seconds = RTC_Get_Seconds(); //** In Decimal Format */
	Time_to_String(RTC_Decimal_seconds, SEC);
}

void RTC_BCD_DATE_Registers(void) {
	uint32_t RTC_Decimal_date = 0;
	uint32_t RTC_Decimal_month = 0;
	uint32_t RTC_Decimal_year = 0;

	RTC_read_DATE();	//** Lee el dia (fecha) del RTC */
	RTC_Decimal_date = RTC_Get_DATE(); 	 	 //** In Decimal Format */
	Time_to_String(RTC_Decimal_date, DATE);

	RTC_read_MONTH();	//** Lee el mes del RTC */
	RTC_Decimal_month = RTC_Get_MONTH(); 	 //** In Decimal Format */
	Time_to_String(RTC_Decimal_month, MONTH);

	RTC_read_YEAR();	//** Lee el anio del RTC */
	RTC_Decimal_year = RTC_Get_YEAR(); 	 	 //** In Decimal Format */
	Time_to_String(RTC_Decimal_year, YEAR);
}

void submenu1 (void) {
	UART_put_string(UART_0, "\033[2J"); 	// Clear
	UART_put_string(UART_0, "\033[10;10H"); // Muevo el cursor
	UART_put_string(UART_0, "1) Escribir hora en formato:\r");
	UART_put_string(UART_0, "\033[11;10H");
	UART_put_string(UART_0, "HH:MM:SS + [ENTER]\r");
	UART_put_string(UART_0, "\033[13;10H"); // Mueve una fila abajo
}

void submenu2 (void) {
	UART_put_string(UART_0, "\033[2J"); 	// Clear
	UART_put_string(UART_0, "\033[10;10H"); // Muevo el cursor
	UART_put_string(UART_0, "2) Esribir fecha en formato:\r");
	UART_put_string(UART_0, "\033[11;10H");
	UART_put_string(UART_0, "DD/MM/AA + [ENTER]\r");
	UART_put_string(UART_0, "\033[13;10H"); // Mueve una fila abajo
}

void submenu3 (void) {
	uint8_t* ptr_string_seconds = Get_String_Time(SEC);
	uint8_t* ptr_string_minutes = Get_String_Time(MIN);
	uint8_t* ptr_string_hours   = Get_String_Time(HOUR);

	UART_put_string(UART_0, "\033[2J"); 	// Clear
	UART_put_string(UART_0, "\033[10;10H"); // Muevo el cursor
	UART_put_string(UART_0, "3) La hora actual es:\r");
	UART_put_string(UART_0, "\033[12;10H");
	UART_put_string(UART_0, ptr_string_hours);		// Se actualizara - ok!
	UART_put_string(UART_0, ptr_string_minutes);	// Se actualizara - ok!
	UART_put_string(UART_0, ptr_string_seconds);	// Se actualizara - ok!
	UART_put_string(UART_0, "\033[14;10H"); // Mueve una fila abajo
}

void submenu4(void) {
	uint8_t* ptr_string_date  = Get_String_Time(DATE);
	uint8_t* ptr_string_month = Get_String_Time(MONTH);
	uint8_t* ptr_string_year  = Get_String_Time(YEAR);

	UART_put_string(UART_0, "\033[2J"); 	// Clear
	UART_put_string(UART_0, "\033[10;10H"); // Muevo el cursor
	UART_put_string(UART_0, "4) La fecha de hoy es:\r");
	UART_put_string(UART_0, "\033[12;10H");
	UART_put_string(UART_0, ptr_string_date);	// Se actualizara - ok!
	UART_put_string(UART_0, ptr_string_month);	// Se actualizara - ok!
	UART_put_string(UART_0, ptr_string_year);	// Se actualizara - ok!
	UART_put_string(UART_0, "\033[14;10H"); // Mueve una fila abajo
}

void submenu5(void) {
	UART_put_string(UART_0, "\033[2J"); 	// Clear
	UART_put_string(UART_0, "\033[10;10H"); // Muevo el cursor
	UART_put_string(UART_0, "5) Escribir mensaje en memoria I2C\r");
	UART_put_string(UART_0, "\033[11;10H"); // Mueve una fila abajo
	UART_put_string(UART_0, "Numero de mensaje de 1 a 5 + [ENTER]:\r");
	UART_put_string(UART_0, "\033[14;10H"); // Mueve una fila abajo
	UART_put_string(UART_0, "Escribe el mensaje + [ENTER]: (MAX. 30 caracteres)\r");
	UART_put_string(UART_0, "\033[15;10H"); // Mueve una fila abajo

}

void submenu6(void) {
	UART_put_string(UART_0, "\033[2J"); 	// Clear
	UART_put_string(UART_0, "\033[10;10H"); // Muevo el cursor
	UART_put_string(UART_0, "6) Mostrar hora en matriz de leds\r");
	UART_put_string(UART_0, "\033[12;10H");
	UART_put_string(UART_0, "Deseas mostrar la hora en matriz de leds?\r");
	UART_put_string(UART_0, "\033[13;10H"); // Mueve una fila abajo
	UART_put_string(UART_0, "Si [ENTER]\r");
	UART_put_string(UART_0, "\033[14;10H"); // Mueve una fila abajo
}

void submenu7(void) {

	UART_put_string(UART_0, "\033[2J"); 	// Clear
	UART_put_string(UART_0, "\033[10;10H"); // Muevo el cursor
	UART_put_string(UART_0, "7) Mostrar mensaje en matriz de leds\r");
	UART_put_string(UART_0, "\033[11;10H"); // Mueve una fila abajo
	UART_put_string(UART_0, "Mensajes almacenados:\r");
	UART_put_string(UART_0, "\033[12;12H"); // Mueve una fila abajo y a la derecha
	UART_put_string(UART_0, mensaje_1);
	// INSERT ARRAY
	UART_put_string(UART_0, "\033[13;12H"); // Mueve una fila abajo y a la derecha
	UART_put_string(UART_0, mensaje_2);
	// INSERT ARRAY
	UART_put_string(UART_0, "\033[14;12H"); // Mueve una fila abajo y a la derecha
	UART_put_string(UART_0, mensaje_3);
	// INSERT ARRAY
	UART_put_string(UART_0, "\033[15;12H"); // Mueve una fila abajo y a la derecha
	UART_put_string(UART_0, mensaje_4);
	// INSERT ARRAY
	UART_put_string(UART_0, "\033[16;12H"); // Mueve una fila abajo y a la derecha
	UART_put_string(UART_0, mensaje_5);
	// INSERT ARRAY
	UART_put_string(UART_0, "\033[18;10H"); // Mueve una fila abajo
	UART_put_string(UART_0, "Mensaje a mostrar? + [ENTER]\r");
	UART_put_string(UART_0, "\033[20;10H"); // Mueve una fila abajo

}

void submenu8(void) {
	UART_put_string(UART_0, "\033[2J"); 	// Clear
	UART_put_string(UART_0, "\033[10;10H"); // Muevo el cursor
	UART_put_string(UART_0, "8) Comunicacion con terminal 2\r");
	UART_put_string(UART_0, "\033[11;10H"); // Mueve una fila abajo
	UART_put_string(UART_0, "(Para enviar con [ENTER] y para salir con [ESC])\r");
	UART_put_string(UART_0, "\033[12;10H"); // Mueve una fila abajo
	UART_put_string(UART_0, terminal_1);
	// INSERT ARRAY for message
	UART_put_string(UART_0, "\033[13;10H"); // Mueve una fila abajo
	UART_put_string(UART_0, terminal_2);
	// INSERT ARRAY for message
	UART_put_string(UART_0, "\033[14;10H"); // Mueve una fila abajo
	UART_put_string(UART_0, terminal_1);
	// INSERT ARRAY for message
	UART_put_string(UART_0, "\033[15;10H"); // Mueve una fila abajo
	UART_put_string(UART_0, terminal_2);
	// INSERT ARRAY for message
	UART_put_string(UART_0, "\033[17;10H"); // Mueve una fila abajo
}

uint8_t* Get_modified_hours(void) {
	uint8_t* ptr_modified_hours = ARRAY_mod_hours;
	return (ptr_modified_hours);
}

uint8_t* Get_modified_minutes(void) {
	uint8_t* ptr_modified_minutes = ARRAY_mod_minutes;
	return (ptr_modified_minutes);
}

uint8_t* Get_modified_seconds(void) {
	uint8_t* ptr_modified_seconds = ARRAY_mod_seconds;
	return (ptr_modified_seconds);
}

uint8_t* Get_modified_date(void) {
	uint8_t* ptr_modified_date = ARRAY_mod_Date;
	return (ptr_modified_date);
}

uint8_t* Get_modified_month(void) {
	uint8_t* ptr_modified_month = ARRAY_mod_Month;
	return (ptr_modified_month);
}

uint8_t* Get_modified_year(void) {
	uint8_t* ptr_modified_year = ARRAY_mod_Year;
	return (ptr_modified_year);
}

void FSM_Submenu_1(void) {
	if (g_new_key_UART0 == TRUE){
		i_sub1++;		// Numero de veces que se presiono una tecla
		g_new_key_UART0 = FALSE;
	}

	if (i_sub1 == 1){
		modified_hours[0] = UART0_key;		// ASCII en decimal
	}

	if (i_sub1 == 2){
		modified_hours[1] = UART0_key;		// ASCII en decimal
	}

	if (i_sub1 == 3){
		//** WAIT for BARRA diagonal '/'
	}

	if (i_sub1 == 4){
		modified_minutes[0] = UART0_key;	// ASCII en decimal
	}

	if (i_sub1 == 5){
		modified_minutes[1] = UART0_key;	// ASCII en decimal
	}

	if (i_sub1 == 6){
		//** WAIT for BARRA diagonal '/'
	}

	if (i_sub1 == 7){
		modified_seconds[0] = UART0_key;		// ASCII en decimal
	}

	if (i_sub1 == 8){
		modified_seconds[1] = UART0_key;		// ASCII en decimal
	}

	if (UART0_key == ENTER) {
		UART_put_string(UART_0, "\033[14;10H"); // Mueve una fila abajo
		UART_put_string(UART_0, "La hora ha sido cambiada! :)\r");
		UART_put_string(UART_0, "\033[15;10H"); // Mueve una fila abajo
		RTC_write_Hours();		/** Configurado para MODIFICAR el registro de HORAS   */
		RTC_write_Minutes();	/** Configurado para MODIFICAR el registro de MINUTOS */
		RTC_write_Seconds();	/** Configurado para MODIFICAR el registro de SEGUNDOS*/
		g_new_key_UART0 = FALSE;
		i_sub1 = 0;		//**Reinicio del arreglo de modoficar TIME*/
		g_FSM_status_flags.submenu_1 = FALSE; //** Termina la FSM */
	}
}

void FSM_Submenu_2(void) {
	if (g_new_key_UART0 == TRUE){
		i_sub2++;		// Numero de veces que se presiono una tecla
		g_new_key_UART0 = FALSE;
	}

	if (i_sub2 == 1) {
		modified_Date[0] = UART0_key;		// ASCII en decimal
	}

	if (i_sub2 == 2) {
		modified_Date[1] = UART0_key;		// ASCII en decimal
	}

	if (i_sub2 == 3) {
		//** WAIT for BARRA diagonal '/'
	}

	if (i_sub2 == 4) {
		modified_Month[0] = UART0_key;		// ASCII en decimal
	}

	if (i_sub2 == 5) {
		modified_Month[1] = UART0_key;		// ASCII en decimal
	}

	if (i_sub2 == 6) {
		//** WAIT for BARRA diagonal '/'
	}

	if (i_sub2 == 7) {
		modified_Year[0] = UART0_key;		// ASCII en decimal
	}

	if (i_sub2 == 8) {
		modified_Year[1] = UART0_key;		// ASCII en decimal
	}

	if (UART0_key == ENTER) {
		UART_put_string(UART_0, "\033[14;10H"); // Mueve una fila abajo
		UART_put_string(UART_0, "La fecha ha sido cambiada! :)\r");
		UART_put_string(UART_0, "\033[15;10H"); // Mueve una fila abajo
		RTC_write_DATE(); 	 	/** Configurado para MODIFICAR el registro de DATE */
		RTC_write_MONTH(); 		/** Configurado para MODIFICAR el registro de MONTH*/
		RTC_write_YEAR(); 		/** Configurado para MODIFICAR el registro de YEAR */
		g_new_key_UART0 = FALSE;
		i_sub2 = 0;		//**Reinicio del arreglo de modoficar DATE*/
		g_FSM_status_flags.submenu_2 = FALSE; //** Termina la FSM */
	}
}

void FSM_Submenu_6(void) {
	uint8_t RTC_Decimal_minutes = 0;
	uint8_t RTC_Decimal_hours = 0;

	if (g_new_key_UART0 == TRUE && UART0_key != ESC) {
		i_sub6++;		// Numero de veces que se presiono una tecla
		g_new_key_UART0 = FALSE;
	}

	if (i_sub6 == 1) {
		matrix_ON[0] = UART0_key;		// ASCII en decimal
	}

	if (i_sub6 == 2) {
		matrix_ON[1] = UART0_key;		// ASCII en decimal
	}

	if (matrix_ON[0] == '6'){
		i_sub6 = 0;		//**Reinicio del arreglo de modoficar TIME -> FORZADO*/
		g_new_key_UART0 = FALSE;
	}

	if ((matrix_ON[0] == 's') && (matrix_ON[1] == 'i') && (UART0_key == ENTER)) {
		RTC_read_Hours();	//** Lee las horas del RTC */
		RTC_Decimal_hours = RTC_Get_Hours(); //** In Decimal Format */

		RTC_read_Minutes(); //** Lee los minutos del RTC */
		RTC_Decimal_minutes = RTC_Get_Minutes(); //** In Decimal Format */

		Submenu_matriz_horas_minutos(RTC_Decimal_hours,RTC_Decimal_minutes);

		g_new_key_UART0 = FALSE;
		i_sub6 = 0;		//**Reinicio del arreglo de modoficar TIME*/
	}
}

uint8_t* Get_mensaje_1(void) {
	uint8_t* ptr_mensaje_1 = ARRAY_mensaje_1;
	return (ptr_mensaje_1);
}

uint8_t* Get_mensaje_2(void) {
	uint8_t* ptr_mensaje_2 = ARRAY_mensaje_2;
	return (ptr_mensaje_2);
}

uint8_t* Get_mensaje_3(void) {
	uint8_t* ptr_mensaje_3 = ARRAY_mensaje_3;
	return (ptr_mensaje_3);
}

uint8_t* Get_mensaje_4(void) {
	uint8_t* ptr_mensaje_4 = ARRAY_mensaje_4;
	return (ptr_mensaje_4);
}

uint8_t* Get_mensaje_5(void) {
	uint8_t* ptr_mensaje_5 = ARRAY_mensaje_5;
	return (ptr_mensaje_5);
}
