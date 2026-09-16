#include "registroDragoes.h"

#include <fstream>
#include <string>

    const char* ARQUIVO_DRAGOES = "dragoes.csv";

bool garanteArquivoExiste()
{
    std::ifstream arquivo(ARQUIVO_DRAGOES);

    if (arquivo.good()) {
        return true;
    }

    // Não existe, então cria.
    std::ofstream novoArquivo(ARQUIVO_DRAGOES);

    return novoArquivo.good();
}

int obtemUltimoId()
{
    std::ifstream arquivo(ARQUIVO_DRAGOES);

    if (!arquivo.is_open()) {
        return -1;
    }

    // Vai para o final do arquivo.
    arquivo.seekg(0, std::ios::end);

    // Arquivo vazio.
    if (arquivo.tellg() == 0) {
        return 0;
    }

    // Começamos no último caractere.
    arquivo.seekg(-1, std::ios::end);

    char caractere;

    // Se o arquivo termina com '\n', ignoramos.
    arquivo.get(caractere);

    if (caractere == '\n') {
        arquivo.seekg(-2, std::ios::end);
    }

    // Voltamos até encontrar o início da última linha.
    while (arquivo.tellg() > 0) {
        arquivo.get(caractere);

        if (caractere == '\n') {
            break;
        }

        arquivo.seekg(-2, std::ios::cur);
    }

    // Agora estamos no início da última linha.
    // O primeiro campo é o ID.
    std::string idTexto;

    std::getline(arquivo, idTexto, ',');

    if (idTexto.empty()) {
        return -1;
    }

    try {
        return std::stoi(idTexto);
    }
    catch (...) {
        return -1;
    }
}



int registraDragao(
    const std::string& nome,
    const std::string& montador,
    int idade,
    float tamanho
) {
    // Garante que o arquivo exista.
    if (!garanteArquivoExiste()) {
        return -1;
    }

    // Obtém o ID da última linha.
    int ultimoId = obtemUltimoId();

    if (ultimoId < 0) {
        return -1;
    }

    int novoId = ultimoId + 1;

    // Abre em modo append para escrever no final.
    std::ofstream arquivo(
        ARQUIVO_DRAGOES,
        std::ios::app
    );

    if (!arquivo.is_open()) {
        return -1;
    }

    arquivo << novoId << ","
            << nome << ","
            << montador << ","
            << idade << ","
            << tamanho << "\n";

    if (!arquivo.good()) {
        return -1;
    }

    return novoId;
}

nlohmann::json lerDragoes()
{
    nlohmann::json dragoes = nlohmann::json::array();

    std::ifstream arquivo(ARQUIVO_DRAGOES);

    if (!arquivo.is_open()) {
        return dragoes;
    }

    std::string linha;

    while (std::getline(arquivo, linha)) {
        if (linha.empty()) {
            continue;
        }

        std::stringstream ss(linha);

        std::string id;
        std::string nome;
        std::string montador;
        std::string idade;
        std::string tamanho;

        // Lê os cinco campos separados por vírgula
        std::getline(ss, id, ',');
        std::getline(ss, nome, ',');
        std::getline(ss, montador, ',');
        std::getline(ss, idade, ',');
        std::getline(ss, tamanho, ',');

        nlohmann::json dragao = {
            {"id", std::stoi(id)},
            {"nome", nome},
            {"montador", montador},
            {"idade", std::stoi(idade)},
            {"tamanho", std::stof(tamanho)}
        };

        dragoes.push_back(dragao);
    }

    return dragoes;
}