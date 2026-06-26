
#ifndef TECLADO
#define TECLADO

#include "main.h"
#include <stdbool.h>

#define UMBRAL 10

typedef struct
{
    GPIO_PinState ultimo_raw;
    GPIO_PinState estado_filtrado;
    uint8_t contador;
} Debounce_t;

extern volatile uint8_t LLAMA_COL;
extern uint8_t contador_estable;
extern volatile uint8_t Teclado_Accionado;
extern bool INICIO_ESTADO_TECLADO;

extern Debounce_t btn1;
extern Debounce_t btn2;
extern Debounce_t btn3;
extern Debounce_t btn4;

bool VerificarBoton(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, Debounce_t *btn);
void INICIO_TECLADO(void);
void TecladoPresiona(void);

#endif
