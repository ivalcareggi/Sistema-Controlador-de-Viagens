#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <vector>
#include "path.h"
#include <string>

class City {
private:
    int id;  // Identificador único da cidade
    std::string name;  // Nome da cidade
    std::vector<Path> paths; // Caminhos saindo desta cidade

public:
    // Construtores
    City(int id, const std::string& name);
    City(const std::string& name);

    // Métodos getter
    int getId() const;
    const std::string& getName() const;
    
    void addPath(const Path& path);
    const std::vector<Path>& getPaths() const;
    const Path* findPathTo(City* destination) const;
};

#endif // CITY_H
