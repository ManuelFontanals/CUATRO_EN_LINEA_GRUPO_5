
#include "TECLADO.h"
#include "main.h"
#include <stdbool.h>


//------------------DEFINE VARIABLES------------------

extern TIM_HandleTypeDef htim14;

volatile uint8_t LLAMA_COL = 0;		//si no es cero, llamo alguna col x
uint8_t contador_estable = 0;		// checkea cantidad de pulsaciones por lectura de
volatile uint8_t Teclado_Accionado = 16; // que tecla se apreta
bool INICIO_ESTADO_TECLADO = 1;			// cuando entra a MENU o PLAYER inicia TIM_14

// inicializo las estructuras creadas para cada boton

Debounce_t btn1 = {
		.ultimo_raw = GPIO_PIN_SET,
		.estado_filtrado = GPIO_PIN_SET,
		.contador = 0
};

Debounce_t btn2 = {
		.ultimo_raw = GPIO_PIN_SET,
		.estado_filtrado = GPIO_PIN_SET,
		.contador = 0
};

Debounce_t btn3 = {
		.ultimo_raw = GPIO_PIN_SET,
		.estado_filtrado = GPIO_PIN_SET,
		.contador = 0
};
Debounce_t btn4 = {
		.ultimo_raw = GPIO_PIN_SET,
		.estado_filtrado = GPIO_PIN_SET,
		.contador = 0
};

//INICIALIZO FILAS EN 1 (SET)
void INICIO_TECLADO(void)
{
	HAL_GPIO_WritePin(FILA_A_GPIO_Port, FILA_A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_SET);
}

// ANTIRREBOTE por flanco, si mantengo apretado el boton no le hace caso
bool VerificarBoton(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, Debounce_t *btn)
{
	// Lectura "anterior"
	GPIO_PinState lectura = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);

	// Chequeo si lectura anterior != lectura actual
	if (lectura != btn->ultimo_raw)
	{
		btn->contador = 0;
		btn->ultimo_raw = lectura;
	}
	else
	{
		if (btn->contador < UMBRAL)
			btn->contador++;
	}

	// si contador pasa el umbral y si significa boton apretado entonces acciona
	if (btn->contador >= UMBRAL)
	{
		if (btn->estado_filtrado != lectura)
		{
			btn->estado_filtrado = lectura;

			// flanco de subida
			if (lectura == GPIO_PIN_SET)
			{
				return true;
			}
		}
	}
	return false;
}


// Rutina de atención a la interrupción del temporizador 14
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// Checkea estado boton COLUMNA_A
	if (VerificarBoton(COLUMNA_A_GPIO_Port, COLUMNA_A_Pin, &btn1)) LLAMA_COL = 1;

	// Checkea estado boton COLUMNA_B
	else if (VerificarBoton(COLUMNA_B_GPIO_Port, COLUMNA_B_Pin, &btn2)) LLAMA_COL = 2;

	// Checkea estado boton COLUMNA_C
	else if (VerificarBoton(COLUMNA_C_GPIO_Port, COLUMNA_C_Pin, &btn3)) LLAMA_COL = 3;

	// Checkea estado boton COLUMNA_D
	else if (VerificarBoton(COLUMNA_D_GPIO_Port, COLUMNA_D_Pin, &btn4)) LLAMA_COL = 4;

	else LLAMA_COL = 0;
}

