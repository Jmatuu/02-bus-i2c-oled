#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
    OLED_WIDTH,
    OLED_HEIGHT,
    &Wire,
    -1
);

const int RELE_M1_ADELANTE = 25;  // LED rojo
const int RELE_M1_ATRAS    = 26;  // LED naranja
const int RELE_M2_ADELANTE = 27;  // LED azul
const int RELE_M2_ATRAS    = 14;  // LED verde


const int RELE_ON  = HIGH;
const int RELE_OFF = LOW;

bool oledDisponible = false;

void detenerMotores() {
    digitalWrite(RELE_M1_ADELANTE, RELE_OFF);
    digitalWrite(RELE_M1_ATRAS, RELE_OFF);
    digitalWrite(RELE_M2_ADELANTE, RELE_OFF);
    digitalWrite(RELE_M2_ATRAS, RELE_OFF);
}

void mostrarMovimiento(const char* movimiento) {
    Serial.print(F("[MOVIMIENTO] "));
    Serial.println(movimiento);

    if (oledDisponible) {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);

        display.println(F("ROBOT ESP32"));
        display.println(F("----------------"));
        display.print(F("Movimiento: "));
        display.println(movimiento);

        display.display();
    }
}

void adelante() {
    detenerMotores();

    digitalWrite(RELE_M1_ADELANTE, RELE_ON);
    digitalWrite(RELE_M2_ADELANTE, RELE_ON);

    mostrarMovimiento("ADELANTE");
}

void atras() {
    detenerMotores();

    digitalWrite(RELE_M1_ATRAS, RELE_ON);
    digitalWrite(RELE_M2_ATRAS, RELE_ON);

    mostrarMovimiento("ATRAS");
}

void derecha() {
    detenerMotores();

    digitalWrite(RELE_M1_ADELANTE, RELE_ON);
    digitalWrite(RELE_M2_ATRAS, RELE_ON);

    mostrarMovimiento("DERECHA");
}

void izquierda() {
    detenerMotores();

    digitalWrite(RELE_M1_ATRAS, RELE_ON);
    digitalWrite(RELE_M2_ADELANTE, RELE_ON);

    mostrarMovimiento("IZQUIERDA");
}

void detener() {
    detenerMotores();
    mostrarMovimiento("DETENIDO");
}

void mostrarAyuda() {
    Serial.println();
    Serial.println(F("===== CONTROL DEL ROBOT ====="));
    Serial.println(F("W = Adelante (rojo + azul)"));
    Serial.println(F("S = Atras (naranja + verde)"));
    Serial.println(F("D = Derecha (rojo + verde)"));
    Serial.println(F("A = Izquierda (naranja + azul)"));
    Serial.println(F("X = Detener"));
    Serial.println(F("============================="));
}

void setup() {
    Serial.begin(115200);

    pinMode(RELE_M1_ADELANTE, OUTPUT);
    pinMode(RELE_M1_ATRAS, OUTPUT);
    pinMode(RELE_M2_ADELANTE, OUTPUT);
    pinMode(RELE_M2_ATRAS, OUTPUT);

    // Apagar todo antes de iniciar
    detenerMotores();

    // Iniciar I2C para la OLED
    Wire.begin(21, 22);

    if (display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        oledDisponible = true;
        mostrarMovimiento("LISTO");
    } else {
        Serial.println(F("[ERROR] No se pudo iniciar la OLED"));
    }

    mostrarAyuda();
}

void loop() {
    if (Serial.available() > 0) {
        char comando = (char)Serial.read();

        if (comando >= 'a' && comando <= 'z') {
            comando = comando - ('a' - 'A');
        }

        switch (comando) {
            case 'W':
                adelante();
                break;

            case 'S':
                atras();
                break;

            case 'D':
                derecha();
                break;

            case 'A':
                izquierda();
                break;

            case 'X':
                detener();
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
    }
}