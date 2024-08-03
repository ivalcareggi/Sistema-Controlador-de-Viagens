#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
#include "city.h" 

class Passenger {
private:
    std::string name; // Atributo nome do passageiro
    City* currentLocation; // Ponteiro para a cidade atual do passageiro >>> verificar/cuidar alocaçao de memoria

public:
    Passenger(const std::string &name);
    std::string getName() const;
    void setName(const std::string &name);
    void printInfo() const;
};

#endif 
