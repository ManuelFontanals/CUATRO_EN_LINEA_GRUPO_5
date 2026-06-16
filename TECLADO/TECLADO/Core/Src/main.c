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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

//ESTO ESTA EN EL "main.h"

//#define FILA_D_Pin GPIO_PIN_12
//#define FILA_D_GPIO_Port GPIOB

//#define FILA_C_Pin GPIO_PIN_13
//#define FILA_C_GPIO_Port GPIOB

//#define FILA_B_Pin GPIO_PIN_14
//#define FILA_B_GPIO_Port GPIOB

//#define FILA_A_Pin GPIO_PIN_15
//#define FILA_A_GPIO_Port GPIOB

//#define COLUMNA_A_Pin GPIO_PIN_8
//#define COLUMNA_A_GPIO_Port GPIOD

//#define COLUMNA_B_Pin GPIO_PIN_9
//#define COLUMNA_B_GPIO_Port GPIOD

//#define COLUMNA_C_Pin GPIO_PIN_10
//#define COLUMNA_C_GPIO_Port GPIOD

//#define COLUMNA_D_Pin GPIO_PIN_11
//#define COLUMNA_D_GPIO_Port GPIOD

//#define LD6_Pin GPIO_PIN_15
//#define LD6_GPIO_Port GPIOD

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint32_t ultimo_rebote = 0;
volatile uint8_t teclado_flag = 0;

//Determina que columna llama a interrupcion
//0 => ya se atendio/ninguna llama
//1 => columna A
//2 => columna B
//3 => columna C
//4 => columna D
uint8_t teclado_column = 0;

// Determina que tecla se apreto
//	0	1	2	3
//	4	5	6	7
//	8	9	10	11
//	12	13	14	15
// 					16 ninguna
uint8_t Teclado_Accionado = 16;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

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
  INICIO_TECLADO();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

	  VERIFICAR_TECLA(teclado_column);

	  if (Teclado_Accionado == 0)
		  HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
	  if (Teclado_Accionado == 1)
		  HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);



    /* USER CODE BEGIN 3 */
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
  HAL_GPIO_WritePin(GPIOB, FILA_D_Pin|FILA_C_Pin|FILA_B_Pin|FILA_A_Pin, GPIO_PIN_RESET);

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

  /*Configure GPIO pins : FILA_D_Pin FILA_C_Pin FILA_B_Pin FILA_A_Pin */
  GPIO_InitStruct.Pin = FILA_D_Pin|FILA_C_Pin|FILA_B_Pin|FILA_A_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : COLUMNA_A_Pin COLUMNA_B_Pin COLUMNA_C_Pin COLUMNA_D_Pin */
  GPIO_InitStruct.Pin = COLUMNA_A_Pin|COLUMNA_B_Pin|COLUMNA_C_Pin|COLUMNA_D_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

//INICIALIZO FILAS EN 1 (SET)
void INICIO_TECLADO(void)
{
	HAL_GPIO_WritePin(FILA_A_GPIO_Port, FILA_A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_SET);
}



// ESTA FUNCION ATIENDE INTERRUPCIONES DE TECLADO
// ES UNICO CALLBACK PARA ""TODAS"" LAS INTERRUPCIONES
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// CODIGO:
	// Antirrebote + flags
	// Al llamarse la interrupcion solo indica que columna fue apretada mediante un flag, dentro del While
	// se llama a la funcion VERIFICAR_TECLA de columna X


	// Esto es antirrebote, si dentro de 20 ms se vuelve a llamar a interrupcion, entonces esa llamada es ignorada
	uint32_t ahora = HAL_GetTick();

	if ((ahora - ultimo_rebote) < 20)
		return;

	ultimo_rebote = ahora;



    // si GPIO_Pin_X entonces FLAG de COLUMNA de X

	if(GPIO_Pin == COLUMNA_A_Pin)
	    {
	        // Interrupción de COL_A
			teclado_column = 1;
	    }
	if(GPIO_Pin == COLUMNA_B_Pin)
	    {
	        // Interrupción de COL_B
			teclado_column = 2;
	    }
	if(GPIO_Pin == COLUMNA_C_Pin)
	    {
	        // Interrupción de COL_C
			teclado_column = 3;
	    }
	if(GPIO_Pin == COLUMNA_D_Pin)
	    {
	        // Interrupción de COL_D
			teclado_column = 4;
	    }
}

