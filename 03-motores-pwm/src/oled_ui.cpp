#include "oled_ui.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

namespace {
constexpr uint8_t OLED_ANCHO = 128;
constexpr uint8_t OLED_ALTO = 64;
constexpr uint8_t OLED_DIRECCION = 0x3C;
constexpr int8_t OLED_PIN_RESET = -1;

Adafruit_SSD1306 pantalla(OLED_ANCHO, OLED_ALTO, &Wire, OLED_PIN_RESET);
bool oledDisponible = false;
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
    pantalla.setCursor(0, 0);
    pantalla.println(F("ROBOT ESP32"));
    pantalla.println(F("----------------"));
    pantalla.print(F("Movimiento: "));
    pantalla.println(movimiento);
    pantalla.print(F("Velocidad: "));
    pantalla.print(velocidad);
    pantalla.println(F("/255"));
    pantalla.display();
}
