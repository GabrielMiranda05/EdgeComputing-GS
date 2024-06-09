/*
  Circuito da OceanStream:
 * Pino RS do LCD no pino digital 12
 * Pino Enable do LCD no pino digital 11
 * Pino D4 do LCD no pino digital 5
 * Pino D5 do LCD no pino digital 4
 * Pino D6 do LCD no pino digital 3
 * Pino D7 do LCD no pino digital 2
 * Pino R/W do LCD no terra
 * Pino VSS do LCD no terra
 * Pino VCC do LCD no 5V
 * Resistor de 10K:
 * extremidades no +5V e terra
 * wiper no pino VO do LCD (pino 3)

 */

#include <LiquidCrystal.h>

// pinos da interface
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Animação (Ondas)
byte wave[4][8] = {
  { B00000, B00001, B00011, B00110, B01100, B11000, B10000, B00000 }, // Frame 1
  { B00001, B00011, B00110, B01100, B11000, B10000, B00000, B00000 }, // Frame 2
  { B00011, B00110, B01100, B11000, B10000, B00000, B00000, B00000 }, // Frame 3
  { B00110, B01100, B11000, B10000, B00000, B00000, B00000, B00000 }  // Frame 4
};

// Animação (peixinhos)
byte fish[4][8] = {
  { B00100, B01110, B10101, B11111, B01110, B00100, B00000, B00000 }, // Fish 1
  { B00000, B00100, B01110, B10101, B11111, B01110, B00100, B00000 }, // Fish 2
  { B00000, B00000, B00100, B01110, B10101, B11111, B01110, B00100 }, // Fish 3
  { B00000, B00000, B00000, B00100, B01110, B10101, B11111, B01110 }  // Fish 4
};

void setup() {
  // linhas do LCD:
  lcd.begin(16, 2);
  
  // Ondas
  for (int i = 0; i < 4; i++) {
    lcd.createChar(i, wave[i]);
  }
  
  // Peixinhos
  for (int i = 0; i < 4; i++) {
    lcd.createChar(i + 4, fish[i]);
  }
  
  // Animação das ondas e peixinhos
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.write(byte(i % 4));
    lcd.setCursor(i, 1);
    lcd.write(byte((i + 2) % 4 + 4));
    delay(100);
  }
  delay(500);
  
  // Display inicial
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("OceanStream");
  
  // Inicialize o serial
  pinMode(A0, INPUT);
  Serial.begin(9600);
  
  // mensagem de início no serial
  Serial.println("Inicio do sketch - valores do potenciômetro");
}

void loop() {
  // pino A0
  int valor = analogRead(A0);
  float volt = float(valor) / 1023 * 5.0;
  float pHValue = 2.63 * volt - 0.36;

  // monitor serial
  Serial.print("Voltios = ");
  Serial.println(volt);
  Serial.print("pH = ");
  Serial.println(pHValue);

  lcd.setCursor(0, 1);
  
  lcd.print("pH = ");
  lcd.print(pHValue);
  
  delay(600);
}
