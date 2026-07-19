void setup() {
  Serial.begin(9600);
  Serial.println("\n\n\n--------------------------------");

}
static void imprimeArray(uint8_t *vet, uint8_t tamanho);
static void somaUmArray(uint8_t *vet, uint8_t tamanho);

void loop() {
  uint8_t meuArray[3] = {10,11,12};

  Serial.print("Enderedo primeiro elemento: ");
  Serial.println((uintptr_t)&meuArray[0], HEX);
  Serial.print("Valor da variavel meuArray: ");
  Serial.println((uintptr_t)meuArray, HEX);

  Serial.println("\n\n-------- ACESSANDO O VALOR --------- \n");
  Serial.print("Primeiro elemento de meuArray: ");
  Serial.println(*meuArray);

  Serial.println("\n\n-------- ACESSANDO OUTROS VALORES --------- \n");
  Serial.print("Segundo elemento de meuArray: ");
  Serial.println(*meuArray+1);
  Serial.print("Terceiro elemento de meuArray: ");
  Serial.println(*meuArray+2);

  Serial.println("\n\n-------- FUNCAO: IMPRIME ARRAY --------- \n");
  imprimeArray(meuArray, 3);

  Serial.println("\n\n-------- FUNCAO: SOMA UM ARRAY --------- \n");
  somaUmArray(meuArray, 3);
  imprimeArray(meuArray,3);

  while(1){}

}

static void imprimeArray(uint8_t *vet, uint8_t tamanho)
{
  uint8_t i = 0;

  for(i = 0; i < tamanho; i++)
  {
    Serial.print("Elemento ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(*vet);

    // Incrementa o ponteiro: Desloca a memória para o próximo elemento
    vet++;
  }
}

static void somaUmArray(uint8_t *vet, uint8_t tamanho)
{
  uint8_t i = 0;

  for(i = 0; i < tamanho; i++)
  {
    // Incrementa um ao VALOR que vet está APONTANDO
    (*vet)++;
    // Incrementa o ponteiro: Desloca a memória para o próximo elemento
    vet++;
  }
}
