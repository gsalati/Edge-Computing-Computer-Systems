/*
* Diferente do Arduino .ino que inclua as bibliotecas padrões automagicamente
* Aqui precisamos incluir todas as libs que iremos utilizar
*/
/*
* Cabeçalho de fluxo de entrada e saída.
* Para printar mensagens no console, utilize:
* Utilize std::cout << "sua mensagem aqui" << std::endl
*/
#include <iostream>
#include <nlohmann/json.hpp>

// Biblioteca http estilo "header-only". Observe no arquivo CMakeLists.txt a adição do caminho para o arquivo
#include "httplib.h"

#include "apiDragoes.h"

/*
* Em um software C/C++ o ponto de entrada do software é a função main.
* i.e. a execução do software começa a partir da main.
* Observe que a função tem um retorno tipo int. 
* Finalização "normal" do programa deve retornar 0.
* Finalizações anormais são finalizadas com valores diferentes de 0.
*/
int main(int argc, char* argv[])
{
    /*
    int olaInteiro = 7;
    // Um olá mundo
    std::cout << "Olá, Fiap! \n";
    // Para printar uma variável:
    std::cout << "Print do número sete: " << olaInteiro << "\n";
    */

    std::cout << "\n------------- INICIANDO HTTP SERVER ---------\n";

    httplib::Server svr;

    // get HelloFiap: Exemplo com função lambda;
    svr.Get("/helloFiap", [](const httplib::Request &, httplib::Response &res) {
        // Define o conteúdo da resposta
        res.set_content("Hello Fiap!", "text/plain");
    });

    /**
     * @brief API de registro e consulta de dragões
     * 
     */
    svr.Post("/dragoes", postDragoes);
    svr.Get("/dragoes", getDragoes);
    svr.Get(R"(/dragoes/(\d+))", getDragaoFromId);

    std::cout << "Iniciando HTTP Server na porta 8080\n";
    std::cout << "-------------------------------------------" << std::endl;

    // Inicia o servidor HTTP e "bind" em 0.0.0.0 -> servidor está disponível em todos os IPs da máquina
    svr.listen("0.0.0.0", 8080); 

    return 0;
}