
#include "motores.h"

#include "oled_ui.h"
#include "pwm_config.h"

// Escribe el ciclo PWM de los cuatro canales.
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

// Giro a la derecha: el motor derecho va más lento.
void derecha(uint8_t velocidad) {
    uint8_t velocidadInterior = velocidad / 2;
    aplicarPWM(velocidad, 0, velocidadInterior, 0);
    mostrarMovimiento("DERECHA", velocidad);
}

// Giro a la izquierda: el motor izquierdo va más lento.
void izquierda(uint8_t velocidad) {
    uint8_t velocidadInterior = velocidad / 2;
    aplicarPWM(velocidadInterior, 0, velocidad, 0);
    mostrarMovimiento("IZQUIERDA", velocidad);
}

void detener() {
    aplicarPWM(0, 0, 0, 0);
    mostrarMovimiento("DETENIDO", 0);
}
