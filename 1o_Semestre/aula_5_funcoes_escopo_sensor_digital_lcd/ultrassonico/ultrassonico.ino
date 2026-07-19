const uint8_t pinTrigger = 9;
const uint8_t pinEcho = 8;

void setup()
{
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
  

  Serial.begin(9600);
}

// Declaração de funções
static void triggerHC(uint8_t pin);
static float time2Distance(unsigned long time);

void loop()
{
  unsigned long time = 0;
  float distance = 0;
  
  // Chama a funcao que inicia o sensor
  triggerHC(pinTrigger);
  
  // Funcao pulseIn do arduino, le o tempo do pulso
  time = pulseIn(pinEcho, HIGH);
  
  // Funcao para conversao do tempo em cm
  distance = time2Distance(time);
  Serial.print("Distancia em cm: ");
  Serial.println(distance);
  
  delay(500);  	
  	
}

// Definicao das funcoes
static void triggerHC(uint8_t pin)
{
  digitalWrite(pin, LOW);
  delayMicroseconds(5);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
}

static float time2Distance(unsigned long time)
{
  return (float)time/58;
}