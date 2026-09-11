#ifndef SENSORS_H
#define SENSORS_H

#include "DHT.h"

#define DHTPIN 14    
#define DHTTYPE DHT11

void init_sensors(void);
void readTemperatureaAndHumidty(float *t, float *h);

#endif