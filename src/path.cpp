#include "../include/path.h"
#include "../include/city.h"

// Construtor
Path::Path(City* origin, City* destination, double distance)
    : origin(origin), destination(destination), distance(distance) {}

// Métodos getters
City* Path::getOrigin() const {
    return origin;
}

City* Path::getDestination() const {
    return destination;
}

double Path::getDistance() const {
    return distance;
}


bool Path::operator==(const Path& other) const {
    return origin == other.origin &&
           destination == other.destination &&
           distance == other.distance;
}
