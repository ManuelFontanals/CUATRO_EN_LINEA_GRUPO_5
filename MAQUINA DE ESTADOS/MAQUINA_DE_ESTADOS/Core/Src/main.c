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

/* USER CODE BEGIN PV */


// MEMORIA debe ser una matriz de 9x5
// donde en los bordes tengo ceros, esto es para simplificar la logica de END_GAME

//		C0	C1	C2	C3	C4	C5
//	F1	0	x	x	x	x	0
//	F2	0	x	x	x	x	0
//	F3	0	x	x	x	x	0
//	F4	0	x	x	x	x	0
//	F5	0	x	x	x	x	0
//	F6	0	x	x	x	x	0
//	F7	0	x	x	x	x	0
//	F8	0	x	x	x	x	0
//	F9	0	0	0	0	0	0

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
uint8_t FILA = 1;
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

// SE crea un numero aleatorio para DIFF 1 de CPU
uint8_t ALEATORIO


// Por ahora color es un integer, luego vemos
uint8_t COLOR_P1 = 0;
uint8_t COLOR_P2 = 1;



// BORRAR DESPUES ES DE MODULO TECLADO
uint8_t Teclado_Accionado = 16;
uint8_t teclado_column = 0;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void MENU(void);
void PLAYER(void);
void TRANSICION(void);
void INICIO_JUEGO(void);
void CPU(void);
void END_GAME(void);
void JUGADA_ACEPTADA(void);
void TRANSICION_END_GAME(void);

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
  /* USER CODE BEGIN 2 */

  TECLADO_INTERRUPT_FLAG = 1;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  switch ESTADO
	  {
		  case 0: MENU();
		  case 1: PLAYER();
		  case 2: TRANSICION();
		  case 3: CPU();
		  case 4: END_GAME();
		  case 5: TRANSICION_END_GAME();
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
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : CS_I2C_SPI_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_I2C_SPI_GPIO_Port, &GPIO_InitStruct);

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

	// Observa COLUMNA llamada por TECLADO
	VERIFICAR_TECLA(teclado_column);


	switch(Teclado_Accionado)
	{
	// Si es 16 entonces no hace nada
	case 16: return;

	// Si es distinto a alguna accion de teclado valida en MENU entonces teclado = 16
	default:
		{
			//buzzer
			Teclado_Accionado = 16;
			break;
		}

	// Elije si CPU activo o no
	case 4:
		{
			//buzzer
			CPU = !CPU;
			break;
		}

	// Elije diff de CPU
	case 5:
		{
			//buzzer
			CPU_DIFF = 1;
			break;
		}
	case 6:
		{
			//buzzer
			CPU_DIFF = 2;
			break;
		}
	case 7:
		{
			//buzzer
			CPU_DIFF = 3;
			break;
		}

	// CAMBIA DE ESTADO A P1
	case 8:
		{
			//buzzer
			ESTADO = 1;
			break;
		}

	// Cambia color P1 y P2, ponele q son 3, subida
	case 10:
		{
			//buzzer
			if (COLOR_P1 < 3) COLOR_P1++;
			else COLOR_P1 = 0;
			break;
		}
	case 14:
		{
			//buzzer
			if (COLOR_P2 < 3) COLOR_P2++;
			else COLOR_P2 = 0;
			break;
		}
	// Cambia color P1 y P2, bajada
	case 9:
		{
			//buzzer
			if (COLOR_P1 > 0) COLOR_P1--;
			else COLOR_P1 = 2;
			break;
		}

	case 13:
		{
			//buzzer
			if (COLOR_P2 > 0) COLOR_P2--;
			else COLOR_P2 = 2;
			break;
		}

	} //END SWITCH

	teclado_column = 0;
	Teclado_Accionado = 16;

	if (ESTADO = 1)	INICIO_JUEGO();

}

void PLAYER(void)
{
	FILA = 1;
	VERIFICAR_TECLA(teclado_column);


	switch(Teclado_Accionado)
	{
		// Si es 16 entonces no hace nada
		case 16: return;

		// Si es distinto a alguna accion de teclado valida en PLAYER entonces teclado = 16
		default:
		{
			//buzzer
			Teclado_Accionado = 16;
			break;
		}
		// Selecciona COLUMNA 1
		case 0:
		{
			//buzzer
			COLUMNA = 1;
			break;
		}
		// Selecciona COLUMNA 2
		case 1:
		{
			//buzzer
			COLUMNA = 2;
			break;
		}
		// Selecciona COLUMNA 3
		case 2:
		{
			//buzzer
			COLUMNA = 3;
			break;
		}
		// Selecciona COLUMNA 4
		case 3:
		{
			//buzzer
			COLUMNA = 4;
			break;
		}

		// Confirmar Jugada
		case 8:
		{
			//buzzer
			ESTADO = 2;
			break;

		}

		// RESET
		case 12:
		{
			//buzzer
			ESTADO = 5;
			break;
		}
	} // FIN SWITCH

	teclado_column = 0;
	Teclado_Accionado = 16;
}


