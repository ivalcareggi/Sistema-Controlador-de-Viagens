#include "../include/passenger.h"
#include <iostream>

// Construtor padrão
Passenger::Passenger() : name(""), currentLocation(nullptr) {}



Passenger::Passenger(const std::string& name, City* currentLocation)
    : name(name), currentLocation(currentLocation) {}


Passenger::Passenger(const std::string& name, City& currentLocation)
    : name(name), currentLocation(&currentLocation) {}

Passenger::Passenger(const std::string& name) : name(name), currentLocation(nullptr) {}


const std::string& Passenger::getName() const {
    return name;
}


void Passenger::setName(const std::string& name) {
    this->name = name;
}


City* Passenger::getCurrentLocation() const {
    return currentLocation;
}


void Passenger::setCurrentLocation(City* city) {
    currentLocation = city;
}

void Passenger::printInfo() const {
    std::cout << "Name: " << name << std::endl;
    if (currentLocation) {
        std::cout << "Localização atual: " << currentLocation->getName() << std::endl;
    } else {
        std::cout << "Localização atual não encontrada" << std::endl;
    }
}


bool Passenger::operator==(const Passenger& other) const {
    return this->name == other.name &&
           this->currentLocation == other.currentLocation;
}


bool Passenger::isOnRoute(bool onRoute) const {
    return onRoute;
}

void Passenger::setPassengerOnRoute(bool onRoute){
    this->onRoute = onRoute;
}