// C++ code
#define SENSOR_PIN A5
#define ADC_RESOL 1023
#define VREF 5
#define BTN 4

static uint16_t encode_temp(float temp);

void setup()
{
  	pinMode(BTN, INPUT);
	Serial.begin(9600);
}

void loop()
{
 	uint16_t sensor = 0;
  	uint16_t dataTx;
  	float sensorVoltage = 0;
  	float temp = 0;
  	uint16_t temp_encoded;
  	bool btn_state = 0;
  	
  
  	static uint8_t btn_history;
  
  	// Faz a leitura do valor do sensor
  	sensor = analogRead(SENSOR_PIN);
   
  	// Converte medida em temperatura
  	sensorVoltage = (float)sensor*VREF/ADC_RESOL;
  	temp = (sensorVoltage - 0.5) * 100;
  
	// Codifica valor de temperaturaa
  	temp_encoded = encode_temp(temp);
  
  	btn_history = (btn_history << 1) | digitalRead(BTN);
  
  	if(btn_history == 0xFF)
    {
    	btn_state = true;
    }
  
  	// Monta o pacote que será transmitido
  	dataTx = temp_encoded | ((btn_state&0x01) << 10);
  
  	Serial.write((char*)&dataTx, sizeof(dataTx));
  
  	// Espera por 10 ms
  	delay(500);
}

static uint16_t encode_temp(float valor)
{
  uint16_t v, encoded;
  // Limita a faixa
  if (valor < -20.0f) valor = -20.0f;
  if (valor >  50.0f) valor =  50.0f;

  // Converte para inteiro com resolução de 0,1
  v = (int16_t)(valor * 10.0f);

  // Offset: -200..500 -> 0..700
  encoded = (uint16_t)(v + 200);
  
  return encoded;
}