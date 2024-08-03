#include "path.h"
// Construtor da classe Path


Path::Path(City& origin, City& destination, bool type, double distance)
    : origin(origin), destination(destination), type(type), distance(distance) {}

City& Path::getOrigin() const {
    return origin;
}

City& Path::getDestination() const {
    return destination;
}

double Path::getDistance() const {
    return distance;
}

bool Path::getType() const {
    return type;
}

bool Path::havePath() const {
    
    return distance > 0; 
}

