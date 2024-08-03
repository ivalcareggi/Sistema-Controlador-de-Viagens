#ifndef CITY_H
#define CITY_H

#include <string>
#include <vector>
#include "path.h"

class Path; // duvida

class City {
private:
    std::string name;
    std::vector<Path*> paths; // Trajetos conectados à cidade

public:
    City(const std::string &name);
    std::string getName() const;
    void addPath(Path* path);
    std::vector<Path*> getPaths() const;
};

#endif 

