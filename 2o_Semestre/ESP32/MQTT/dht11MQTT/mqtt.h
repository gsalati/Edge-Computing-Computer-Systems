#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <PubSubClient.h>

void init_mqtt(void);
void mqtt_callback(char* topic, byte* payload, unsigned int length);

void publish_state(bool s);
void publish_temperatura(float t);
void publish_umidade(float h);

void mqtt_loop(void);
bool mqtt_connected(void);
void check_connection(void);
void connect_mqtt(void);


#endif