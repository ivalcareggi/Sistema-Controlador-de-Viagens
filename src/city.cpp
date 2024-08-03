#include "city.h"

// Construtor
City::City(const std::string &name) : name(name) {}


std::string City::getName() const {
    return name;
}


void City::addPath(Path* path) {
    paths.push_back(path);
}

// Retorna todos os trajetos conectados à cidade
std::vector<Path*> City::getPaths() const {
    return paths;
}