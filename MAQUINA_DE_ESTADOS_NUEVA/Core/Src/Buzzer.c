#include "stm32f4xx_hal.h"
#include "Buzzer.h"
#define TENCENDIDO 200

void buzzvalida(void){											//Funciones de buzzer, todas con mismo funcionamiento
 TIM3->ARR = 4;
 uint16_t ciclomaximo = TIM3->ARR;
 TIM3->CCR1 = ciclomaximo;
 HAL_Delay(TENCENDIDO);
 TIM3->CCR1 = 0;
 HAL_Delay(TENCENDIDO);
 TIM3->CCR1 = ciclomaximo;
 HAL_Delay(TENCENDIDO);
 TIM3->CCR1 = 0;
 TIM3->ARR = 3;
}

void buzzinvalida(void){
 TIM3->ARR = 18;
 uint16_t ciclomaximo = TIM3->ARR;
 TIM3->CCR1 = ciclomaximo;
 HAL_Delay(TENCENDIDO);
 TIM3->CCR1 = 0;
 HAL_Delay(TENCENDIDO);
 TIM3->CCR1 = ciclomaximo;
 HAL_Delay(TENCENDIDO);
 TIM3->CCR1 = 0;
 TIM3->ARR = 3;
}

void buzzempate(void){
 TIM3->ARR = 5;
 uint16_t ciclomaximo = TIM3->ARR;
 TIM3->CCR1 = ciclomaximo;
 HAL_Delay(TENCENDIDO);
 TIM3->CCR1 = 0;
 HAL_Delay(TENCENDIDO);
 TIM3->CCR1 = ciclomaximo;
 HAL_Delay(TENCENDIDO);
 TIM3->CCR1 = 0;
 HAL_Delay(TENCENDIDO);
 TIM3->ARR = 18;
 TIM3->CCR1 = ciclomaximo;
 HAL_Delay(TENCENDIDO);
 TIM3->CCR1 = 0;
 HAL_Delay(TENCENDIDO);
 TIM3->ARR = 10;
 TIM3->CCR1 = ciclomaximo;
 HAL_Delay(TENCENDIDO);
 TIM3->CCR1 = 0;
 HAL_Delay(TENCENDIDO);
 TIM3->ARR = 22;
 TIM3->CCR1 = ciclomaximo;
 HAL_Delay(TENCENDIDO);
 TIM3->CCR1 = 0;
 HAL_Delay(TENCENDIDO);
 TIM3->ARR = 15;
 TIM3->CCR1 = ciclomaximo;
 HAL_Delay(TENCENDIDO);
 TIM3->CCR1 = 0;
 TIM3->ARR = 3;
}

void buzzvictoria(void){
 uint16_t ciclomaximo = TIM3->ARR;
   TIM3->ARR = 4;
   TIM3->CCR1 = ciclomaximo;
   HAL_Delay(TENCENDIDO);
   TIM3->CCR1 = 0;
   HAL_Delay(TENCENDIDO);
   TIM3->ARR = 5;
   TIM3->CCR1 = ciclomaximo;
   HAL_Delay(TENCENDIDO);
   TIM3->CCR1 = 0;
   HAL_Delay(TENCENDIDO);
   TIM3->ARR = 6;
   TIM3->CCR1 = ciclomaximo;
   HAL_Delay(TENCENDIDO);
   TIM3->CCR1 = 0;
   HAL_Delay(TENCENDIDO);
   TIM3->ARR = 7;
   TIM3->CCR1 = ciclomaximo;
   HAL_Delay(TENCENDIDO);
   TIM3->CCR1 = 0;
   HAL_Delay(TENCENDIDO);
   TIM3->ARR = 6;
   TIM3->CCR1 = ciclomaximo;
   HAL_Delay(TENCENDIDO);
   TIM3->CCR1 = 0;
   HAL_Delay(TENCENDIDO);
   TIM3->ARR = 5;
   TIM3->CCR1 = ciclomaximo;
   HAL_Delay(TENCENDIDO);
   TIM3->CCR1 = 0;
   HAL_Delay(TENCENDIDO);
   TIM3->ARR = 4;
   TIM3->CCR1 = ciclomaximo;
   HAL_Delay(TENCENDIDO);
   TIM3->CCR1 = 0;
   TIM3->ARR = 3;

}

void buzzturno(void){
 TIM3->ARR = 8;
 uint16_t ciclomaximo = TIM3->ARR;
 TIM3->CCR1 = ciclomaximo;
 HAL_Delay(500);
 TIM3->CCR1 = 0;
 TIM3->ARR = 3;
}
