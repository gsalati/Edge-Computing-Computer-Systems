#ifndef MQTT_H
#define MQTT_H
#include <cstdint>
#include <functional>
#include <mqtt/async_client.h>
#include <memory>
#include <queue>

// Possible values for client.state()
#define MQTT_CONNECT_FAILED         -2
#define MQTT_DISCONNECTED           -1
#define MQTT_CONNECTED               0

struct mqttQueueMsg{
    std::string topic;
    std::string payload;
};

class MqttCallback : public virtual mqtt::callback
{
public:
    void message_arrived(mqtt::const_message_ptr msg) override;
    void dispatch_msgs();
    void set_callback_arduino(std::function<void(const char*, uint8_t*, unsigned int)> cb);
private:
    std::queue<mqttQueueMsg> msgQueue;
    std::function<void(const char*, uint8_t*, unsigned int)> callbackArduino;
};

class ArduinoMQTT {
public:
    ArduinoMQTT();
    ~ArduinoMQTT();
    void setServer(const char * Domain, uint16_t Port);
    void setCallback(std::function<void(const char*, uint8_t*, unsigned int)> Callback);
    
    bool connected();
    bool connect(const char* id);
    void disconnect();

    bool subscribe(const char* topic);
    bool publish(const char* topic, const char* payload);

    void loop();
private:
    const char* domain;
    uint16_t port;
    std::unique_ptr<mqtt::async_client> mqttClient;
    MqttCallback callbackPaho;

};

#endif