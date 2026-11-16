#pragma once

#include <Arduino.h>

// Inicializa el PWM antes de usar cualquiera de los movimientos.
void inicializarMotores();

// Cada movimiento recibe una velocidad entre 0 y 255.
void adelante(uint8_t velocidad);
void atras(uint8_t velocidad);
void derecha(uint8_t velocidad);
void izquierda(uint8_t velocidad);
void detener();
