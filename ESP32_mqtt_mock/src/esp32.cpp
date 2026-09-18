#include "esp32.h"

const char* broker_mqtt = "localhost";
const int broker_mqtt_port = 1883;
const char* topic_subscribe_cmd = "/TEF/exemplo001/cmd";
const char* topic_publish_attrs = "/TEF/exemplo001/attrs";
const char* topic_publish_temp = "/TEF/exemplo001/attrs/t";
const char* topic_publish_hum = "/TEF/exemplo001/attrs/h";
const char* default_ID_MQTT = "fiware_001";

const char* topicPrefix = "exemplo001";

// Para Arduino conectado:
//SerialCom Serial;

// Sem Arduino, utilizamos "serial mock"
SerialMock Serial;

// Awui o objeto para o MQTT vem da classe ArduinoMQTT
// Não é necessário inicializar com um objeto "WiFiClient" como no ESP32
ArduinoMQTT MQTT;

// Array com bytes arbitrários para teste
uint8_t test[2] = {0xAB, 0xCD};

void mqtt_callback(const char* topic, uint8_t* payload, unsigned int length){
    String msg((char*)payload, length);
    std::cout << "\n\n----------Topico: " << topic << "| Payload: " << msg << std::endl;
}

void setup()
{
    MQTT.setServer(broker_mqtt, broker_mqtt_port);
    MQTT.setCallback(mqtt_callback);
    MQTT.connect("teste");
      // Assina os topicos desejados
    MQTT.subscribe(topic_subscribe_cmd);

    // h -> dados escritos e lidos em hexa; s -> dados em formato de texto
    Serial.begin('h'); 

    // Com Arduino conectado, serial.begin "normal"
    // Serial.begin(9600)

    // Aguarda um tempo para serial inicializar
    delay(2000);

    MQTT.publish(topic_publish_attrs, "s|true");
}


void loop(){
   int a;
   int n;
   uint8_t rx[256];

    while(1){
        // Checa se há caracteres esperando para serem recebidos
        a = Serial.available();
        if (a > 0) { 
            n = Serial.readBytes((char*)rx, a);
            /* 
             * Printa na nossa tela o dado recebido
             * Com arduino conectado, printaria apenas o primeiro byte enviado pelo arduino
             * Sem arduino conectado, printa o primeiro byte enviado por nós "simulando" o Arduino no console
            */
            cout << "RX ESP32: ";
            cout << (int)rx[0] << endl;
            cout.flush();

            delay(1000);
        }

        MQTT.loop();
        delay(2000);
    }
}