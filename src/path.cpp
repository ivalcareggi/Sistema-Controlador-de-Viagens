#include "path.h"
#include "city.h"

// Implementação das funções da classe Path
Path::Path(City* origin, City* destination, double distance)
    : origin(origin), destination(destination), distance(distance) {}

City* Path::getOrigin() const {
    return origin;
}

City* Path::getDestination() const {
    return destination;
}

double Path::getDistance() const {
    return distance;
}