//	SI LLAMA_COL DE ATENCION DE SUBRUTINA ES DISTINTO DE 0 ENTONCES CHECKEA CUAL FUE
void TecladoPresiona(void) {

	if (LLAMA_COL == 0) return;

	HAL_TIM_Base_Stop_IT(&htim14);

	switch (LLAMA_COL)
	{
		case 1:
		{
			// Accion sobre MT(0,0) o 0
			HAL_GPIO_WritePin(FILA_A_GPIO_Port, FILA_A_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_A_GPIO_Port, COLUMNA_A_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 0;
				break;
			}
			HAL_GPIO_WritePin(FILA_A_GPIO_Port, FILA_A_Pin, GPIO_PIN_SET);


			// Accion sobre MT(1,0) o 4
			HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_A_GPIO_Port, COLUMNA_A_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 4;
				break;
			}
			HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_SET);


			// Accion sobre MT(2,0) o 8
			HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_A_GPIO_Port, COLUMNA_A_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 8;
				break;
			}
			HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_SET);

			// Accion sobre MT(3,0) o 12
			HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_A_GPIO_Port, COLUMNA_A_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 12;
				break;
			}
			HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_SET);
		} break;

		//CHECKEO SOLO COLUMNA B
		case 2:
		{
			// Accion sobre MT(0,1) o 1
			HAL_GPIO_WritePin(FILA_A_GPIO_Port, FILA_A_Pin, GPIO_PIN_RESET);
//			HAL_Delay(1);
			if (HAL_GPIO_ReadPin(COLUMNA_B_GPIO_Port, COLUMNA_B_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 1;
				break;
			}
			HAL_GPIO_WritePin(FILA_A_GPIO_Port, FILA_A_Pin, GPIO_PIN_SET);


			// Accion sobre MT(1,1) o 5
			HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_RESET);
//			HAL_Delay(1);
			if (HAL_GPIO_ReadPin(COLUMNA_B_GPIO_Port, COLUMNA_B_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 5;
				break;
			}
			HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_SET);


			// Accion sobre MT(2,1) o 9
			HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_RESET);
//			HAL_Delay(1);
			if (HAL_GPIO_ReadPin(COLUMNA_B_GPIO_Port, COLUMNA_B_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 9;
				break;
			}
			HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_SET);

			// Accion sobre MT(3,1) o 13
			HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_RESET);
//			HAL_Delay(1);
			if (HAL_GPIO_ReadPin(COLUMNA_B_GPIO_Port, COLUMNA_B_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 13;
				break;
			}
			HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_SET);
		} break;

		//CHEQUEO SOLO COLUMNA C
		case 3:
		{
			// Accion sobre MT(0,2) o 2
			HAL_GPIO_WritePin(FILA_A_GPIO_Port, FILA_A_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_C_GPIO_Port, COLUMNA_C_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 2;
				break;
			}
			HAL_GPIO_WritePin(FILA_A_GPIO_Port, FILA_A_Pin, GPIO_PIN_SET);


			// Accion sobre MT(1,2) o 6
			HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_RESET);
//			HAL_Delay(1);
			if (HAL_GPIO_ReadPin(COLUMNA_C_GPIO_Port, COLUMNA_C_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 6;
				break;
			}
			HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_SET);


			// Accion sobre MT(2,2) o 10
			HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_RESET);
//			HAL_Delay(1);
			if (HAL_GPIO_ReadPin(COLUMNA_C_GPIO_Port, COLUMNA_C_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 10;
				break;
			}
			HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_SET);

			// Accion sobre MT(3,2) o 14
			HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_RESET);
//			HAL_Delay(1);
			if (HAL_GPIO_ReadPin(COLUMNA_C_GPIO_Port, COLUMNA_C_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 14;
				break;
			}
			HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_SET);
		} break;
		case 4:
		{
			// Accion sobre MT(0,3) o 3
			HAL_GPIO_WritePin(FILA_A_GPIO_Port, FILA_A_Pin, GPIO_PIN_RESET);
//			HAL_Delay(1);
			if (HAL_GPIO_ReadPin(COLUMNA_D_GPIO_Port, COLUMNA_D_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 3;
				break;
			}
			HAL_GPIO_WritePin(FILA_A_GPIO_Port, FILA_A_Pin, GPIO_PIN_SET);


			// Accion sobre MT(1,3) o 7
			HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_RESET);
//			HAL_Delay(1);
			if (HAL_GPIO_ReadPin(COLUMNA_D_GPIO_Port, COLUMNA_D_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 7;
				break;
			}
			HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_SET);


			// Accion sobre MT(2,3) o 11
			HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_RESET);
//			HAL_Delay(1);
			if (HAL_GPIO_ReadPin(COLUMNA_D_GPIO_Port, COLUMNA_D_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 11;
				break;
			}
			HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_SET);

			// Accion sobre MT(3,3) o 15
			HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_RESET);
//			HAL_Delay(1);
			if (HAL_GPIO_ReadPin(COLUMNA_D_GPIO_Port, COLUMNA_D_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 15;
				break;
			}
			HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_SET);
		} break;

	} // END SWITCH

	//Reseteo variables para la proxima lectura
	LLAMA_COL = 0;
	INICIO_TECLADO();
	HAL_TIM_Base_Start_IT(&htim14);

}


