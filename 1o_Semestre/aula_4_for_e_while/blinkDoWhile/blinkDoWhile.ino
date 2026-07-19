/*
* https://www.tinkercad.com/things/4MvWAXCKQS2-blinkdowhile?sharecode=9GleLILvgcKe2gHqIJgPuOO9SvpA29fH6MkDXGohN-o
*/
// C++ code
#define LED 4
#define BTN 2
void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);  
  pinMode(BTN, INPUT);
}

void loop()
{
  uint8_t state;
  
  digitalWrite(LED, HIGH);
  delay(1000);
  
  do{
    digitalWrite(LED, LOW);
    delay(1000);  
    
    state = digitalRead(BTN);
  }while(state == HIGH);
 
}