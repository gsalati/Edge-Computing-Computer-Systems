/*
* Happy coding =)
*/
#define ILUMINACAO 4
#define AQUECIMENTO 2
#define TMP36 A2
#define LDR A3
#define BTN 12
#define TEMPO 2000
#define VREF 5
#define ADC_RESOL 1023

void setup()
{
  Serial.begin(9600);
  
  pinMode(ILUMINACAO, OUTPUT);
  pinMode(AQUECIMENTO, OUTPUT);
  pinMode(BTN, INPUT);
}

void loop()
{
  uint16_t sensorTmp, sensorLdr;
  float temperatura, tempVoltage;
  uint8_t luminosidade, btnState;
  
  /*
  * Le todas as entradas do sistema
  */
  
  // Botao
   btnState = digitalRead(BTN);
  
  // Temperatura
  sensorTmp = analogRead(TMP36);
  tempVoltage = (float)sensorTmp*VREF/ADC_RESOL;
  temperatura = (tempVoltage - 0.5)*100;
  
  // Luminosidade
  sensorLdr = analogRead(LDR);
  luminosidade = map (sensorLdr, 54, 974, 0, 100);
  
  Serial.print("Estado do botão: ");
  Serial.println(btnState);
  
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  
  Serial.print("Luminosidade: ");
  Serial.println(luminosidade);
  
  // Sistema de aquecimento
  if(temperatura < 36)
  {
  	digitalWrite(AQUECIMENTO, HIGH);
  }
  
  if(temperatura > 40)
  {
  	digitalWrite(AQUECIMENTO, LOW);
  }
  
  // Sistema de iluminação
  if(luminosidade < 95 || btnState)
  {
  	digitalWrite(ILUMINACAO, HIGH);
  }
  else
  {
  	digitalWrite(ILUMINACAO,LOW);
  }
  
  delay(TEMPO);
   
}