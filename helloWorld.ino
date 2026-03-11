// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("\nHello FIAP from setup. Isto vai rodar apenas 1x");
}

// the loop routine runs over and over again forever:
void loop() {
  // print out the state of the button:
  Serial.println("Hello Eng. de SW FIAP from loop");
  delay(1000);  // delay in milli segundos
}
