#ifndef LEDS_H_
#define LEDS_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

void comunicacionled(uint32_t *L, uint32_t *vectorled);
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim4);
void ENVIODMA(uint32_t *vecled);


#endif
