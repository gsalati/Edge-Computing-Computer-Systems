# ESP32ish Simulator

Mock de ESP32 (Serial e MQTT) para utilização nas aulas de Edge Computing (FIAP/POA).

Esse simulador expõe algumas funções da biblioteca serial e da biblioteca PubSubClient(MQTT) do Arduino/ESP32 para utiização em aula.

## Utilização

Edite o software no arquivo [esp32.cpp](src/esp32.cpp). Utilize a função função setup e a função loop "normalmente".

Esse simulador implementa as funções da API do arduino listadas:
+ Serial.begin
+ Serial.available
+ Serial.readBytes(char* buffer, int length)
+ Serial.writeBytes(char* data, int length);
+ delay(int ms)

E as funções da bibliotea PubSubClient:
+ void setServer(const char * Domain, uint16_t Port);
+ void setCallback(std::function<void(const char*, uint8_t*, unsigned int)> Callback);
+ bool connected();
+ bool connect(const char* id);
+ void disconnect();
+ bool subscribe(const char* topic);
+ bool publish(const char* topic, const char* payload);
+ void loop();

### Para utilização com comunicação com Arduino
No arquivo [esp32.cpp](src/esp32.cpp), utilize a iniciallização do objeto Serial com a classe SerialCom
```cpp
SerialCom Serial
```


Antes de utilizar a comunicação serial, certifique-se qual Porta Com você deseja utilizar:
```bash
dmesg | grep tty
```

Edite o arquivo [serial.h](src/serial/serial.h#L21), e modifique a porta COM na linha 21. A porta padrão é `/dev/ttyACM0`.

#### Para utilização com WSL2

Caso esteja utilizando uma máquina virtual com WSL2, os seguintes passos devem ser seguidos:

1. Instale o [usbipd-win](https://github.com/dorssel/usbipd-win), através do instalador disponível no link, ou através do *powershell*:
```bash
winget install usbipd
```
2. Utilizando o *powershell* como adminsitrador.Adicione o dispositivo (Arduino) conectado ao WSL2:
```bash
usbipd list
usbipd bind --busid=<BUSID>
usbipd attach --wsl --busid=<BUSID>
```
Pronto! Agora o dispostivo deve ser listado normalmente dentro do WSL2.

### Para utilização SEM comunicação com Arduino
O simulador permite simular o outro ponto de comunicação através do objeto SerialMock. Para esse tipo de uso, as mensagens enviadas em Serial.writeBytes são simplesmente exibidas no console. Para simular o envio do dispositivo que estaria conectado utilize a entrada do console.

No arquivo [esp32.cpp](src/esp32.cpp), utilize a iniciallização do objeto Serial com a classe SerialCom
```cpp
SerialMock Serial
```

Para a "serial simulada" o método Serial.begin recebe um caractere do formato de dado que será utilizado na entrada do teclado.
```cpp
Serial.begin('h'); // Para formato hexadecimal
Serial.begin('s'); // Para formato de texto
```

## Build & Run



### Build
Em um sistema _Linux_, certifique-se que o cmake está instalado. Se necessário, instale
```bash
sudo apt upgrade
sudo apt install cmake
sudo apt install build-essential
```
Após, instale o pacote MQTT-PAHO utilizado no software:
```bash
sudo apt install libpaho-mqtt-dev libpaho-mqttpp-dev
```
Execute os seguintes comandos:

```bash
mkdir build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

Para um clean build
```bash
cmake --build build --clean-first
```

### Run:
Para executar, execute:
```bash
sudo ./build/ESP32Mock
```