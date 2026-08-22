# ESP32ish Simulator

"Simulacro" de ESP32 para utilização nas aulas de Edge Computing (FIAP/POA).

Esse simulador expõe algumas funções da biblioteca serial e da biblioteca de MQTT do Arduino para utiização em aula.

## Utilização
Edite o software no arquivo [esp32.cpp](src/esp32.cpp). Utilize a função função setup e a função loop "normalmente".

Antes de utilizar a comunicação serial, certifique-se qual Porta Com você deseja utilizar:
```bash
dmesg | grep tty
```

Edite o arquivo [serial.h](src/serial/serial.h#L21), e modifique a porta COM na linah 21. A porta padrão é `/dev/ttyACM0`.

## Build & Run

### Build
Em um sistema _Linux_, certifique-se que o cmake está instalado
```bash
sudo apt install cmake
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
sudo ./build/ESP32ish
```