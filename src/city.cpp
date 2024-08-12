#include "city.h"

// Construtor que inicializa o nome da cidade
City::City(const std::string& name) : name(name) {}

// Método para obter o nome da cidade
const std::string& City::getName() const {
    return name;
}

// Adiciona um caminho à cidade
void City::addPath(const Path& path) {
    paths.push_back(path);
}

// Retorna os caminhos saindo desta cidade
const std::vector<Path>& City::getPaths() const {
    return paths;
}
