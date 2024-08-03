#include "transport.h"


Transport::Transport(const std::string &name, bool type, int capacity, int speed, int rest, double timerest)
    : name(name), type(type), capacity(capacity), speed(speed), rest(rest), timerest(timerest), available(true) {
   
}


std::string Transport::getName() const {
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
    return distrest;
}

double Transport::getTimerest() const {
    return timerest;
}

bool Transport::isAvailable() const {
    return available;
}