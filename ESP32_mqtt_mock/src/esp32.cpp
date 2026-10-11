#include "esp32.h"

const char* broker_mqtt = "localhost";
const int broker_mqtt_port = 1883;
// device_id é o valor utilizado no post 3 - Provisioning a smart lamp
const char* topic_subscribe_cmd = "/TEF/fiap001/cmd"; // no protocolo UltraLight os comandos são enviados para esse tópico
const char* topic_publish_attrs = "/TEF/fiap001/attrs";
const char* topic_publish_attr_id = "/TEF/fiap001/attrs/t"; // /t é o object_id no post 3 - Provisioning a smart lamp

const char* default_ID_MQTT = "fiware_001";

const char* topicPrefix = "exemplo001";


// Awui o objeto para o MQTT vem da classe ArduinoMQTT
// Não é necessário inicializar com um objeto "WiFiClient" como no ESP32
ArduinoMQTT MQTT;

// Para Arduino conectado:
// Classe Serial "imitando" Arduino
SerialCom Serial;

// Toda vez que um comando é enviado, essa função será chamada;
// Veremos envio de comandos (se der tempo) na terceira parte (CP3)
void mqtt_callback(const char* topic, uint8_t* payload, unsigned int length){
    String msg((char*)payload, length);
    std::cout << "\n\n----------Topico: " << topic << "| Payload: " << msg << std::endl;
}

void setup()
{
    //
    Serial.begin(9600);

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
    MQTT.publish(topic_publish_attr_id, "25.3");
}


void loop(){
    int bytesToRead;
    int bytesRead;
    uint8_t bufferRx;
    uint8_t bufferTx;
    std::string payloadMqtt;
    bool mqttResponse;

    while(1){

        // Checa se recebeu uma mensagem do Arduino
        bytesToRead = Serial.available();
        if(bytesToRead > 0){
            // Le a mensagem do arduino
            bytesRead = Serial.readBytes((char*)&bufferRx, bytesToRead);

            // Printa na tela. Estamos utilizando uma stream de output do C++.
            // Não estamos no hardware do arduino, portanto nao utilizamos Serial.print para escrever na tela
            std::cout << "Byte recebido: " << (int)bufferRx << std::endl;

            /* Publica o valor recebeido no atributo da temperatura.
            * Lembrando, o payload do MQTT é em formato de texto, estamos recebendo um valor inteiro
            * Devemos converete resse valor para texto
            * */
            payloadMqtt = std::to_string(static_cast<int>(bufferRx));
            mqttResponse = MQTT.publish(topic_publish_attr_id, payloadMqtt.c_str());
            
            if(mqttResponse){ // MQTT publicado. Responde com OK
                std::cout << "MQTT Publicado!" << std::endl;
                bufferTx = 0x01;
                Serial.writeBytes((char*)&bufferTx, sizeof(bufferTx));
            }else{
                std::cout << "Falha ao publicar MQTT" << std::endl;
                bufferTx = 0x00;
                Serial.writeBytes((char*)&bufferTx, sizeof(bufferTx));
            }
        }

        // a função .loop() deve ser chamada de tempo em tempo para para processar as mensagens recebedios (subscribed)
        MQTT.loop();
        delay(200);

    }   
}
