#include "motores.h"

#include "oled_ui.h"
#include "pwm_config.h"

// Escribe el ciclo PWM de los cuatro canales en el orden de los pines.
static void aplicarPWM(uint8_t m1Adelante, uint8_t m1Atras,
                       uint8_t m2Adelante, uint8_t m2Atras) {
    ledcWrite(PWM_CANAL_M1_ADELANTE, m1Adelante);
    ledcWrite(PWM_CANAL_M1_ATRAS, m1Atras);
    ledcWrite(PWM_CANAL_M2_ADELANTE, m2Adelante);
    ledcWrite(PWM_CANAL_M2_ATRAS, m2Atras);
}

void inicializarMotores() {
    configurarPWM();
}

void adelante(uint8_t velocidad) {
    aplicarPWM(velocidad, 0, velocidad, 0);
    mostrarMovimiento("ADELANTE", velocidad);
}

void atras(uint8_t velocidad) {
    aplicarPWM(0, velocidad, 0, velocidad);
    mostrarMovimiento("ATRAS", velocidad);
}

void derecha(uint8_t velocidad) {
    aplicarPWM(velocidad, 0, 0, velocidad);
    mostrarMovimiento("DERECHA", velocidad);
}

void izquierda(uint8_t velocidad) {
    aplicarPWM(0, velocidad, velocidad, 0);
    mostrarMovimiento("IZQUIERDA", velocidad);
}

void detener() {
    aplicarPWM(0, 0, 0, 0);
    mostrarMovimiento("DETENIDO", 0);
}
