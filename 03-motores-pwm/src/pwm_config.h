#pragma once

#include <Arduino.h>

// Configuracion comun del PWM y asignacion de canales a los cuatro pines.
constexpr uint32_t PWM_FRECUENCIA = 1000;
constexpr uint8_t PWM_RESOLUCION = 8;
constexpr uint8_t PWM_CANAL_M1_ADELANTE = 0;
constexpr uint8_t PWM_CANAL_M1_ATRAS = 1;
constexpr uint8_t PWM_CANAL_M2_ADELANTE = 2;
constexpr uint8_t PWM_CANAL_M2_ATRAS = 3;

constexpr uint8_t PIN_M1_ADELANTE = 25;
constexpr uint8_t PIN_M1_ATRAS = 26;
constexpr uint8_t PIN_M2_ADELANTE = 27;
constexpr uint8_t PIN_M2_ATRAS = 14;

// Prepara los cuatro canales PWM y deja los motores apagados.
void configurarPWM();
