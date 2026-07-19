/*
* https://www.tinkercad.com/things/6zsUmAx2fvM-blinkwhile?sharecode=jLtoocrxEk3RI0CMYNXj_Tond5AhqdVZj2UJAhGPNB8
*/

// C++ code
#define LED 4
#define BTN 2
void setup()
{
  pinMode(LED, OUTPUT);  
  pinMode(BTN, INPUT);
}

void loop()
{
  uint8_t state;
  
  state = digitalRead(BTN);
  
  while(state == HIGH)
  {
  	digitalWrite(LED, HIGH);
  	delay(1000); 
  	digitalWrite(LED, LOW);
  	delay(1000);
    
    state = digitalRead(BTN);
  }
 
}