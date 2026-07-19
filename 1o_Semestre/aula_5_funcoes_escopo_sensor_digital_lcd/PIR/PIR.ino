const uint8_t pinLed = 7;
const uint8_t pinPir = 12; 
void setup()
{
  pinMode(pinLed, OUTPUT);
  pinMode(pinPir, INPUT);
}

void loop()
{
  uint8_t sensorState;
  
  sensorState = digitalRead(pinPir);
 
  digitalWrite(pinLed, sensorState);
  
  delay(200); // Wait for 1000 millisecond(s)
}