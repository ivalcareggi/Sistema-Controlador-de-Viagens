#include "passenger.h"
#include <iostream>


Passenger::Passenger(const std::string &name)
    : name(name), currentLocation(nullptr) {}


std::string Passenger::getName() const {
    return name;
}

void Passenger::setName(const std::string &name) {
    this->name = name;
}


void Passenger::printInfo() const {
    std::cout << "Name: " << name << std::endl;
 
    if (currentLocation != nullptr) {
        std::cout << "Current Location: " << currentLocation->getName() << std::endl;
    } else {
        std::cout << "Current Location: Unknown" << std::endl;
    }
}
