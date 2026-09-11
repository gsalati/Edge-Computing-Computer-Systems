#include "mqtt.h"
#include <WiFi.h>

const char* broker_mqtt = "192.168.137.1";
// const char* broker_mqtt = "http://host.wokwi.internal";;
const int broker_mqtt_port = 1883;
const char* topic_subscribe_cmd = "/TEF/exemplo001/cmd";
const char* topic_publish_attrs = "/TEF/exemplo001/attrs";
const char* topic_publish_temp = "TEF/exemplo001/attrs/t";
const char* topic_publish_hum = "TEF/exemplo001/attrs/h";
const char* default_ID_MQTT = "fiware_001";

const char* topicPrefix = "exemplo001";

WiFiClient espClient;
PubSubClient MQTT(espClient);
//------------------------------------------------------------------------------//
void init_mqtt(void)
{
  Serial.println("Inicializando MQTT");
  MQTT.setServer(broker_mqtt, broker_mqtt_port);
  MQTT.setCallback(mqtt_callback);
  connect_mqtt();
}
//------------------------------------------------------------------------------//
void mqtt_callback(char* topic, byte* payload, unsigned int length){
    String msg((char*)payload, length);
    
    Serial.print("- Mensagem recebida: ");
    Serial.println(msg);

    // Forma o padrão de tópico para comparação
    String onTopic = String(topicPrefix) + "@on|";
    String offTopic = String(topicPrefix) + "@off|";

    // Compara com o tópico recebido
    if (msg.equals(onTopic)) {
      Serial.println("Comando ON recebido");
      publish_state(true);
    }

    if (msg.equals(offTopic)) {
        Serial.println("Comando OFF recebido");
        publish_state(false);
    }

}
//------------------------------------------------------------------------------//
void publish_state(bool s)
{
  check_connection();

  Serial.println("publica attr state");
  if(s)
  {
    MQTT.publish(topic_publish_attrs, "s|true");
  }else
  {
    MQTT.publish(topic_publish_attrs, "s|false");
  }
}
//------------------------------------------------------------------------------//
void publish_umidade(float h)
{
  check_connection();

  Serial.println("publica attr h");

  MQTT.publish(topic_publish_hum, String(h).c_str());

}
//------------------------------------------------------------------------------//
void publish_temperatura(float t)
{
  check_connection();

  Serial.println("publica attr t");

  MQTT.publish(topic_publish_temp, String(t).c_str());

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
  Serial.print("Conectando MQTT...");
  
  Serial.print("Broker: ");
  Serial.print(broker_mqtt);
  Serial.print(":");
  Serial.println(broker_mqtt_port);

  while (!MQTT.connected())
  {
      if (MQTT.connect(default_ID_MQTT))
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
  Serial.println("\n MQTT conectado");

  // Assina os topicos desejados
  MQTT.subscribe(topic_subscribe_cmd);
}
//-------------------------------------------------------------------------------//
void check_connection(void){
  if(!MQTT.connected()){
    Serial.println("MQTT desconectado. Reconectando");
    connect_mqtt();
  }
}
