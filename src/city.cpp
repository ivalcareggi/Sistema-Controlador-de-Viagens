#include "city.h"

// Construtor da classe City
City::City(const std::string& name) : name(name) {}

// Retorna o nome da cidade
const std::string& City::getName() const {
    return name;
}
