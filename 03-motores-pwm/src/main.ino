
#include <Arduino.h>

#include "motores.h"
#include "oled_ui.h"

// Velocidad seleccionada.
uint8_t velocidad = 170;
char movimientoActual = 'X';

// Control del giro temporal.
bool giroEnCurso = false;
unsigned long inicioGiro = 0;
const unsigned long DURACION_GIRO = 600;

void setup() {
    Serial.begin(115200);
    inicializarMotores();
    inicializarOLED();
    mostrarMovimiento("LISTO", velocidad);

    Serial.println();
    Serial.println(F("===== CONTROL DE MOTORES PWM ====="));
    Serial.println(F("W = Adelante | S = Atras"));
    Serial.println(F("D = Giro derecha | A = Giro izquierda"));
    Serial.println(F("X = Detener"));
    Serial.println(F("+ = Subir velocidad | - = Bajar velocidad"));
    Serial.println(F("1 = Baja (85) | 2 = Media (170) | 3 = Alta (255)"));
    Serial.println(F("Giro automatico: 600 ms"));
    Serial.println(F("=================================="));
}

void loop() {
    if (Serial.available() > 0) {
        char comando = static_cast<char>(Serial.read());

        if (comando >= 'a' && comando <= 'z') {
            comando = static_cast<char>(comando - ('a' - 'A'));
        }

        bool actualizarVelocidad = false;

        switch (comando) {
            case 'W':
                giroEnCurso = false;
                movimientoActual = 'W';
                adelante(velocidad);
                break;

            case 'S':
                giroEnCurso = false;
                movimientoActual = 'S';
                atras(velocidad);
                break;

            case 'D':
                movimientoActual = 'D';
                giroEnCurso = true;
                inicioGiro = millis();
                derecha(velocidad);
                break;

            case 'A':
                movimientoActual = 'A';
                giroEnCurso = true;
                inicioGiro = millis();
                izquierda(velocidad);
                break;

            case 'X':
                giroEnCurso = false;
                movimientoActual = 'X';
                detener();
                break;

            case '+':
                velocidad = velocidad <= 230 ? velocidad + 25 : 255;
                actualizarVelocidad = true;
                break;

            case '-':
                velocidad = velocidad >= 25 ? velocidad - 25 : 0;
                actualizarVelocidad = true;
                break;

            case '1':
                velocidad = 85;
                actualizarVelocidad = true;
                break;

            case '2':
                velocidad = 170;
                actualizarVelocidad = true;
                break;

            case '3':
                velocidad = 255;
                actualizarVelocidad = true;
                break;

            case '\r':
            case '\n':
            case ' ':
                break;

            default:
                Serial.print(F("[ERROR] Comando desconocido: "));
                Serial.println(comando);
                break;
        }

        // Actualiza la velocidad sin cancelar el giro.
        if (actualizarVelocidad) {
            Serial.print(F("Velocidad seleccionada: "));
            Serial.print(velocidad);
            Serial.println(F("/255"));

            switch (movimientoActual) {
                case 'W':
                    adelante(velocidad);
                    break;
                case 'S':
                    atras(velocidad);
                    break;
                case 'D':
                    derecha(velocidad);
                    break;
                case 'A':
                    izquierda(velocidad);
                    break;
                default:
                    mostrarMovimiento("DETENIDO", 0);
                    break;
            }
        }
    }

     // Al terminar el giro, el robot queda detenido.
    if (giroEnCurso && millis() - inicioGiro >= DURACION_GIRO) {
    giroEnCurso = false;
    movimientoActual = 'X';

    detener();

    Serial.println(F("Giro terminado: robot detenido."));
}
}