// ESTA FUNCION VERIFICA QUE TECLA SE APRETO, DEPENDE DE FLAG DE "X"
// POSIBLE PROBLEMA, WRITE NO LLEGA A CONMUTAR LO SUF RAPIDO, ENTONCES NO LLEGA A LEER (READ) CORRECTAMENTE
// SI ESO OCURRE ENTONCES HAL_DELAY(1) PONELE ANTES DE LA LECTURA
void VERIFICAR_TECLA(uint8_t teclado_column)
{
	// Esta funcion chequea fila por fila que boton de que columna es accionado
	// devuelve en Teclado_Accionado el valor de cual boton fue el apretado
	// OJO: Luego de atender al boton, volver a setear Teclado_Accionado en 16 para evitar doble lectura

	switch(teclado_column){
		case 0: return;

		//CHECKEO SOLO COLUMNA A
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
		}

		//CHECKEO SOLO COLUMNA B
		case 2:
		{
			// Accion sobre MT(0,1) o 1
			HAL_GPIO_WritePin(FILA_A_GPIO_Port, FILA_A_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_B_GPIO_Port, COLUMNA_B_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 1;
				break;
			}
			HAL_GPIO_WritePin(FILA_A_GPIO_Port, FILA_A_Pin, GPIO_PIN_SET);


			// Accion sobre MT(1,1) o 5
			HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_B_GPIO_Port, COLUMNA_B_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 5;
				break;
			}
			HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_SET);


			// Accion sobre MT(2,1) o 9
			HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_B_GPIO_Port, COLUMNA_B_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 9;
				break;
			}
			HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_SET);

			// Accion sobre MT(3,1) o 13
			HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_B_GPIO_Port, COLUMNA_B_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 13;
				break;
			}
			HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_SET);
		}

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
			if (HAL_GPIO_ReadPin(COLUMNA_C_GPIO_Port, COLUMNA_C_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 6;
				break;
			}
			HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_SET);


			// Accion sobre MT(2,2) o 10
			HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_C_GPIO_Port, COLUMNA_C_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 10;
				break;
			}
			HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_SET);

			// Accion sobre MT(3,2) o 14
			HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_C_GPIO_Port, COLUMNA_C_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 14;
				break;
			}
			HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_SET);
		}
		case 4:
		{
			// Accion sobre MT(0,3) o 3
			HAL_GPIO_WritePin(FILA_A_GPIO_Port, FILA_A_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_D_GPIO_Port, COLUMNA_D_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 3;
				break;
			}
			HAL_GPIO_WritePin(FILA_A_GPIO_Port, FILA_A_Pin, GPIO_PIN_SET);


			// Accion sobre MT(1,3) o 7
			HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_D_GPIO_Port, COLUMNA_D_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 7;
				break;
			}
			HAL_GPIO_WritePin(FILA_B_GPIO_Port, FILA_B_Pin, GPIO_PIN_SET);


			// Accion sobre MT(2,3) o 11
			HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_D_GPIO_Port, COLUMNA_D_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 11;
				break;
			}
			HAL_GPIO_WritePin(FILA_C_GPIO_Port, FILA_C_Pin, GPIO_PIN_SET);

			// Accion sobre MT(3,3) o 15
			HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(COLUMNA_D_GPIO_Port, COLUMNA_D_Pin) == GPIO_PIN_RESET){
				Teclado_Accionado = 15;
				break;
			}
			HAL_GPIO_WritePin(FILA_D_GPIO_Port, FILA_D_Pin, GPIO_PIN_SET);
		}

		teclado_column = 0;
		INICIO_TECLADO();

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
