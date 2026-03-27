/*
* Link para exemplo:
* https://www.tinkercad.com/things/gWhGAooe3Jh-blinkfor?sharecode=jZokboJQTmXsUqE2HDJLIkh6wHcC7RCGat2DFXp64i8
*/
#define LED 4

void setup()
{
  pinMode(LED, OUTPUT);
}

void loop()
{
  uint8_t i = 0;
  for(i = 0; i < 30; i++)
  {
  	digitalWrite(LED, HIGH);
  	delay(200); 
  	digitalWrite(LED, LOW);
  	delay(200); 
  }
  
  delay(30000);

}