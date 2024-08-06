#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include "city.h"
#include <string>

class Passenger {
private:
    std::string name;           // Nome do passageiro
    City* currentLocation;      // Localização atual do passageiro

public:
    // Construtor com parâmetros para inicializar os atributos
    Passenger(const std::string& name, City* currentLocation);

    // Métodos para acessar e modificar o nome do passageiro
    const std::string& getName() const;
    void setName(const std::string& name);

    // Métodos para acessar e modificar a localização atual do passageiro
    City* getCurrentLocation() const;
    void setCurrentLocation(City* city);

    //operador de comparaçao
    bool operator==(const Passenger& other) const;

    // Método para imprimir informações do passageiro
    void printInfo() const;
};

#endif // PASSENGER_H
