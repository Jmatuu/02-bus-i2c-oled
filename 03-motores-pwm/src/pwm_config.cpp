#include "pwm_config.h"

// Enlaza cada pin a un canal independiente del ESP32.
void configurarPWM() {
    ledcSetup(PWM_CANAL_M1_ADELANTE, PWM_FRECUENCIA, PWM_RESOLUCION);
    ledcSetup(PWM_CANAL_M1_ATRAS, PWM_FRECUENCIA, PWM_RESOLUCION);
    ledcSetup(PWM_CANAL_M2_ADELANTE, PWM_FRECUENCIA, PWM_RESOLUCION);
    ledcSetup(PWM_CANAL_M2_ATRAS, PWM_FRECUENCIA, PWM_RESOLUCION);

    ledcAttachPin(PIN_M1_ADELANTE, PWM_CANAL_M1_ADELANTE);
    ledcAttachPin(PIN_M1_ATRAS, PWM_CANAL_M1_ATRAS);
    ledcAttachPin(PIN_M2_ADELANTE, PWM_CANAL_M2_ADELANTE);
    ledcAttachPin(PIN_M2_ATRAS, PWM_CANAL_M2_ATRAS);

    ledcWrite(PWM_CANAL_M1_ADELANTE, 0);
    ledcWrite(PWM_CANAL_M1_ATRAS, 0);
    ledcWrite(PWM_CANAL_M2_ADELANTE, 0);
    ledcWrite(PWM_CANAL_M2_ATRAS, 0);
}
