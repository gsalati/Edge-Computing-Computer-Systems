#include "mqtt.h"
#include <WiFi.h>
#include "control.h"

const char* topic_subscribe_cmd = "/TEF/exemplo001/cmd";
const char* topic_publish_attrs = "/TEF/exemplo001/attrs";
const char* topic_publish_temp = "TEF/exemplo001/attrs/t";
const char* topic_publish_hum = "TEF/exemplo001/attrs/h";
const char* default_ID_MQTT = "fiware_001";

const char* topicPrefix = "exemplo001";

// ThingSpeak MQTT
const char* mqtt_server = "mqtt3.thingspeak.com";
const int mqtt_port = 1883;

const char* mqtt_client_id = "JCApOBASPC8DCSM6MwcbDDk";
const char* mqtt_username = "JCApOBASPC8DCSM6MwcbDDk";
const char* mqtt_password = "VjgF/Lp55TRnQmMck6NKAuD/";

// ID numérico do canal ThingSpeak
const unsigned long channelID = 3543455;

WiFiClient espClient;
PubSubClient MQTT(espClient);
//------------------------------------------------------------------------------//
void init_mqtt(void)
{
  Serial.println("Inicializando MQTT");
  MQTT.setServer(mqtt_server, mqtt_port);
  MQTT.setCallback(mqtt_callback);
  connect_mqtt();
}
//------------------------------------------------------------------------------//
void mqtt_callback(char* topic, byte* payload, unsigned int length){
    String msg((char*)payload, length);
    float temperatura = msg.toFloat();
    
    Serial.print("- Mensagem recebida. Topico :");
    Serial.print(topic);
    Serial.print(" payload: ");
    Serial.println(msg);

    setTempTh(temperatura);

}
//------------------------------------------------------------------------------//
void publish_temp_umidade(float t, float h){
  check_connection();

  Serial.print("Publica Umidade: ");
  Serial.print(h);
  Serial.print("e Temperatura: ");
  Serial.println(t);

   // Tópico para publicar no canal
    String topico =
      "channels/" + String(channelID) + "/publish";

      String payload = "field1=" + String(t) +"&field2=" + String(h);

      MQTT.publish(topico.c_str(),
      payload.c_str());
}
//------------------------------------------------------------------------------//
void publish_umidade(float h)
{
  check_connection();

  Serial.print("Publica Umidade: ");
  Serial.println(h);

   // Tópico para publicar no canal
    String topico =
      "channels/" + String(channelID) + "/publish";

      String payload = "field2=" + String(h);

      MQTT.publish(topico.c_str(),
      payload.c_str());
}
//------------------------------------------------------------------------------//
void publish_temperatura(float t)
{
  check_connection();

  Serial.print("Publica Temperatura: ");
  Serial.println(t);

   // Tópico para publicar no canal
    String topico =
      "channels/" + String(channelID) + "/publish";

      String payload = "field1=" + String(t);

      MQTT.publish(topico.c_str(),
      payload.c_str());

}
//------------------------------------------------------------------------------//
void mqtt_loop(void)
{
  check_connection();
  MQTT.loop();
}
//------------------------------------------------------------------------------//
bool mqtt_connected(void)
{
  return MQTT.connected();
}
//-------------------------------------------------------------------------------//
void connect_mqtt(void)
{
  // Tópico para publicar no canal
  String topico_sub =  "channels/" + String(channelID) + "/subscribe/fields/field3";

  boolean sub_resp;
  
  Serial.print("Conectando MQTT...");
  
  Serial.print("Broker: ");
  Serial.print(mqtt_server);
  Serial.print(":");
  Serial.println(mqtt_port);

  while (!MQTT.connected())
  {
      if (MQTT.connect(
          mqtt_client_id,
          mqtt_username,
          mqtt_password))
      {
          Serial.println("\nMQTT conectado!");
      }
      else
      {
          Serial.print("\nFalha MQTT, state=");
          Serial.println(MQTT.state());
          delay(2000);
      }
  }
  
  Serial.println("Assina tópico de configuração: ");

  // Assina os topicos desejados
  Serial.println(topico_sub);

  // QoS deve ser 0 para o thingspeak free
  if(!MQTT.subscribe(topico_sub.c_str(), 0)){
    Serial.println("Falha ao assinar tópico de configuração");
  }

}
//-------------------------------------------------------------------------------//
void check_connection(void){
  if(!MQTT.connected()){
    Serial.println("MQTT desconectado. Reconectando");
    connect_mqtt();
  }
}
