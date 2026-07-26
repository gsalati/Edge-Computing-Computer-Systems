#define R 13
#define G 11
#define B 12

void setup()
{
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  
  Serial.begin(9600);  
}

void loop()
{
  uint16_t dataRx = 0;
  int16_t v = 0;
  float temperatura;
  size_t read;
  bool btn;
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  
  // Checa se há uma mensagem para ser lida
  if (Serial.available() >= sizeof(dataRx)) { 
	  read = Serial.readBytes((char*)&dataRx, sizeof(dataRx));

    // Decodifica
    btn = (dataRx >> 10) & 0x01;
    v = (int16_t)(dataRx & 0x03FF) - 200;
    temperatura = (float)v/10;
    
    Serial.println(dataRx);
  	Serial.println(temperatura);
  	Serial.println(btn);
  
  if(btn)
  {
    if (temperatura > 40.0f)
    {
       r = 1;
    }
    else if (temperatura >= 0.0f)
    {
        g = 1;
    }
    else
    {
       b = 1;
    }
  }
      
      digitalWrite(R,r);
      digitalWrite(G,g);
      digitalWrite(B,b);
    }
   
}