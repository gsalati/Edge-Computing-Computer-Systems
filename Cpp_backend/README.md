# Backend HTTP em C++

Este é um projeto didático de apoio aos alunos. O objetivo é demonstrar, de
forma rápida, como configurar um servidor HTTP em C++ e implementar operações
de `GET` e `POST`.

No exemplo, uma API de dragões recebe dados em JSON, registra-os em um arquivo
CSV e disponibiliza os registros por meio de uma operação `GET`. O projeto usa
as bibliotecas [cpp-httplib](third_party/cpp-httplib) para o servidor HTTP e
[nlohmann/json](https://github.com/nlohmann/json) para leitura e criação de
JSON.

## Visão geral

O programa é iniciado pela função `main`, que cria um servidor
`httplib::Server`, registra as rotas e escuta na porta `8080`.
Rotas disponíveis:

| Método | Rota | Descrição |
| --- | --- | --- |
| `GET` | `/helloFiap` | Retorna a mensagem simples `Hello Fiap!`. |
| `POST` | `/dragoes` | Valida um JSON, grava um dragão no CSV e retorna o ID criado. |
| `GET` | `/dragoes` | Lê o CSV e retorna todos os dragões em JSON. |
| `GET` | `/dragoes/{id}` | Retorna uma mensagem informando que a busca por ID ainda não foi implementada. |

### Exemplo de POST

Requisição:

```bash
curl -X POST http://localhost:8080/dragoes \
	-H "Content-Type: application/json" \
	-d '{"nome":"Banguela","montador":"Soluço","idade":10,"tamanho":8.5}'
```

Resposta esperada:

```json
{"id":1}
```

Os campos obrigatórios são `nome`, `montador`, `idade` e `tamanho`. JSON
inválido ou com algum desses campos ausente resulta em uma resposta `400`.
Quando o registro é criado, a API responde com status `201`.

### Exemplo de GET

```bash
curl http://localhost:8080/dragoes
```

A resposta é uma lista JSON, mesmo quando não há registros. Os dados são
armazenados no arquivo `dragoes.csv`, criado no diretório de execução quando
necessário. Cada linha possui o formato:

```text
id,nome,montador,idade,tamanho
```

O ID é calculado a partir do último registro existente no arquivo.

## Arquivos e funções

### `src/main.cpp`

- `main(int argc, char* argv[])`: ponto de entrada do programa. Cria o
	servidor HTTP, configura as rotas `/helloFiap` e `/dragoes`, inicia o
	atendimento na porta `8080` e retorna `0` ao finalizar normalmente.

### `src/apiDragoes.h`

Declara os manipuladores das rotas HTTP:

- `getDragoes(const httplib::Request&, httplib::Response&)`: declaração da
	função que atende `GET /dragoes`.
- `postDragoes(const httplib::Request&, httplib::Response&)`: declaração da
	função que atende `POST /dragoes`.
- `getDragaoFromId(const httplib::Request&, httplib::Response&)`: declaração da
	função que atende `GET /dragoes/{id}`.

### `src/apiDragoes.cpp`

- `postDragoes(...)`: interpreta o corpo da requisição como JSON, verifica os
	campos obrigatórios, chama `registraDragao` e devolve o novo ID. Trata JSON
	inválido com status `400` e retorna `201` quando o registro é criado.
- `getDragoes(...)`: chama `lerDragoes` e devolve todos os registros como JSON
	com status `200`.
- `getDragaoFromId(...)`: extrai o ID da URL e devolve esse ID junto com a
	mensagem `Não implementado =)`. É um ponto de extensão para uma futura busca
	individual.

### `src/registroDragoes.h`

Declara as funções responsáveis pela persistência dos dados:

- `registraDragao(...)`: grava um dragão no arquivo CSV e retorna o ID criado.
- `lerDragoes()`: lê o CSV e retorna os registros como um array JSON.

### `src/registroDragoes.cpp`

- `garanteArquivoExiste()`: verifica se `dragoes.csv` existe e o cria quando
	necessário.
- `obtemUltimoId()`: percorre o final do CSV, lê o ID do último registro e o
	retorna. Retorna `0` para um arquivo vazio e `-1` em caso de erro.
- `registraDragao(...)`: garante a existência do arquivo, calcula o próximo
	ID, abre o CSV em modo append e adiciona uma linha com os dados do dragão.
- `lerDragoes()`: lê cada linha do CSV, separa os cinco campos e monta um
	array JSON com `id`, `nome`, `montador`, `idade` e `tamanho`.

### `CMakeLists.txt`

Define o projeto CMake, exige C++20, baixa a versão `v3.11.3` de
`nlohmann/json`, adiciona os arquivos do executável `Backend_Cpp` e configura o
caminho dos headers do `cpp-httplib`.

### `build_and_run.sh`

Script auxiliar que configura o CMake, recompila o projeto e tenta iniciar um
executável. Para este backend, os comandos recomendados estão na seção
**Build & Run** abaixo.

### `THIRD_PARTY_NOTICES.md` e `LICENSES/`

Registram as bibliotecas de terceiros usadas pelo projeto e mantêm os textos
das licenças MIT correspondentes.

### `third_party/cpp-httplib/`

Contém os arquivos da biblioteca header-only `cpp-httplib`, usada para criar o
servidor HTTP.

Os diretórios e arquivos dentro de `build/` são gerados pelo CMake e não fazem
parte do código-fonte principal.

### `house_of_the_dragon.json`
Collection para o Postman com exemplo de requisições.



## Build & Run

### Build
Em um sistema _Linux_, certifique-se que o cmake está instalado
```bash
sudo apt install cmake
```

Realize o clone desse repositório e navegue até a pasta do projeto "Cpp_backend"
```bash
git clone https://github.com/gsalati/Edge-Computing-Computer-Systems
cd Edge-Computing-Computer-Systems/Cpp_backend
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

O executável estará disponível no diretório _build_.
### Run:
Para executar, execute:
```bash
./build/Backend_cpp
```