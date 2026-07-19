// C++ code
// https://www.tinkercad.com/things/fkTosZrQQOg-ledpwm?sharecode=ELcgdkBpevyms_0yQAi-8to7VEk1pncqyU-6QzYxtkY
const uint8_t ledPwm = 11;
const uint8_t pot = A1;

void setup()
{
  	Serial.begin(9600);
	pinMode(ledPwm, OUTPUT);
}

void loop()
{
  uint16_t potRead = 0;
  uint8_t potLed = 0;
  
  potRead = analogRead(pot);
  potLed = map(potRead, 0, 1023, 0,255);
  Serial.println(potLed);
  analogWrite(ledPwm, potLed);
  delay(10);
}