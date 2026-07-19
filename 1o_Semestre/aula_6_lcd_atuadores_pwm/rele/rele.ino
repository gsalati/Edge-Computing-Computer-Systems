// C++ code
// https://www.tinkercad.com/things/hpVQ5iar1tC-relespdt?sharecode=GMX_Ek6OWi2Wl226zWqLxTMov30sMS9fAB0ilW-_KRU
#define pin 8
void setup()
{
  pinMode(pin, OUTPUT);
}

void loop()
{
  digitalWrite(pin, HIGH);
  delay(5000); //
  digitalWrite(pin, LOW);
  delay(2000); // 
}