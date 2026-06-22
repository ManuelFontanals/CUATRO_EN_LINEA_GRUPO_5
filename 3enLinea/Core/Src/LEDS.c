#include "stm32f4xx_hal.h"
#include "LEDS.h"

extern TIM_HandleTypeDef htim4;
volatile uint8_t dma_listo = 0;

void comunicacionled(uint32_t *L, uint32_t *vectorled){
	volatile uint32_t indice = 0;
	for (int i=0; i<32; i++){
		for (int j=23; j>=0; j--){
			if ((L[i]>> j )&1){
				vectorled[indice] = 31;

			}
			else{
				vectorled[indice] = 16;
			}
			indice++;
		}
	}
	for (int i=0; i<50; i++){
		vectorled[indice] = 0;
		indice++;
	}
}



void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim4)
{
	if (htim4->Instance == TIM4)
        dma_listo = 1;
}

void ENVIODMA(uint32_t *vecled)
{
    dma_listo = 0;
    HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_1, (uint32_t *)vecled, 818);

    while (dma_listo == 0)
    {
    }

//    HAL_TIM_PWM_Stop_DMA(&htim4, TIM_CHANNEL_1);
}
