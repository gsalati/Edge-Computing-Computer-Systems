/**
 * @file spi_example.ino
 * @author Guilherme Salati (profguilherme.salati@fiap.com.br)
 * @brief 
 * Exemplo de utilização de SPI com Arduino UNO.
 * Link para simulação: https://wokwi.com/projects/470821841496905729
 * @version 0.1
 * @date 2026-08-01
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <SPI.h>

#define CS 10

void setup() {
  char buffer[] = "Hello Fiap";

  Serial.begin(9600);
  pinMode(CS, OUTPUT);

  // SPI Transaction: sends the contents of buffer, and overwrites it with the received data.
  digitalWrite(CS, LOW);
  SPI.begin();
  SPI.transfer(buffer, strlen(buffer)+1);
  SPI.end();
  digitalWrite(CS, HIGH);

  Serial.println("Data received from SPI device:");
  Serial.println(buffer);
}

void loop() {
}
