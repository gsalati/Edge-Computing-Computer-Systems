#include "DHT.h"

#define DHTPIN 2    

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  dht.begin();
  delay(2000); // Aguarde a inicialização do sensor

}

void loop() {
  float h = dht.readHumidity();
  delay(500); // delay entre medidas
  float t = dht.readTemperature();

  Serial.print("Umidade: ");
  Serial.println(h);

  Serial.print("Temperatura: ");
  Serial.println(t);

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Falha"));
    delay(2000);
    return;
  }

  // Delay para proxima medida
  delay(2000);

}
