/**
* Atividade botoeira de duplo acionamento.
* Aula 2: GPIOs
* DICA: Para manter um push button pressionado no tinkercad
* clique pressioanndo o shift, o botão permanecerá pressionado
* https://www.tinkercad.com/things/9121wpWgsLQ-boteiraduploacionamento?sharecode=DYk81D98dsvl91g1qqJqkyjM47hlkvDgqClizshvSP8
* 
* DICA: Atente-se aos terminais dos push-buttons,
* passando o mouse em cima, é possível notar a detonação
* terminal 1a, 2a, 1b, 2b. A ligação ocorre entre
* os terminais 1a-2a ou 1b-2b
*/

/*
* Define valores constantes
*/ 
#define LED1 12
#define BOTAO1 11
#define BOTAO2 4
#define TEMPO_LEITURA 600


void setup()
{
  // Configura porta serial para utilizar o monitor serial
  Serial.begin(9600);
  
  // Configura os pinos de entrada e saida
  pinMode(LED1, OUTPUT);
  
  pinMode(BOTAO1,INPUT);
  pinMode(BOTAO2,INPUT);
}

void loop()
{
  uint8_t estadoBt1 = 0;
  uint8_t estadoBt2 = 0;
  
  // Le o estados dos dois botões
  estadoBt1 = digitalRead(BOTAO1);
  estadoBt2 = digitalRead(BOTAO2);
  
  // Printa para a saída serial o estado dos botões
  Serial.print("Estado Botao1: ");
  Serial.println(estadoBt1);
  
  Serial.print("Estado Botao2: ");
  Serial.println(estadoBt2);
  
  /*
  * Verifica: Se AMBOS os botões estão ativos
  * (observe que o circuito utiliza resistores de pull down)
  * Se ambos estão ativos, acende o LED
  */
  if(estadoBt1 == HIGH && estadoBt2 == HIGH)
  {
    digitalWrite(LED1, HIGH);
  }
  // SE NÃO, apaga o LED
  else
  {
  	digitalWrite(LED1, LOW);
  }

  // Espera o tempo desejado
  delay(TEMPO_LEITURA); 
}