#include "transport.h"
#include <algorithm>
#include <iostream>

Transport::Transport() 
    : name(""), type(false), capacity(0), speed(0), distRest(0), timeRest(0) {}

Transport::Transport(const std::string& name, bool type, int capacity, int speed, int distRest, int timeRest)
    : name(name), type(type), capacity(capacity), speed(speed), distRest(distRest), timeRest(timeRest), available(true) {}

const std::string& Transport::getName() const {
    return name;
}
bool Transport::getType() const {
    return type;
}

int Transport::getCapacity() const {
    return capacity;
}

int Transport::getSpeed() const {
    return speed;
}

int Transport::getDistRest() const {
    return distRest;
}

int Transport::getTimerest() const {
    return timeRest;
}

bool Transport::isAvailable() const {
    return available;
}

void Transport::setName(const std::string& name) {
    this->name = name;
}

void Transport::setType(bool type) {
    this->type = type;
}

void Transport::setCapacity(int capacity) {
    this->capacity = capacity;
}

void Transport::setSpeed(int speed) {
    this->speed = speed;
}

void Transport::setDistRest(int distRest) {
    this->distRest = distRest;
}

void Transport::setTimerest(int timeRest) {
    this->timeRest = timeRest;
}

void Transport::setAvailable(bool available) {
    this->available = available;
}

void Transport::addPassenger(const Passenger& passenger) {
    if (passengers.size() < static_cast<std::vector<Passenger>::size_type>(capacity)) {
        passengers.push_back(passenger);
    } else {
        std::cout << "Transporte lotado, tente novamente!" << std::endl;
    }
}

void Transport::removePassenger(const Passenger& passenger) {
    auto it = std::remove(passengers.begin(), passengers.end(), passenger);
    passengers.erase(it, passengers.end());
}
