# Proyecto 03: Motores PWM y OLED

Proyecto para ESP32 con cuatro LEDs que representan las salidas de los motores.
Cada LED se controla con PWM; no se usan relés.

## Archivos

- `src/main.ino`: inicia los módulos y procesa los comandos del monitor Serial.
- `src/pwm_config.h` y `src/pwm_config.cpp`: configura cuatro canales PWM a 1000 Hz y 8 bits.
- `src/motores.h` y `src/motores.cpp`: implementa adelante, atras, derecha, izquierda y detener.
- `src/oled_ui.h` y `src/oled_ui.cpp`: inicia la OLED I2C y muestra movimiento y velocidad.
- `diagram.json`: circuito Wokwi con OLED y cuatro LEDs con resistencias de 330 ohm.

## Uso

Compila desde esta carpeta con `pio run`. Abre la simulación con Wokwi o
conecta el ESP32 y ejecuta `pio device monitor --baud 115200`.

Usa `W`, `S`, `D`, `A` para moverte; `X` para detener; `+` y `-` para ajustar
la velocidad; y `1`, `2`, `3` para seleccionar baja, media y alta.
