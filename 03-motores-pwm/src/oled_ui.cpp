
#include "oled_ui.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>

namespace {
constexpr uint8_t OLED_ANCHO = 128;
constexpr uint8_t OLED_ALTO = 64;
constexpr uint8_t OLED_DIRECCION = 0x3C;
constexpr int8_t OLED_PIN_RESET = -1;

Adafruit_SSD1306 pantalla(OLED_ANCHO, OLED_ALTO, &Wire, OLED_PIN_RESET);
bool oledDisponible = false;

// Dibuja una flecha hacia arriba.
void dibujarArriba() {
    pantalla.drawLine(100, 48, 100, 22, SSD1306_WHITE);
    pantalla.fillTriangle(100, 12, 89, 27, 111, 27, SSD1306_WHITE);
}

// Dibuja una flecha hacia abajo.
void dibujarAbajo() {
    pantalla.drawLine(100, 12, 100, 38, SSD1306_WHITE);
    pantalla.fillTriangle(100, 48, 89, 33, 111, 33, SSD1306_WHITE);
}

// Dibuja una flecha hacia la derecha.
void dibujarDerecha() {
    pantalla.drawLine(85, 30, 108, 30, SSD1306_WHITE);
    pantalla.fillTriangle(118, 30, 103, 19, 103, 41, SSD1306_WHITE);
}

// Dibuja una flecha hacia la izquierda.
void dibujarIzquierda() {
    pantalla.drawLine(95, 30, 118, 30, SSD1306_WHITE);
    pantalla.fillTriangle(85, 30, 100, 19, 100, 41, SSD1306_WHITE);
}

// Dibuja un símbolo de detenido.
void dibujarDetenido() {
    pantalla.fillRect(90, 20, 20, 20, SSD1306_WHITE);
}
}

// La OLED comparte el bus I2C iniciado en GPIO 21 y GPIO 22.
bool inicializarOLED() {
    Wire.begin(21, 22);
    oledDisponible = pantalla.begin(SSD1306_SWITCHCAPVCC, OLED_DIRECCION);

    if (!oledDisponible) {
        Serial.println(F("[ERROR] No se pudo iniciar la OLED"));
    }

    return oledDisponible;
}

void mostrarMovimiento(const char* movimiento, uint8_t velocidad) {
    if (!oledDisponible) {
        return;
    }

    pantalla.clearDisplay();
    pantalla.setTextSize(1);
    pantalla.setTextColor(SSD1306_WHITE);

    // Encabezado.
    pantalla.setCursor(0, 0);
    pantalla.println(F("ROBOT ESP32"));
    pantalla.drawLine(0, 11, 127, 11, SSD1306_WHITE);

    // Información del movimiento.
    pantalla.setCursor(0, 20);
    pantalla.println(F("MOVIMIENTO:"));

    pantalla.setCursor(0, 32);
    pantalla.println(movimiento);

    pantalla.setCursor(0, 49);
    pantalla.print(F("PWM: "));
    pantalla.print(velocidad);
    pantalla.println(F("/255"));

    // Indicador gráfico según el movimiento.
    if (strcmp(movimiento, "ADELANTE") == 0) {
        dibujarArriba();
    } else if (strcmp(movimiento, "ATRAS") == 0) {
        dibujarAbajo();
    } else if (strcmp(movimiento, "DERECHA") == 0) {
        dibujarDerecha();
    } else if (strcmp(movimiento, "IZQUIERDA") == 0) {
        dibujarIzquierda();
    } else {
        dibujarDetenido();
    }

    pantalla.display();
}
