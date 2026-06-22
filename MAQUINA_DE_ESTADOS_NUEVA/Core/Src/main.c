/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


// INCLUYO libreria para números aleatorios
#include <stdlib.h>
// LIB BOOL
#include <stdbool.h>
// INCLUYE DEL TECLADO.h
#include "TECLADO.h"

// LIB MEMORIA
#include <string.h>


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim14;

/* USER CODE BEGIN PV */


// MEMORIA debe ser una matriz de 8x4
// donde en los bordes tengo ceros, esto es para simplificar la logica de END_GAME

uint8_t M[8][4] = {0};
//			C1	C2	C3	C4
//		F1	x	x	x	x
//		F2	x	x	x	x
//		F3	x	x	x	x
//		F4	x	x	x	x
//		F5	x	x	x	x
//		F6	x	x	x	x
//		F7	x	x	x	x
//		F8	x	x	x	x


//	ESTADO elije en que estado de la maquina esta
//	0	menu
//	1	P1 y P2
//	2	TRANSICION
//	3	CPU
//	4	END GAME
//	5	TRANSICION_END_GAME
uint8_t ESTADO = 0;

// Si hay ganador
//GANA = 0 NO FIN
//GANA = 1 P1
//GANA = 2 P2 O CPU
//GANA = 3 EMPATE
uint8_t GANA = 0;

// Para MEMORIA y LEDs
uint8_t FILA = 0;
uint8_t COLUMNA;

//	QUIEN JUEGA, solo define el color de la ficha
//	0	P1
//	1	P2
bool TURNO_JUGADOR = 0;
// CPU no tiene un turno, es un cambio a otro estado


// si CPU = 0 juega P2; si CPU = 1, juega CPU
bool CPU = 0;

// CPU_DIFF elijo dificultad de CPU
//	1	random
//	2	facil
//	3	dificil???
uint8_t CPU_DIFF = 1;


// Por ahora color es un integer, luego vemos
uint8_t COLOR_P1 = 1;
uint8_t COLOR_P2 = 2;

uint8_t COLOR = 1;



// MEPA Q ESTO ES PARA ASIGNAR COLOR
//uint32_t VECTOR_COLOR_3[8] = {D20,D19,D18,D17,D4,D3,D2,D1}





