# ⚡ Starter-Kit: Taller Práctico Semana 02 — Soporte Técnico (3° BGU UETS)
### Protocolo Bus I2C, Scanner de Hardware y Telemetría en Pantalla OLED SSD1306

Bienvenido al taller práctico de la Semana 02. En este laboratorio desarrollarás el firmware en código de Arduino para dominar la comunicación I2C y la telemetría gráfica en pantalla OLED SSD1306 del **sistema embebido ESP32**.

El taller incluye el siguiente reto práctico:

* 🟢 **Bloque 1:** Escáner de Direcciones de Hardware I2C (Detección de `0x3C`).

---

## 📺 Guía Maestra Técnica en Vivo (Cloudflare Edge)

[![Ver Guía Maestra en Vivo](https://img.shields.io/badge/Guía_Técnica-Ver_en_Línea-E07A5F?style=for-the-badge&logo=cloudflare)](https://uets-st-portal.vgmiltonisaac.workers.dev/02-bus-i2c-oled/)

👉 **[Abrir Guía Maestra en el Portal Oficial (Cloudflare Edge)](https://uets-st-portal.vgmiltonisaac.workers.dev/02-bus-i2c-oled/)**  
👉 **[Ver Portal Curricular de Soporte Técnico](https://uets-st-portal.vgmiltonisaac.workers.dev/)**

---

## ❄️ Setup Diario Anti-Deep Freeze (Obligatorio en Laboratorio)

Dado que las computadoras del laboratorio se reinician a su estado base al apagarse, configura tu identidad de Git antes de empezar:

```bash
git config --global user.name "TU_USUARIO_GITHUB"
git config --global user.email "tu_correo_registrado@ejemplo.com"
```

### Flujo de Trabajo en Git:
1. Haz **Fork** del repositorio docente a tu cuenta personal de GitHub.
2. Clona tu propio fork en la máquina local:
   ```bash
   git clone https://github.com/MI_USUARIO_GITHUB/02-bus-i2c-oled.git
   cd 02-bus-i2c-oled
   ```
3. Crea tu rama de entrega personal:
   ```bash
   git checkout -b entrega/nombre-apellido
   ```

---

## 📖 Material de Apoyo Estudiantil
* 📘 **[Cheatsheet del Estudiante (Analogías & Código de Arduino)](CHEATSHEET_ESTUDIANTE.md):** Hoja de trucos con las analogías del megáfono, la memoria buffer RAM y preguntas clave de auto-diagnóstico.

---

## 📁 Arquitectura del Repositorio

```text
02-bus-i2c-oled/
├── 02-bus-i2c-oled.code-workspace  <-- Espacio de trabajo oficial para VS Code
├── CHEATSHEET_ESTUDIANTE.md        <-- Hoja de trucos y preguntas clave
├── LICENSE                         <-- Licencia MIT oficial UETS
├── README.md                       <-- Guía de inicio y protocolo de aula
└── bloque_1/                       <-- 🟢 Reto 01: Escáner I2C
    ├── diagram.json                <-- Circuito esquemático Wokwi
    ├── platformio.ini              <-- Entorno de compilación ESP32
    ├── wokwi.toml                  <-- Configuración del simulador
    └── src/bloque_1.ino            <-- Código de Arduino con // TODO:
```

---

## 🚀 Flujo de Trabajo en VS Code & Wokwi

> [!TIP]
> **Abre el archivo \`02-bus-i2c-oled.code-workspace\` en VS Code:**  
> Ve a **Archivo ➔ Abrir espacio de trabajo desde archivo...** y selecciona `02-bus-i2c-oled.code-workspace` (o haz doble clic sobre él en Windows). Esto cargará el bloque como proyecto independiente en PlatformIO.

> [!IMPORTANT]
> **¿Por qué Wokwi necesita compilación previa con PlatformIO?**  
> En la extensión de VS Code, Wokwi **no compila código por sí mismo**; es un simulador de hardware que ejecuta el archivo binario (`.pio/build/esp32/firmware.bin`) generado por el compilador de PlatformIO.  
> Si pulsas *Play* en Wokwi antes de compilar, el simulador reportará que no encuentra el firmware. El orden correcto siempre es:
> 1. **Escribir el código:** Edita `bloque_1/src/bloque_1.ino` y completa los `// TODO:`.
> 2. **Compilar con PlatformIO:** Haz clic en el visto **Build (✔)** en la barra azul inferior (o en el icono de la hormiga 🐜 ➔ **PROJECT TASKS** ➔ **esp32** ➔ **Build**). Verifica que la terminal muestre `[SUCCESS]`.
> 3. **Simular en Wokwi:** Abre `bloque_1/diagram.json` y pulsa el botón verde **Start Simulation (Play)** (o presiona `F1` ➔ `Wokwi: Start Simulator`).
> 4. **Verificar Salidas:** Abre el **Serial Monitor** (115200 bps) o mira la pantalla OLED encenderse en la simulación.
> 5. **Entrega en GitHub:** Guarda tus commits con formato semántico y abre tu Pull Request comparando tu rama `entrega/nombre-apellido` contra la rama `base: main` del docente.

---

## 🧪 Suite CLI de Comandos del Taller (\`pnpm\` / \`npm\`)

Este repositorio incluye un **Evaluador Pedagógico Integrado** que revisa tu código en 3 segundos y te muestra qué conceptos de hardware ya dominas y qué detalles te faltan por completar:

```bash
# Probar el reto (con retroalimentación pedagógica y guía de Wokwi):
pnpm run start:01   # 🟢 Reto 01: Escáner de Hardware I2C (0x3C)

# Probar el reto (Reporte formativo y Entrega Parcial Salesiana):
pnpm test

# Verificar que no existan errores estructurales ni de sintaxis:
pnpm run check
```

### 🤖 En GitHub (Automático en cada Pull Request):
Al abrir o actualizar tu Pull Request, GitHub Actions ejecuta el evaluador y muestra tu reporte de avance en los logs del Check Verde ✅.

---

## ⏱️ Límites de Duración de Video & Penalizaciones

* **Short de Anticipación ($\le 60\text{ s}$):** Límite estricto de 60 segundos (margen de gracia hasta 65s). Penalización automática de **-0.50 pts** si excede los 65 segundos.
* **Screencast Demostrativo (3 a 4 min):** Límite máximo absoluto de **5:00 minutos**. La revisión docente se detiene en 5:00; videos de 5:01 en adelante tienen **-1.00 pt de penalización**.

---

## 🕊️ Directiva de Entrega Parcial Salesiana ("¡Nunca te quedes con 0!")

Si la clase concluye y no alcanzaste a terminar el bloque:
1. Haz commit de tu avance: `git commit -m "feat: avance parcial del reto I2C"`
2. Sube los cambios a tu fork y abre el Pull Request.
3. Graba tu video screencast explicando con honestidad lo que lograste implementar y qué aprendiste.
4. **Beneficio:** Aseguras los **5.00 puntos de la sustentación oral** más la nota proporcional del circuito completado.
