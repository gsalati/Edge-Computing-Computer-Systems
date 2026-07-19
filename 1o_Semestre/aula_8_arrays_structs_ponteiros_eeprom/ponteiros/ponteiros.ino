void setup() {
  Serial.begin(9600);
  Serial.println("\n\n\n--------------------------------");
}

void loop() {
  uint8_t valor = 10;
  uint8_t *ptr = &valor;

  Serial.print("Valor: ");
  Serial.println(valor);
  Serial.print("Endereco: ");
  Serial.println((uintptr_t)ptr, HEX);

  Serial.println("\n\n\n------------ALTERNADO VALOR--------------------");
  Serial.print("Valor: ");
  Serial.println(valor);
  *ptr = 107;
  Serial.print("Valor apos operacao: ");
  Serial.println(valor);
  Serial.print("Endereco: ");
  Serial.println((uintptr_t)ptr, HEX);

  while(1){};

}