// ACA VA LA LOGICA DEL JUEGO, DECIDE SI JUGADOR HACE JUGADA VALIDA, SI HACE ANIMACION DE TRANSICION, SI PASA A P2
// SI PASA A CPU O SI VUELVE A P1, O SI FINALIZA EL JUEGO,TODO JUNTO
// aca por ahi si, se introduce una variable matriz de la posicion de las jugadas
void TRANSICION(void)
{
//	color(TURNO_JUGADOR);
	if ( MEMORIA(FILA,COLUMNA) != 0 )
	{
		//JUGADA INVALIDA

		//buzzer
		ESTADO = 1;
		return;
	}
	else
	{
		//JUGADA VALIDADA

		//buzzer
		JUGADA_ACEPTADA();
	}


}

void INICIO_JUEGO(void)
{
	// aca hago algo con los LED para que pase un tiempito
	// es inicio de juego
}

void JUGADA_ACEPTADA(void)
{
    while (1)
    {
        ENCIENDE_LED(FILA, COLUMNA);

        FILA++;

        if ( (MEMORIA(FILA, COLUMNA) != 0) || (FILA > 8) )
        {
        	FILA = 1;
            ESTADO = 4;
            return;
        }

        FILA--;
        APAGA_LED(FILA, COLUMNA);
        FILA++;
    }
}


void END_GAME(void)
{
	//SI ALGUIEN GANA
	for (FILA = 0; FILA < 8; FILA++)
	{
		for (COLUMNA = 0; COLUMNA < 4; COLUMNA++)
		{
			if (MEMORIA(FILA,COLUMNA) != 0)
			{
				if (
						((MEMORIA(FILA+1,COLUMNA)   == MEMORIA(FILA,COLUMNA)) && (MEMORIA(FILA+1,COLUMNA)   == MEMORIA(FILA,COLUMNA))) || // Vertical
						((MEMORIA(FILA-1,COLUMNA-1) == MEMORIA(FILA,COLUMNA)) && (MEMORIA(FILA+1,COLUMNA+1) == MEMORIA(FILA,COLUMNA))) || 		// Diagonal
						((MEMORIA(FILA,COLUMNA-1)   == MEMORIA(FILA,COLUMNA)) && (MEMORIA(FILA,COLUMNA+1)   == MEMORIA(FILA,COLUMNA))) || // Horizontal
						((MEMORIA(FILA+1,COLUMNA-1) == MEMORIA(FILA,COLUMNA)) && (MEMORIA(FILA-1,COLUMNA+1) == MEMORIA(FILA,COLUMNA)))    // Diagonal /
				)
				{
					//buzzer
					GANA = MEMORIA(FILA,COLUMNA);
					ESTADO = 5;
				}
			}
		}
	}

	// SI HAY EMPATE
	if ( (MEMORIA(0,0) != 0) && (MEMORIA(0,1) != 0) && (MEMORIA(0,2) != 0) && (MEMORIA(0,3) != 0) )
	{
		//buzzer
		GANA = 3;
		ESTADO = 5;
	}


	//SI NO ES FIN DE JUEGO
	//Si CPU = 0 entonces cambia de turno entre P1 y P2
	//Si CPU = 1 entonces mantiene el turno pero salta a estado de juego de CPU
	if (CPU == 0)
	{
		TURNO_JUGADOR = !TURNO_JUGADOR;
		ESTADO = 1;
	}
	else ESTADO = 3;


}


void TRANSICION_END_GAME(void)
{
	Teclado_Accionado = 16;

	while (Teclado_Accionado == 16)
	{
		VERIFICAR_TECLA(teclado_column)
					if (GANA == 1)
					{
						//ANIMACION P1
					}
					else if (GANA == 2)
					{
						//ANIMACION P2 O CPU
					}
					else if (GANA == 3)
					{
						//ANIMACION EMPATE
					}
					else  //(GANA == 0) RESET
					{
						//ANIMACION RESET
					}
	}
	ESTADO = 0;
	INICIO_JUEGO();


}

void CPU(void)
{
	TURNO_JUGADOR = !TURNO_JUGADOR;

	// TODAVIA DIFF 1 NO ESTA HABILITADA, ERROR AL VOLVER POR PLAYER 1
	if (CPU_DIFF == 1)
	{
		srand(HAL_GetTick());
		ALEATORIO = (rand() % 4) + 1;

		COLUMNA = ALEATORIO;
	}

	else if (CPU_DIFF == 2)
	{

	}

	TURNO_JUGADOR = !TURNO_JUGADOR;
	//ESTO DEPENDE DE COMO HAGA DIFF 1
	ESTADO = 1;

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
#ifdef USE_FULL_ASSERT
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
