#ifndef REGISTRO_DRAGOES_H
#define REGISTRO_DRAGOES_H

#include <string>
#include <nlohmann/json.hpp>

int registraDragao(
    const std::string& nome,
    const std::string& montador,
    int idade,
    float tamanho
);

nlohmann::json lerDragoes();

#endif