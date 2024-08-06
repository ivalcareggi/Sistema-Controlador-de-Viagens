#include "passenger.h"
#include <iostream>

// Construtor da classe Passenger
Passenger::Passenger(const std::string& name, City* currentLocation)
    : name(name), currentLocation(currentLocation) {}

// Retorna o nome do passageiro
const std::string& Passenger::getName() const {
    return name;
}

// Define o nome do passageiro
void Passenger::setName(const std::string& name) {
    this->name = name;
}

// Retorna a localização atual do passageiro
City* Passenger::getCurrentLocation() const {
    return currentLocation;
}

// Define a localização atual do passageiro
void Passenger::setCurrentLocation(City* city) {
    currentLocation = city;
}

// Imprime informações do passageiro
void Passenger::printInfo() const {
    std::cout << "Name: " << name << std::endl;
    if (currentLocation) {
        std::cout << "Localização atual:  " << currentLocation->getName() << std::endl;
    } else {
        std::cout << "Localização atual não encontrada" << std::endl;
    }
}
bool Passenger::operator==(const Passenger& other) const {
    // Compara pelo nome e pela localização atual
    return this->name == other.name &&
           this->currentLocation == other.currentLocation;
}