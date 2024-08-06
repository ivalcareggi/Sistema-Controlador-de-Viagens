#ifndef CITY_H
#define CITY_H

#include <iostream>

class City {
private:
    std::string name;  // Nome da cidade

public:
    // Construtor que inicializa o nome da cidade
    City(const std::string& name);

    // Método para obter o nome da cidade
    const std::string& getName() const;
};

#endif // CITY_H
