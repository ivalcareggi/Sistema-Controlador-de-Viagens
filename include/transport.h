#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <iostream>
#include <vector>
#include "path.h"

class Transport {
private:
    std::string name;
    bool type; // True = Terrestre e False = Aquático
    int capacity;
    int speed;
    int distrest; // Distância entre descansos
    double timerest; // Tempo de descanso
    bool available; // Indica se o transporte está disponível

public:
    Transport(const std::string &name, bool type, int capacity, int speed, int distrest, double timerest);
    std::string getName() const;
    bool getType() const;
    int getCapacity() const;
    int getSpeed() const;
    int getDistRest() const; // tempo de descanso
    double getTimerest() const; // tempo entre descansos
    bool isAvailable() const;

};

#endif 
