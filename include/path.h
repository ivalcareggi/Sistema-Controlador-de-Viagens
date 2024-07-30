#ifndef PATH_H
#define PATH_H
#include <iostream>
#include <vector>
#include "city.h"

class Path{
private:
    double distance; 
    bool type; // True = terreste  e False = aquatico
    City origin;
    City destination;
public:
    Path(City origin, City destination, bool type, double distance) : origin(origin), destination(destination), type(type), distance(distance){};
    City getOrigin();
    City getDestination();
    double getDistance();
    bool getType();
    bool havePath(); // verificar
};

#endif

