// C++ code
// https://www.tinkercad.com/things/kX2diAEpj5y-ponte-h?sharecode=vgU64_o2O4_bcRpqt0-zs2GgyGKHT0OBclC9S8KLpFc
#define H1 10
#define H2 9
void setup()
{
  pinMode(H1, OUTPUT);
  pinMode(H2, OUTPUT);

  digitalWrite(H1, LOW);
  digitalWrite(H2, LOW);
}

void loop()
{
  digitalWrite(H2, LOW);
  digitalWrite(H1, HIGH);
  delay(5000); //
  
  digitalWrite(H1, LOW);
  digitalWrite(H2, HIGH);
  delay(5000); // Wait for 1000 millisecond(s)
}