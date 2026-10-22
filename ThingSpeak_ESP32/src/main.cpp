#include <Arduino.h>
#include <WiFi.h>
#include "mqtt.h"
#include "sensors.h"
#include "control.h"

#define TEMPO_AMOSTRAGEM 20000
#define TEMPO_WIFI_CHECK 100

// Configuração WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

void connect_wifi(){
  Serial.print("Conectando..");
  // Poll o status do wifi até ser conectado.
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500); // Embora tenhamos iniciado uma saga contra o delay, nesse caso nada além de esperar conectar o wifi está acontecendo. então tudo bem.
  }

  Serial.println("\nWifi Conectado");
}

void setup() {
  Serial.begin(9600);

  init_control();

  // Inicia a conexão do WiFi
  WiFi.begin(ssid, password);

  init_sensors();
  connect_wifi();
  init_mqtt();
}

void loop() {
  unsigned long lastTimeSensor = 0;
  unsigned long lastTimeCon = 0;
  unsigned long timeNow = 0;

  float t,h;

  while(true){

   timeNow = millis();
    
    if(timeNow - lastTimeCon >= TEMPO_WIFI_CHECK) {
      if(WiFi.status() != WL_CONNECTED)
      {
        Serial.println("Wifi desconectado");
        // reconecta wifi
        connect_wifi();
      }
      lastTimeCon = millis();
    }

    if(timeNow - lastTimeSensor >= TEMPO_AMOSTRAGEM)
    {
      readTemperatureaAndHumidty(&t, &h);
      Serial.print("Temperatura: ");
      Serial.println(t);
      Serial.print("Umidade: ");
      Serial.println(h);

      // Publish para o MQTT
      publish_temp_umidade(t, h);

      controlLed(t);
      
      lastTimeSensor = millis();
    }

    // Verifica Mensagens MQTT;
    mqtt_loop();
  }
}
