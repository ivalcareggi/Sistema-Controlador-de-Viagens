#include "city.h"

// Construtores
City::City(int id, const std::string& name) : id(id), name(name) {}

City::City(const std::string& name) : id(-1), name(name) {}

// Getter para o ID
int City::getId() const {
    return id;
}

// Getter para o nome
const std::string& City::getName() const {
    return name;
}

// Adiciona um caminho
void City::addPath(const Path& path) {
    paths.push_back(path);
}

// Retorna os caminhos
const std::vector<Path>& City::getPaths() const {
    return paths;
}

// Encontra um caminho para a cidade de destino
const Path* City::findPathTo(City* destination) const {
    for (const Path& path : paths) {
        if (path.getDestination() == destination) {
            return &path;
        }
    }
    return nullptr;
}
