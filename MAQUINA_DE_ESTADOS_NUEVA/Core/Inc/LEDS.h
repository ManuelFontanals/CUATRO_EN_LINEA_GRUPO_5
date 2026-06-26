
#ifndef LEDS_H_
#define LEDS_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

void comunicacionled(uint32_t *L, uint32_t *vectorled);
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim4);
void ENVIODMA(uint32_t *vecled);
void armadoled(uint8_t ESTADO, bool TURNO_JUGADOR, uint32_t *L, uint8_t COLOR_P2, uint8_t COLOR_P1, uint8_t CPU_DIFF, bool CPU, uint8_t COLUMNA, uint8_t M[8][4]);


#endif
