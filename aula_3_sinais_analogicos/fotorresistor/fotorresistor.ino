/*
* Aula 3: Sinais analógicos
* Exemplo de leitura analógica e utilização do fotorresistor
* https://www.tinkercad.com/things/7Axp1NZkdfZ-fotorresistor?sharecode=eeogGqTaAKI64KGGgVidkDB4F-3_ESJ3iDL1l0Oi4GQ
*/
// C++ code
//
/*
* Definimos os valores constantes que serão utilizados
*/
#define ADC_RESOL 1023
#define VREF 5
#define R1 10000

void setup()
{
  // Inicia a porta serial com baudrate de 9600
  Serial.begin(9600);
}

void loop()
{
  // Definição das variáveis que serão utilziadas
  uint16_t sensorValue = 0;
  float tensao = 0;
  float resistencia = 0;
  
  // Faz a leitura do conversor AD no pino A0
  sensorValue = analogRead(A0);
  
  /*
  * Converte o valor digital do conversor AD em valor 
  *	de tensão analógica
  */
  tensao = (float)sensorValue*VREF/ADC_RESOL;
  
  // Converte o valor da tensão em resistência
  resistencia = R1*(VREF-tensao)/tensao;
  
  // Escreve para o monitor serial os valores
  Serial.print("Valor medida no ADC: ");
  Serial.println(sensorValue);
  
  Serial.print("Valor convertido em tensão: ");
  Serial.println(tensao);
  
  Serial.print("Valor convertido em resistência: ");
  Serial.println(resistencia);
  
  delay(2000);
}