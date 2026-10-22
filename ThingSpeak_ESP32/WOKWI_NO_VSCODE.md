# ESP32 + PlatformIO + Wokwi + MQTT local

Guia para configurar um projeto ESP32 no Visual Studio Code usando
PlatformIO e Wokwi

## 1. Instalar o Visual Studio Code

1.  Baixe e instale o [Visual Studio
    Code](https://code.visualstudio.com/).
2.  Abra o VS Code.
3.  Abra a área **Extensions** (ícone de extensões na barra lateral, ou
    `Ctrl+Shift+X`).

## 2. Instalar o PlatformIO

1.  Na área de extensões, procure por **PlatformIO IDE**.
2.  Instale a extensão oficial **PlatformIO IDE**.
3.  Aguarde a inicialização e a instalação dos componentes necessários.
    Isso pode levar alguns minutos.
4.  Não é necessário instalar o PlatformIO Core separadamente para usar
    a extensão do VS Code.

Documentação: [PlatformIO IDE para VS
Code](https://docs.platformio.org/en/latest/integration/ide/vscode.html).

## 3. Instalar o Wokwi para VS Code

1.  Na área de extensões (`Ctrl+Shift+X`), procure **Wokwi Simulator** /
    **Wokwi for VS Code**.
2.  Instale a extensão oficial do Wokwi.
3.  Pressione `F1` para abrir a Command Palette.
4.  Execute `Wokwi: Request a new License` e siga as instruções no
    navegador para ativar a licença, caso solicitado.

Documentação: [Getting Started --- Wokwi for VS
Code](https://docs.wokwi.com/vscode/getting-started).

## 4. Criar o projeto ESP32 no PlatformIO

1.  Abra o menu PlatformIO (ícone de formiga na barra lateral) ou o
    **PlatformIO Home**.
2.  Clique em **New Project**.
3.  Use, por exemplo:
    -   **Name:** `esp32-mqtt-wokwi`
    -   **Board:** `DO IT ESP32 Dev KIT` 
    -   **Framework:** `Arduino`
4.  Crie o projeto e abra a pasta dele no VS Code.

A estrutura ficará parecida com esta:

``` text
esp32-mqtt-wokwi/
├── include/
├── lib/
├── src/
│   └── main.cpp
├── test/
├── platformio.ini
├── wokwi.toml
└── diagram.json
```

Os arquivos `wokwi.toml` e `diagram.json` serão criados manualmente
abaixo, caso ainda não existam.

## 5. Configurar o PlatformIO e a biblioteca MQTT

Abra `platformio.ini` e confirme que o ambiente corresponde à placa
escolhida. Para o exemplo `esp32dev`, use:

``` ini
[env:esp32doit-devkit-v1]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
lib_deps = 
	knolleary/PubSubClient@^2.8
	adafruit/DHT sensor library@^1.4.7
```

Se o PlatformIO criou um ambiente com outro nome, mantenha esse nome e
use-o também no caminho do firmware em `wokwi.toml`.

## 6. Criar o arquivo `wokwi.toml`

Crie `wokwi.toml` na **raiz do projeto**, no mesmo diretório que
`platformio.ini`. Para o ambiente `[env:esp32doit-devkit-v1]`, use:

``` toml
[wokwi]
version = 1
firmware = '.pio/build/esp32doit-devkit-v1/firmware.bin'
elf = '.pio/build/esp32doit-devkit-v1/firmware.elf'

[net]
gateway = "ws://localhost:9011"
```

Se o nome do ambiente não for `esp32doit-devkit-v1`, substitua esse trecho nos
caminhos `.pio/build/<esp32dev>/...`.

A seção `[net]` configura a extensão do Wokwi para usar o gateway
privado local. O gateway precisa estar rodando antes de iniciar a
simulação.

Referência: [Configuração do projeto Wokwi
(`wokwi.toml`)](https://docs.wokwi.com/vscode/project-config).

## 7. Criar o arquivo `diagram.json`

Crie `diagram.json` na raiz do projeto, junto de `wokwi.toml`. Copie o conteúdo do arquivo `diagram.json` presente no simulador online do Wokwi.

## 8. Compilar e iniciar a simulação

1.  Abra o terminal integrado do VS Code (**Terminal → New Terminal**).

2.  Compile o projeto:

    ``` bash
    pio run
    ```

    Se o comando `pio` não estiver disponível no terminal, use o botão
    **Build** do PlatformIO.

3.  Confirme que a compilação terminou sem erros e que existe o arquivo
    `.pio/build/esp32doit-devkit-v1/firmware.bin`.

4.  Abra `diagram.json`.

5.  Pressione `F1` e execute `Wokwi: Start Simulator`.

6.  Confira a saída serial da simulação.

⚠️ 📢

**_A extensão do Wokwi simula o firmware já compilado pelo PlatformIO;
compile novamente sempre que fizer alterações no código._**

⚠️ 📢

## 9. Solução de problemas

### O ESP32 não conecta ao broker
-   Confirme que `wokwi.toml` está na raiz do projeto e contém
    `gateway = "ws://localhost:9011"`.
-   No firmware, use `host.wokwi.internal` como host MQTT, não
    `localhost` nem `127.0.0.1`.
-   Confirme que o Mosquitto está ativo na porta `1883`.
-   Veja o código retornado por `mqtt.state()` no monitor serial.

### A simulação não encontra o firmware

-   Execute `pio run` antes de iniciar o simulador.
-   Confirme o nome do ambiente em `platformio.ini`.
-   Confira os caminhos de `firmware` e `elf` em `wokwi.toml`. Os
    caminhos são relativos à raiz do projeto e devem usar barras `/`,
    inclusive no Windows.


## Links úteis

-   [Visual Studio Code](https://code.visualstudio.com/)
-   [Instalação do PlatformIO
    IDE](https://platformio.org/install/ide?install=vscode)
-   [Wokwi para VS Code --- primeiros
    passos](https://docs.wokwi.com/vscode/getting-started)
-   [Wokwi --- configuração
    `wokwi.toml`](https://docs.wokwi.com/vscode/project-config)
-   [Wokwi --- projetos
    PlatformIO](https://docs.wokwi.com/vscode/platformio)
-   [Wokwi Private IoT Gateway ---
    releases](https://github.com/wokwi/wokwigw/releases)
-   [Wokwi --- Wi-Fi no ESP32](https://docs.wokwi.com/guides/esp32-wifi)
