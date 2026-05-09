// Exemplo de strings em C no Arduino

// Podemos definir a string com um tamanho "arbitrário" grande o suficiente para conter o texto desejado
// Devemos sempre contar o caractere de terminação no tamanho do array
// Ou seja, a string mensagem consegue armazenar até 124 caracteres
char mensagem[125] = "Ola Fiap!";

void setup() {
  Serial.begin(9600);

  // Imprime a string completa
  Serial.println(mensagem);

  // Mostra cada caractere separadamente
  Serial.println("Caracteres da string:");
  // Note a utilizaççao do caractere de terminação ao percorrer a string
  for (int i = 0; mensagem[i] != '\0'; i++) {
    Serial.print("Posicao ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(mensagem[i]);
  }

  // Calcula tamanho da string
  int tamanho = strlen(mensagem);

  Serial.print("Tamanho da string: ");
  Serial.println(tamanho);
}

void loop() {

}