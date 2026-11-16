# Proyecto 03: Control de motores con PWM y pantalla OLED

Proyecto desarrollado con una **ESP32** para practicar el control de velocidad y dirección de motores mediante señales PWM. La interfaz OLED muestra el movimiento seleccionado y el valor de velocidad aplicado.

La simulación de Wokwi utiliza **cuatro LEDs como indicadores de las salidas** de los motores. Permite comprobar la lógica de control y las señales, pero no representa el movimiento físico de motores ni incluye un módulo L293D conectado.

## Objetivos

- Configurar cuatro canales PWM independientes en la ESP32.
- Controlar avance, retroceso y giros diferenciados.
- Ajustar la velocidad mediante comandos enviados por el monitor serial.
- Realizar giros temporizados de 600 ms sin bloquear el programa.
- Mostrar el estado del sistema mediante una pantalla OLED SSD1306.

## Componentes y herramientas

| Elemento | Uso |
| --- | --- |
| ESP32 DevKit | Microcontrolador principal |
| Pantalla OLED SSD1306 128×64 | Visualización del movimiento y PWM |
| 4 LEDs | Indicadores de las cuatro señales de salida |
| 4 resistencias de 330 Ω | Limitación de corriente para los LEDs |
| Wokwi | Simulación del circuito |
| PlatformIO | Compilación y carga del programa |

## Conexiones

### Salidas PWM

| Señal | GPIO ESP32 | Canal PWM | Indicador en Wokwi |
| --- | ---: | ---: | --- |
| Motor 1 - adelante | 25
