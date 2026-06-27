#include "stm32f4xx_hal.h"
#include "LEDS.h"
#include <stdbool.h>

extern TIM_HandleTypeDef htim4;
volatile uint8_t dma_listo = 0;
volatile uint8_t noenviar =0;

void armadoled(uint8_t ESTADO, bool TURNO_JUGADOR, uint32_t *L, uint8_t COLOR_P2, uint8_t COLOR_P1, uint8_t CPU_DIFF, bool CPU, uint8_t COLUMNA, uint8_t M[8][4]){
	static uint32_t  C1 = 0x000000;					// Variable para color jugador 1
	static uint32_t  C2 = 0x000000;					// Variable para color jugador 2
													  //     0   1   2    3
	uint8_t matrizled[8][4] =  {{ 31, 27, 23, 19 },   // 0  D32 D28 D24 D20
								{ 30, 26, 22, 18 },   // 1  D31 D27 D23 D19
								{ 29, 25, 21, 17 },   // 2  D30 D26 D22 D18
								{ 28, 24, 20, 16 },   // 3  D29 D25 D21 D17
								{ 15, 11,  7,  3 },   // 4  D16 D12 D8  D4
								{ 14, 10,  6,  2 },   // 5  D15 D11 D7  D3
								{ 13,  9,  5,  1 },   // 6  D14 D10 D6  D2
								{ 12,  8,  4,  0 },   // 7  D13 D9  D5  D1
		};
	switch (ESTADO){														// switch para determinar el estado
	case 0:
		switch (COLOR_P1){													// Seleccion color de jugador 1
		 case 1: C1=0x010506;break;
		 case 2: C1=0x010604;break;
		 case 3: C1=0x020703;break;
		}
		switch (COLOR_P2){													// Seleccion color de jugador 2
		 case 1: C2=0x060501;break;
		 case 2: C2=0x040601;break;
		 case 3: C2=0x070302;break;
		}
		L[matrizled[0][0]] = C1; L[matrizled[0][1]] = C1;					// Visualziacion de color J1  en pantalla
		L[matrizled[1][0]] = C1; L[matrizled[1][1]] = C1;					// Visualziacion de color J1  en pantalla
		L[matrizled[0][2]] = C2; L[matrizled[0][3]] = C2;					// Visualziacion de color J2  en pantalla
		L[matrizled[1][2]] = C2; L[matrizled[1][3]] = C2;					// Visualziacion de color J2  en pantalla

		if (CPU == false)													// Visualziacion de color CPU
			L[matrizled[3][0]] = 0x000100;									// Apagado
		else
			L[matrizled[3][0]] = 0x010000;									// Encendido

		L[24]=0x000000;L[20]=0x000000;L[16]=0x000000;						// Reinicia los leds de dificultad
		for (int i = 1;i<=CPU_DIFF; i++)									// Este for enciende los leds de dificultad segun CPU_DIFF
			L[matrizled[3][i]] = 0x000001;									//
		break;
	case 1:
		if (L[24] == 0x000001)												// Este If borra la pantalla usada en menu, se mira el led 24 en azul pues es el nivel basico del CPU
					for (int i = 0; i < 32; i++)
						L[i]=0x000000;

		L[31]=0x000000;L[27]=0x000000;L[23]=0x000000;L[19]=0x000000;		// Limpia la primera fila para permitir ver que columna se selecciona
		if (!TURNO_JUGADOR)													// Dependiendo el turno es el color presente en la columna
			L[matrizled[0][COLUMNA]] = C1;									//
		else
			L[matrizled[0][COLUMNA]] = C2;               					//
		break;
	case 2:

		for (int i = 0; i < 8; i++) {										//Revisa toda la matriz M para hacer la animacion de gravedad
		    for (int j = 0; j < 4; j++) {
		        if (M[i][j] == COLOR_P1)
		            L[matrizled[i][j]] = C1;
		        else if (M[i][j] == COLOR_P2)
		            L[matrizled[i][j]] = C2;
		        else
		            L[matrizled[i][j]] = 0x000000;
		    }
		}
	break;
	case 5:
		for (int i = 0; i < 8; i++) {										// Hace la animacion de victoria o empate llenando la matriz
				    for (int j = 0; j < 4; j++) {
				        if (M[i][j] == COLOR_P1)
				            L[matrizled[i][j]] = C1;
				        else if (M[i][j] == COLOR_P2)
				            L[matrizled[i][j]] = C2;
				        else
				            L[matrizled[i][j]] = 0x010101;

	}
}
	break;
	}
}

void comunicacionled(uint32_t *L, uint32_t *vectorled){
	volatile uint32_t indice = 0;
	for (int i=0; i<32; i++){												//Mira cada componente del vector L
		for (int j=23; j>=0; j--){											//Cuenta 24 por la cantidad de bits de cada color
			if ((L[i]>> j )&1){												//Dezplaza a la derecha y compara con 1
				vectorled[indice] = 31;

			}
			else{
				vectorled[indice] = 16;
			}
			indice++;
		}
	}
	for (int i=0; i<50; i++){												//Llena 50 bits mas con 0 para el reset
		vectorled[indice] = 0;
		indice++;
	}
}



void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim4)			//Interrupcion DMA
{
	if (htim4->Instance == TIM4){
        dma_listo = 1;
        noenviar=0;
}
}

void ENVIODMA(uint32_t *vecled)												//Se comienza el envio del DMA
{
	if (noenviar==0){														//Impide que vuelva a llamarse la funcion
		noenviar=1;
		dma_listo = 0;
		HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_1, (uint32_t *)vecled, 818);

    while (dma_listo == 0)
    {
    }
	}

   //HAL_TIM_PWM_Stop_DMA(&htim4, TIM_CHANNEL_1);
}
