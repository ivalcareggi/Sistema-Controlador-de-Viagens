#include "../include/transport.h"
#include <algorithm>
#include <iostream>

Transport::Transport() 
    : name(""), type(false), capacity(0), speed(0), distRest(0), timeRest(0), available(true), currentLocation(nullptr) {}

Transport::Transport(const std::string& name, bool type, int capacity, int speed, int distRest, int timeRest)
    : name(name), type(type), capacity(capacity), speed(speed), distRest(distRest), timeRest(timeRest), available(true), currentLocation(nullptr) {}



Transport::Transport(int id, const std::string& name, bool type, int capacity)
    : name(name), type(type), capacity(capacity), speed(0), distRest(0), timeRest(0), available(true), id(id), currentLocation(nullptr) {
}
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

bool Transport::isInTransit()const{
    return inTransit;
}

City* Transport::getCurrentLocation() const {
    return currentLocation;
}

int Transport::getCurrentOccupancy() const {
    return occupancy;
}

int Transport::getId() const {
    return id;
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

void Transport::setInTransit(bool inTransit){
    this->inTransit = inTransit;
}

void Transport::setCurrentLocation(City* location) {
    currentLocation = location;
}

void Transport::addPassenger(const Passenger& passenger) {
    if (occupancy < capacity) {
        passengers.push_back(passenger);
        ++occupancy;  
    }
}
void Transport::removePassenger(const Passenger& passenger) {
    auto it = std::remove(passengers.begin(), passengers.end(), passenger);
    if (it != passengers.end()) {
        passengers.erase(it, passengers.end());
    }
}
