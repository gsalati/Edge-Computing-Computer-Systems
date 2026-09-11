#include "sensors.h"

DHT dht(DHTPIN, DHTTYPE);

void init_sensors(void){
  dht.begin();
  delay(2000);
}

void readTemperatureaAndHumidty(float *t, float *h){
  *h = dht.readHumidity();
  delay(500); // delay entre medidas
  *t = dht.readTemperature();
}