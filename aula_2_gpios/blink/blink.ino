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
  pinMode(4, OUTPUT);
}

void loop()
{
 uint16_t val = 0;
 val = analogRead(A0);
}