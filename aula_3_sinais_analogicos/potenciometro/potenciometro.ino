/*
* Aula 3: Sinais analógicos
* Exemplo de utilização do potenciômetro para definição de intensidade
* https://www.tinkercad.com/things/i4qaKhIIEwx-potenciometro?sharecode=o1KsG3x0ew8rIShLPTruflx1pmkRhRAWFmDLH_snTeQ
*
* DICA: documentação da função map:
* https://docs.arduino.cc/language-reference/fun%C3%A7%C3%B5es/math/map/
*/
// define constantes
#define VERDE 13
#define BRANCO 12
#define AZUL 11
#define POTENCIOMETRO A5
#define TEMPO_ATUALIZACAO 500
#define ADC_RESOL 1023

void setup()
{
  /*
  * Inicializa porta serial e pinos de saída
  */
  Serial.begin(9600);
  pinMode(VERDE, OUTPUT);
  pinMode(BRANCO, OUTPUT);
  pinMode(AZUL, OUTPUT);
}

void loop()
{
  uint16_t pot = 0;
  uint8_t intensidade = 0;
  uint8_t estadoVerde, estadoBranco, estadoAzul;
  
  // Faz a leitura do conversador AD
  pot = analogRead(POTENCIOMETRO);
  
  // Converte o valor do conversor AD 
  intensidade = map(pot, 0, ADC_RESOL, 100, 0);
  
  Serial.print("Valor de intensidade: ");
  Serial.println(intensidade);
  
  if(intensidade < 30)
  {
    estadoVerde = LOW;
    estadoBranco = LOW;
    estadoAzul = LOW;
  }
  else if(intensidade < 60)
  {
    estadoVerde = HIGH;
    estadoBranco = LOW;
    estadoAzul = LOW;
  }
  else if(intensidade < 90)
  {
    estadoVerde = HIGH;
    estadoBranco = HIGH;
    estadoAzul = LOW;
  }
  else
  {
    estadoVerde = HIGH;
    estadoBranco = HIGH;
    estadoAzul = HIGH;
  }
 
  // Atualiza o estados dos LEDs
  digitalWrite(VERDE, estadoVerde);
  digitalWrite(BRANCO, estadoBranco);
  digitalWrite(AZUL, estadoAzul);
  
  // Aguarda o tempo de amostragem
  delay(TEMPO_ATUALIZACAO);
}