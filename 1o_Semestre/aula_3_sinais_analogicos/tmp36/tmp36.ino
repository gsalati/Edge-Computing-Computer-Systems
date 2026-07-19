/*
* Aula 3: Sinais analógicos
* Exemplo básico de utilização do sensor TMP36
*https://www.tinkercad.com/things/0Rr9XdPabEU-tmp36?sharecode=aKBFPfHPWhgy7pytov8ITYerzN-X145Hk7nn8v_B-2E
*/

#define SENSOR_PIN A5
#define ADC_RESOL 1023
#define VREF 5

void setup()
{
	Serial.begin(9600);
}

void loop()
{
 	uint16_t sensor = 0;
  	float sensorVoltage = 0;
  	float temp = 0;
  
  	// Faz a leitura do valor do sensor
  	sensor = analogRead(SENSOR_PIN);
   
  	// Converte medida em temperatura
  	sensorVoltage = (float)sensor*VREF/ADC_RESOL;
  	temp = (sensorVoltage - 0.5) * 100;
  
  	// Imprime
  	Serial.print("Temperatura medida: ");	
  	Serial.println(temp);
  
  	// Espera por 1 segundo
  	delay(1000);
}