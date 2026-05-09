#include <EEPROM.h>
void setup() {
  Serial.begin(9600);
  Serial.println("\n\n---------------------\n");
  uint8_t value = 15;
  EEPROM.write(0x0F, value);

  Serial.print("Valor: ");
  Serial.print(value);
  Serial.println(" escrito no endereço 0x0F");

}

void loop() {
  // put your main code here, to run repeatedly:

}
