/*
* Utiliza diretrizes de compilação para melhor legibilidade do código
* No exemplo disponivel no tinkercard, utilizei o pino digital 4 do Arduino
* TEMPO_PISCA em ms, 1000ms = 1s
*/ 
#define LED1 4
#define TEMPO_PISCA 1000

void setup()
{
  // Setamos o pino LED1 como SAÍDA
  pinMode(LED1, OUTPUT);
}

void loop()
{
  // Escreve o valor HIGH no pino LED1, ligando o led
  digitalWrite(LED1, HIGH);
  // Espera o tempo desejado
  delay(TEMPO_PISCA); 
  // Escreve o valor lógico LOW no pino LED1, desligando o led
  digitalWrite(LED1, LOW);
  // Espera o tempo desejado
  delay(TEMPO_PISCA); 
}