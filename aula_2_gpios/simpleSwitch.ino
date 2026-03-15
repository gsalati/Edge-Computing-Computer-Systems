#define LED1 4
#define BOTAO 3
#define TEMPO_LEITURA 100


void setup()
{
  // Setamos o pino LED1 como SAÍDA
  pinMode(LED1, OUTPUT);
  // Setamos o pino BOTAO como entrada
  pinMode(BOTAO,INPUT);
}

void loop()
{
  // Declaramos uma variável de apenas 1 byte para leitura do estado do botão
  uint8_t on_off = 0;

  // Realiza a leitura
  on_off = digitalRead(BOTAO);

  /*
  * Escreve o valor lido pelo botão no LED
  * Como optamos por um resistor de pull down
  * o valor lógico quando pressionado é alto
  */ 
  digitalWrite(LED1, on_off);

  // Espera um tempo entre leituras
  delay(TEMPO_LEITURA); 
}