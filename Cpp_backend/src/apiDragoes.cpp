#include "apiDragoes.h"
#include "registroDragoes.h"

// --------------------------------------------------------------------//
void postDragoes(const httplib::Request& req, httplib::Response& res){
    nlohmann::json dados;
    nlohmann::json resposta;

    std::cout << "POST Dragão recebido" << std::endl;
    std::cout << req.body;
    
    // Converte o body para JSON
    try{
        dados = nlohmann::json::parse(req.body);
    }
    catch(const nlohmann::json::parse_error&){
        res.status = 400;
        res.set_content(
            R"({"erro":"JSON invalido"})",
            "application/json"
        );

        return; // Retorno da função lambda
    }

    // Resposta
    // Verifica que todos os dados obrigatórios foram recebidos
    if(!dados.contains("nome") || !dados.contains("montador") || !dados.contains("idade") || !dados.contains("tamanho")){
        resposta["erro"] = "Algum campo obrigatório não foi encontrado";
        
        res.status = 400;
        res.set_content(resposta.dump(), "application/json");
        return; // Retorno da função lambda
    }

    // Para o exemplo, os valor "", 0 e 0.0f são valores padrões casos os campos fossem opcionais
    std::string nome = dados.value("nome", "");
    std::string montador = dados.value("montador", "");
    int idade = dados.value("idade", 0);
    float tamanho = dados.value("tamanho", 0.0f);

    //std::endl coloca um \n e "flusha" o buffer de saída
    std::cout << "Dragão: " << nome << "\nMontador: " << montador << "\nIdade: " << idade << "\nTamanho: " << tamanho << std::endl;
    int id = registraDragao(nome, montador, idade, tamanho);
    resposta["id"] = id;
    res.status = 201;
    res.set_content(resposta.dump(), "application/json");

    return;
}
// --------------------------------------------------------------------//
void getDragoes(const httplib::Request& req, httplib::Response& res){
    std::cout << "GET Dragões recebido! \n";
    auto resposta = lerDragoes();

    res.status = 200;
    res.set_content(resposta.dump(), "application/json");

    return;
}
// --------------------------------------------------------------------//
void getDragaoFromId(const httplib::Request& req, httplib::Response& res){
    int id = std::stoi(req.matches[1]);
    nlohmann::json resposta;
    resposta["mensage"] = "Não implementado =)";
    resposta["id"] = id;

    res.status = 200;
    res.set_content(resposta.dump(), "application/json");

    return;
}
