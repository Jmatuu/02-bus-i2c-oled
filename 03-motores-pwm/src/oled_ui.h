#pragma once

#include <Arduino.h>

// Inicia I2C en los pines indicados y la pantalla SSD1306.
bool inicializarOLED();

// Muestra el movimiento actual y el valor PWM aplicado.
void mostrarMovimiento(const char* movimiento, uint8_t velocidad);
