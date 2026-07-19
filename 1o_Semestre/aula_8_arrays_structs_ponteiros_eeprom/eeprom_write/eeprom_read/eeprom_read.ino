#include <EEPROM.h>
void setup() {
  Serial.begin(9600);
  Serial.println("\n\n---------------------\n");
  uint8_t value;
  value = EEPROM.read(0x0F);

  Serial.print("Valor: ");
  Serial.print(value);
  Serial.println(" lido no endereço 0x0F");

}

void loop() {
  // put your main code here, to run repeatedly:

}
