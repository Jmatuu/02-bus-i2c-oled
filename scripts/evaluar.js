#!/usr/bin/env node
/**
 * Evaluador pedagógico del reto de escaneo I2C.
 * Uso: node scripts/evaluar.js [1]
 */

const fs = require('fs');
const path = require('path');

const rootDir = path.resolve(__dirname, '..');
const targetArg = process.argv[2] ? process.argv[2].trim() : 'all';
const file = 'bloque_1/src/bloque_1.ino';
const fullPath = path.join(rootDir, file);
const targetBlock = targetArg === 'all' ? null : Number(targetArg);
const c = {
  reset: '\x1b[0m',
  bold: '\x1b[1m',
  green: '\x1b[32m',
  yellow: '\x1b[33m',
  red: '\x1b[31m',
  cyan: '\x1b[36m'
};

if (targetArg !== 'all' && targetBlock !== 1) {
  console.error(`Reto no disponible: ${targetArg}. El único reto es el 1.`);
  process.exit(1);
}

console.log(`\n${c.bold}${c.cyan}======================================================================${c.reset}`);
console.log(`${c.bold}${c.cyan} 🤖 REPORTE PEDAGÓGICO DE ENTREGA — SOPORTE TÉCNICO UETS              ${c.reset}`);
console.log(`${c.bold}${c.cyan}    Semana 02: Protocolo Bus I2C, Scanner y Pantalla OLED SSD1306     ${c.reset}`);
console.log(`${c.bold}${c.cyan}======================================================================${c.reset}\n`);

if (!fs.existsSync(fullPath)) {
  console.error(`  ${c.red}✖ Archivo '${file}' no encontrado.${c.reset}`);
  process.exit(1);
}

const code = fs.readFileSync(fullPath, 'utf8');
const forbiddenTerms = [
  [/c\+\+/i, 'Contiene "C++". Usar "código de Arduino".'],
  [/baymax/i, 'Contiene "Baymax". Usar nomenclatura neutral.'],
  [/socr[aá]t/i, 'Contiene jerga "socrática".']
];
let violations = 0;
forbiddenTerms.forEach(([pattern, message]) => {
  if (pattern.test(code)) {
    console.log(`  ${c.red}✖ ${message}${c.reset}`);
    violations++;
  }
});

const hasWireBegin = /Wire\.begin\s*\(\s*(21|I2C_SDA_PIN)\s*,\s*(22|I2C_SCL_PIN)\s*\)/i.test(code) || /Wire\.begin\s*\(/i.test(code);
const hasWireClock = /Wire\.setClock\s*\(\s*(400000|I2C_CLOCK_SPEED)\s*\)/i.test(code);
const hasTransmission = /Wire\.beginTransmission\s*\(/i.test(code) && /Wire\.endTransmission\s*\(/i.test(code);
const hasAckCheck = /error\s*==\s*0/i.test(code) || /Wire\.endTransmission\s*\(\s*\)\s*==\s*0/i.test(code);
const hasOledAddr = /0x3C/i.test(code) || /OLED_I2C_ADDR/i.test(code);
const hasTodoActive = code.includes('/* ESCRIBE TU CÓDIGO AQUÍ */');
const checks = [
  [hasWireBegin, 'Wire.begin(21, 22) configurado.', 'Falta inicializar el bus con Wire.begin(21, 22).'],
  [hasWireClock, 'Wire.setClock(400000) en Modo Rápido.', 'Sugerencia: Wire.setClock(400000) para 400kHz.'],
  [hasTransmission, 'Transmisión I2C (beginTransmission / endTransmission) activa.', 'Falta beginTransmission() y endTransmission().'],
  [hasAckCheck && hasOledAddr, 'Condición ACK (error == 0) y dirección 0x3C evaluadas.', 'Falta validar el ACK (error == 0) y la dirección 0x3C.']
];
checks.forEach(([passed, successMessage, failureMessage]) => {
  console.log(`  ${passed ? c.green + '✔ ' + successMessage : c.yellow + '✖ ' + failureMessage}${c.reset}`);
});

const complete = hasWireBegin && hasTransmission && hasAckCheck && !hasTodoActive;

console.log(`\n${c.bold}======================================================================${c.reset}`);
console.log(complete
  ? `  ${c.green}${c.bold}✅ ¡RETO 01 COMPLETADO! (1.00 / 1.00 pt)${c.reset}`
  : `  ${c.yellow}${c.bold}ESTADO: EN PROCESO / PENDIENTE (0.00 / 1.00 pt)${c.reset}`);
console.log(`${c.bold}======================================================================\n${c.reset}`);

if (targetBlock === null) {
  console.log(`${c.bold}📋 RESUMEN FORMATIVO:${c.reset}`);
  console.log(`   • Bloques completados al 100%: ${complete ? '1' : '0'} de 1`);
  console.log(`   • Puntaje estimado de Código/Wokwi: ${complete ? '1.00' : '0.00'} / 1.00 pts`);
  console.log(complete
    ? `   ${c.green}🎉 ¡Reto completado! Tu código está listo para PR.${c.reset}`
    : `   ${c.yellow}ℹ️ Completa el reto y entrega tu avance en GitHub.${c.reset}`);
} else {
  console.log(`\n${c.bold}💡 Guía Rápida para Simular Reto 01 en Wokwi:${c.reset}`);
  console.log(`   1. Abre ${c.cyan}bloque_1/diagram.json${c.reset} en VS Code.`);
  console.log(`   2. Presiona ${c.cyan}F1${c.reset} y ejecuta ${c.cyan}Wokwi: Start Simulator${c.reset}.`);
  console.log(`   3. Abre el Monitor Serial (115200 bps) y comprueba que detecte ${c.green}0x3C [OK]${c.reset}.\n`);
}

if (violations > 0) process.exit(1);
process.exit(0);
