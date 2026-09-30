#include "esp32.h"

const char* broker_mqtt = "localhost";
const int broker_mqtt_port = 1883;
// device_id é o valor utilizado no post 3 - Provisioning a smart lamp
const char* topic_subscribe_cmd = "/TEF/device_id/cmd"; // no protocolo UltraLight os comandos são enviados para esse tópico
const char* topic_publish_attrs = "/TEF/device_id/attrs";
const char* topic_publish_attr_id = "/TEF/device_id/attrs/t"; // /t é o object_id no post 3 - Provisioning a smart lamp

const char* default_ID_MQTT = "fiware_001";

const char* topicPrefix = "exemplo001";


// Awui o objeto para o MQTT vem da classe ArduinoMQTT
// Não é necessário inicializar com um objeto "WiFiClient" como no ESP32
ArduinoMQTT MQTT;


// Toda vez que um comando é enviado, essa função será chamada;
// Veremos envio de comandos (se der tempo) na terceira parte (CP3)
void mqtt_callback(const char* topic, uint8_t* payload, unsigned int length){
    String msg((char*)payload, length);
    std::cout << "\n\n----------Topico: " << topic << "| Payload: " << msg << std::endl;
}

void setup()
{
    // seta o servidor mqtt que está rodando o fiware -> localhost e porta 1883
    MQTT.setServer(broker_mqtt, broker_mqtt_port);
    // seta a função de callback quando recebemos comandos
    MQTT.setCallback(mqtt_callback);
    // conecta no servidor mqtt. teste é um identificador qualquer do cliente conectado. deve ser único para o mesmo servidor.
    MQTT.connect("teste");

    // Assina o topico de comandos
    MQTT.subscribe(topic_subscribe_cmd);


    // Aguarda um tempo para serial inicializar
    delay(2000);
    // publica um valor no atributoi desejado. valor deve estar em formato de texto
    MQTT.publish(topic_publish_attr_id, "valor");
}


void loop(){
    // a função .loop() deve ser chamada de tempo em tempo para para processar as mensagens recebedios (subscribed)
    MQTT.loop();
    delay(2000);
}