/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM14_Init(void);
/* USER CODE BEGIN PFP */
void MENU(void);
void PLAYER(void);
void TRANSICION(void);
void INICIO_JUEGO(void);
void CPU_JUEGA(void);
void END_GAME(void);
void JUGADA_ACEPTADA(void);
void TRANSICION_END_GAME(void);
uint8_t WIN_CONDITION(void);
uint8_t COLOR_PLAYER(bool TURNO_JUGADOR);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */

  INICIO_TECLADO();
  INICIO_JUEGO();


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  switch (ESTADO)
	  {
	      case 0:
	          MENU();
	          break;

	      case 1:
	          PLAYER();
	          break;

	      case 2:
	          TRANSICION();
	          break;

	      case 3:
	          CPU_JUEGA();
	          break;

	      case 4:
	          END_GAME();
	          break;

	      case 5:
	          TRANSICION_END_GAME();
	          break;
	  }

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 9999;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 7;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|FILA_D_Pin|FILA_C_Pin|FILA_B_Pin
                          |FILA_A_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : CS_I2C_SPI_Pin FILA_D_Pin FILA_C_Pin FILA_B_Pin
                           FILA_A_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|FILA_D_Pin|FILA_C_Pin|FILA_B_Pin
                          |FILA_A_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PDM_OUT_Pin */
  GPIO_InitStruct.Pin = PDM_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : I2S3_WS_Pin */
  GPIO_InitStruct.Pin = I2S3_WS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(I2S3_WS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI1_SCK_Pin SPI1_MISO_Pin SPI1_MOSI_Pin */
  GPIO_InitStruct.Pin = SPI1_SCK_Pin|SPI1_MISO_Pin|SPI1_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : COLUMNA_A_Pin COLUMNA_B_Pin COLUMNA_C_Pin COLUMNA_D_Pin */
  GPIO_InitStruct.Pin = COLUMNA_A_Pin|COLUMNA_B_Pin|COLUMNA_C_Pin|COLUMNA_D_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : CLK_IN_Pin */
  GPIO_InitStruct.Pin = CLK_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin
                           Audio_RST_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : I2S3_MCK_Pin I2S3_SCK_Pin I2S3_SD_Pin */
  GPIO_InitStruct.Pin = I2S3_MCK_Pin|I2S3_SCK_Pin|I2S3_SD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : VBUS_FS_Pin */
  GPIO_InitStruct.Pin = VBUS_FS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VBUS_FS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : OTG_FS_ID_Pin OTG_FS_DM_Pin OTG_FS_DP_Pin */
  GPIO_InitStruct.Pin = OTG_FS_ID_Pin|OTG_FS_DM_Pin|OTG_FS_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Audio_SCL_Pin Audio_SDA_Pin */
  GPIO_InitStruct.Pin = Audio_SCL_Pin|Audio_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// DEFINO ESTADO MENU Y SU INTERACCION CON TECLADO Y BUZZER
// Ver si agregar INTERFAZ de USUARIO
void MENU(void)
{

	// CUANDO ENTRA EN MENU ACTIVA INTERRUPT
	if (INICIO_ESTADO_TECLADO == 1)
		{
		  HAL_TIM_Base_Start_IT(&htim14);
		  INICIO_ESTADO_TECLADO = 0;
		}


	TecladoPresiona();

	switch (Teclado_Accionado)
	{


		// Elije si CPU activo o no
		case 4:
			{
				//buzzer
				CPU = !CPU;

			}break;

		// Elije diff de CPU
		case 5:
			{
				//buzzer
				CPU_DIFF = 1;

			}break;
		case 6:
			{
				//buzzer
				CPU_DIFF = 2;

			}break;
		case 7:
			{
				//buzzer
				CPU_DIFF = 3;

			}break;

		// CAMBIA DE ESTADO A P1
		case 8:
			{
				//buzzer
				HAL_TIM_Base_Stop_IT(&htim14);
				ESTADO = 1;
				INICIO_ESTADO_TECLADO = 1;

			}break;

		// Cambia color P1 y P2, ponele q son 3, subida
		case 10:
			{
				//buzzer
				if (COLOR_P1 < 3) COLOR_P1++;
				else COLOR_P1 = 1;

			}break;
		case 14:
			{
				//buzzer
				if (COLOR_P2 < 3) COLOR_P2++;
				else COLOR_P2 = 0;

			}break;
		// Cambia color P1 y P2, bajada
		case 9:
			{
				//buzzer
				if (COLOR_P1 > 1) COLOR_P1--;
				else COLOR_P1 = 3;

			}break;

		case 13:
			{
				//buzzer
				if (COLOR_P2 > 1) COLOR_P2--;
				else COLOR_P2 = 3;

			}break;

		// Si es distinto a alguna accion de teclado valida en MENU entonces teclado = 16
		default:
			{
				//buzzer
				Teclado_Accionado = 16;
			}break;


	}// END SWITCH

	Teclado_Accionado = 16;

}

void PLAYER(void)
{

	// CUANDO ENTRA EN PLAYER ACTIVA INTERRUPT
	if (INICIO_ESTADO_TECLADO == 1)
		{
		  HAL_TIM_Base_Start_IT(&htim14);
		  INICIO_ESTADO_TECLADO = 0;
		}

	TecladoPresiona();

	switch(Teclado_Accionado)
	{
		// Selecciona COLUMNA 1
		case 0:
		{
			//buzzer
			COLUMNA = 0;
		}break;

		// Selecciona COLUMNA 2
		case 1:
		{
			//buzzer
			COLUMNA = 1;
		}break;

		// Selecciona COLUMNA 3
		case 2:
		{
			//buzzer
			COLUMNA = 2;
		}break;

		// Selecciona COLUMNA 4
		case 3:
		{
			//buzzer
			COLUMNA = 3;
		}break;

		// Confirmar Jugada
		case 8:
		{
			//buzzer
			HAL_TIM_Base_Stop_IT(&htim14);
			ESTADO = 2;
			INICIO_ESTADO_TECLADO = 1;
		}break;

		// RESET
		case 12:
		{
			//buzzer
			HAL_TIM_Base_Stop_IT(&htim14);
			ESTADO = 5;
			INICIO_ESTADO_TECLADO = 1;
		}break;

		// Si es distinto a alguna accion de teclado valida en PLAYER entonces teclado = 16
		default:
		{
			//buzzer
			Teclado_Accionado = 16;
		}break;

	} // FIN SWITCH

	Teclado_Accionado = 16;
}


uint8_t COLOR_PLAYER(bool TURNO_JUGADOR)
{
	if (TURNO_JUGADOR)
	{
	        COLOR = COLOR_P2;
	        return COLOR;
	}

	COLOR = COLOR_P1;
	return COLOR;

}


// ACA VA LA LOGICA DEL JUEGO, DECIDE SI JUGADOR HACE JUGADA VALIDA, SI HACE ANIMACION DE TRANSICION, SI PASA A P2
// SI PASA A CPU O SI VUELVE A P1, O SI FINALIZA EL JUEGO, TODOO JUNTO
// aca por ahi si, se introduce una variable matriz de la posicion de las jugadas
void TRANSICION(void)
{

	COLOR = COLOR_PLAYER(TURNO_JUGADOR);

	if ( M[0][COLUMNA] != 0 )
	{
		//JUGADA INVALIDA

		//buzzer
		ESTADO = 1;
		return;
	}

		//JUGADA VALIDADA

		//buzzer
		JUGADA_ACEPTADA();

}

void INICIO_JUEGO(void)
{
	// aca hago algo con los LED para que pase un tiempito
	// es inicio de juego
	memset(M, 0, sizeof(M));
    ESTADO=0;
    GANA=0;
    FILA=0;
    COLUMNA=0;
    TURNO_JUGADOR=0;
    CPU=0;
    CPU_DIFF=1;
    COLOR_P1=1;
    COLOR_P2=2;
    COLOR=1;


}

void JUGADA_ACEPTADA(void)
{
	uint8_t c = COLUMNA;

	M[0][c] = COLOR;
	// ENCIENDO PRIMER LED
	//SI COLUMNA 3 ENTONCES ENCIENDO D20

	for (uint8_t f = 1; f < 8; f++)
	{
		if (M[f][c] != 0)
		{
			ESTADO = 4;
			return;
		}

//	ESTA FUNCION DEBE ENCENDER LA FILA ACTUAL Y APAGAR LA ANTERIOR
//		ASIGNACION_LEDS(c,f,COLOR)

		M[f][c] = COLOR;


		M[f - 1][c] = 0;

	}

//		disp(M);

	ESTADO = 4;
}


uint8_t WIN_CONDITION(void)
{
	// Zona central
	for (uint8_t f = 1; f <= 6; f++)
	{
		for (uint8_t c = 1; c <= 2; c++)
		{
			if (M[f][c] != 0)
			{
				if (
						((M[f-1][c]   == M[f][c]) && (M[f+1][c]   == M[f][c])) ||
						((M[f-1][c-1] == M[f][c]) && (M[f+1][c+1] == M[f][c])) ||
						((M[f][c-1]   == M[f][c]) && (M[f][c+1]   == M[f][c])) ||
						((M[f+1][c-1] == M[f][c]) && (M[f-1][c+1] == M[f][c]))
				)
				{
					return M[f][c];
				}
			}
		}
	}

	// Fila superior
	if (M[0][1] != 0)
	{
		if (
				((M[0][0] == M[0][1]) && (M[0][1] == M[0][2])) ||
				((M[0][1] == M[0][2]) && (M[0][2] == M[0][3]))
		)
		{
			return M[0][1];
		}
	}

	// Fila inferior
	if (M[7][1] != 0)
	{
		if (
				((M[7][0] == M[7][1]) && (M[7][1] == M[7][2])) ||
				((M[7][1] == M[7][2]) && (M[7][2] == M[7][3]))
		)
		{
			return M[7][1];
		}
	}

	// Columna izquierda
	for (uint8_t f = 1; f <= 6; f++)
	{
		if (M[f][0] != 0)
		{
			if ((M[f-1][0] == M[f][0]) &&
					(M[f+1][0] == M[f][0]))
			{
				return M[f][0];
			}
		}
	}

	// Columna derecha
	for (uint8_t f = 1; f <= 6; f++)
	{
		if (M[f][3] != 0)
		{
			if ((M[f-1][3] == M[f][3]) &&
					(M[f+1][3] == M[f][3]))
			{
				return M[f][3];
			}
		}
	}

	// Empate (fila superior llena)
	if ((M[0][0] != 0) &&
			(M[0][1] != 0) &&
			(M[0][2] != 0) &&
			(M[0][3] != 0))
	{
		return 5;
	}

	// No hay ganador
	return 0;
}

void END_GAME(void)
{

	GANA = WIN_CONDITION();

	if (GANA =! 0)
	{
		ESTADO = 5;
		return;
	}


	//SI NO ES FIN DE JUEGO

	// CAMBIA TURNO ENTRE P1 y (P2 o CPU)
	TURNO_JUGADOR = !TURNO_JUGADOR;

	//Si CPU = 0 entonces vuelve a PLAYER siempre
	if (CPU == 0)
	{
		ESTADO = 1;
		return;
	}


	// SI CPU = 1 entonces cambia entre turno CPU y P1
	if (TURNO_JUGADOR)
	{
		ESTADO = 3;
		return;
	}
	ESTADO = 1;


}


void TRANSICION_END_GAME(void)
{
	Teclado_Accionado = 16;

	if (INICIO_ESTADO_TECLADO == 1)
		{
		  HAL_TIM_Base_Start_IT(&htim14);
		  INICIO_ESTADO_TECLADO = 0;
		}

	while (Teclado_Accionado == 16)
	{
		TecladoPresiona();

		for (uint8_t f = 7; f >= 0; f--)
		        {
		            for (uint8_t c = 0; c < 4; c++)
		            {
		                M[f][c] = GANA;
		            }
		        }

	}
	HAL_TIM_Base_Stop_IT(&htim14);
	ESTADO = 0;
	INICIO_JUEGO();
	INICIO_ESTADO_TECLADO = 1;

}

void CPU_JUEGA(void)
{

	if (CPU_DIFF == 1)
	{
		uint8_t disponibles[4];
		uint8_t n = 0;

		for (uint8_t c = 0; c < 4; c++)
		{
			if (M[0][c] == 0)
			{
				disponibles[n++] = c;
			}
		}
		COLUMNA = disponibles[rand() % n];
	}
	else if (CPU_DIFF == 2)
	{

	}

	ESTADO = 2;

}

void ASIGNACION_LEDS(uint8_t columna, uint8_t fila, uint8_t COLOR)
{
	uint32_t HEX_COLOR = 0x000000;

	//ROJO
	if (COLOR == 1) HEX_COLOR = 0x1F0000;
	//AZUL
	if (COLOR == 2) HEX_COLOR = 0x00001F;

	if (columna == 0)
	{
//	encender fila actual
//	esto es enciendo D_X del vector asociado a VECTOR COLOR 0

//		VECTOR_COLOR_0[fila] = HEX_COLOR;
//	y apago D_X anterior
//		VECTOR_COLOR_0[fila - 1] = 0x000000;
	}
	else if (columna == 1)
	{
//	encender fila actual
//	esto es enciendo D_X del vector asociado a VECTOR COLOR 1

//		VECTOR_COLOR_1[fila] = HEX_COLOR;
//	y apago D_X anterior
//		VECTOR_COLOR_1[fila - 1] = 0x000000;
	}
	else if (columna == 2)
	{
//	encender fila actual
//	esto es enciendo D_X del vector asociado a VECTOR COLOR 2

//		VECTOR_COLOR_2[fila] = HEX_COLOR;
//	y apago D_X anterior
//		VECTOR_COLOR_2[fila - 1] = 0x000000;
	}
	else if (columna == 3)
	{
//	encender fila actual
//	esto es enciendo D_X del vector asociado a VECTOR COLOR 3

//		VECTOR_COLOR_3[fila] = HEX_COLOR;
//	y apago D_X anterior
//		VECTOR_COLOR_3[fila - 1] = 0x000000;
	}
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
