void setup() {
  Serial.begin(9600);
  Serial.print("\n\n------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------\n\n");
}

void loop() {
  uint8_t i = 0;
  // Declara e inicializa um array de 5 posições
  uint8_t vet[5] = {5,2,15,255,0};
  
  // Escreve os valores no terminal
  for(i = 0; i < 5; i++){
    Serial.print("indice: ");
    Serial.print(i);
    Serial.print(" | valor vet[");
    Serial.print(i);
    Serial.print("]: ");
    Serial.print(vet[i]);
    Serial.print(" | Endereço na memória: ");
    Serial.println((uintptr_t)&vet[i], HEX);
  }  
  while(1)
  {}

}
