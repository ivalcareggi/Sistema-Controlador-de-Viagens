#include "path.h"

// Construtor da classe Path
Path::Path(const City& origin, const City& destination, double distance)
    : origin(origin), destination(destination), distance(distance) {}

// Retorna a cidade de origem do trajeto
const City& Path::getOrigin() const {
    return origin;
}

// Retorna a cidade de destino do trajeto
const City& Path::getDestination() const {
    return destination;
}

// Retorna a distância entre as cidades de origem e destino
double Path::getDistance() const {
    return distance;
}

