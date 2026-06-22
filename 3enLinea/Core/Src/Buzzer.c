#include "stm32f4xx_hal.h"
#include "Buzzer.h"
#define TENCENDIDO 200
void buzz(void){
 uint16_t ciclomaximo = TIM3->ARR;
 TIM3->CCR1 = ciclomaximo;
 HAL_Delay(TENCENDIDO);
 TIM3->CCR1 = 0;
 HAL_Delay(TENCENDIDO);
}
