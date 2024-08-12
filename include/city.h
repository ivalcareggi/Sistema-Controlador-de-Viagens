
#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <vector>
#include "path.h"

class City {
private:
    std::string name;  // Nome da cidade
    std::vector<Path> paths; // Caminhos saindo desta cidade

public:
    // Construtor que inicializa o nome da cidade
    City(const std::string& name);

    // Método para obter o nome da cidade
    const std::string& getName() const;

    // Adiciona um caminho à cidade
    void addPath(const Path& path);

    // Retorna os caminhos saindo desta cidade
    const std::vector<Path>& getPaths() const;

  
};

#endif // CITY_H