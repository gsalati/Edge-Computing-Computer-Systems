/*
  Wokwi Custom SPI Chip example
  Exemplo didático SPI com Arduino
  Baseado em https://wokwi.com/projects/330669951756010068
  See https://docs.wokwi.com/chips-api/getting-started for more info about custom chips
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
