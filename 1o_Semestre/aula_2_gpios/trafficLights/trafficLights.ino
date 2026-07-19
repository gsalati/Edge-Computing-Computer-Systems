/**
* Atividade sugerida na aula 2: GPIOs
* Circuito e simulação no tinkercad: https://www.tinkercad.com/things/jApjFp4IoM9-trafficlights?sharecode=hRNFsLuYolMO8eG2i6d_1O1WElTvH4jw6HziI3vi8Os
*/

/*
* Utiliza diretrizes de compilação para melhor legibilidade do código
* No exemplo disponivel no tinkercard, utilizei o pino digital 4 do Arduino
* TEMPO_PISCA em ms, 1000ms = 1s
*/ 
#define VERMELHO 4
#define AMARELO 3
#define VERDE 2
#define TEMPO_VERMELHO  5000 // 5 segundos
#define TEMPO_AMARELO   2000 // 2 segundos
#define TEMPO_VERDE 	4000 // 4 segundos

void setup()
{
  // Configura pinos como saída
  pinMode(VERMELHO, OUTPUT);
  pinMode(AMARELO, OUTPUT);
  pinMode(VERDE, OUTPUT);
}

void loop()
{
  /*
  * Acende o led desejado, aguarda o tempo em que o led deve estar ativo e desativa
  * A lógica se repete para as três cores
  */
  digitalWrite(VERMELHO, HIGH);
  delay(TEMPO_VERMELHO); 
  digitalWrite(VERMELHO, LOW);
  
  digitalWrite(VERDE, HIGH);
  delay(TEMPO_VERDE); 
  digitalWrite(VERDE, LOW);
  
  digitalWrite(AMARELO, HIGH);
  delay(TEMPO_AMARELO); 
  digitalWrite(AMARELO, LOW);
}