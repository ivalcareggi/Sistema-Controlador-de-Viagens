#ifndef PATH_H
#define PATH_H
#include <iostream>
#include <vector>
#include "city.h"

class City; // duvida

class Path{
private:
    double distance; 
    bool type; // True = terreste  e False = aquatico
    City& origin; 
    City& destination; // tirar duvidas sobre o uso de ponteiro e passagem por referencia
public:
    Path(City& origin, City& destination, bool type, double distance);
    City& getOrigin() const;
    City& getDestination() const;
    double getDistance() const;
    bool getType() const;
    bool havePath() const; // verificar se há trajetos
};

#endif

