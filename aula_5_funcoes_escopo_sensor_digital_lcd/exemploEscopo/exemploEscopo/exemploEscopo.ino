int variavelGlobal = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(variavelGlobal);
  variavelGlobal++;
}

void loop() {
  int variavelLocal = 0;
  Serial.println(variavelGlobal);
  variavelGlobal++;
  Serial.println(variavelGlobal);

  variavelLocal = variavelGlobal;
  Serial.println(variavelLocal);

  delay(300000)
}
