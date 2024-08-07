#include "path.h"

// construtor da classe Path
Path::Path(const City& origin, const City& destination, double distance)
    : origin(origin), destination(destination), distance(distance) {}

// retorna a cidade de origem do trajeto
const City& Path::getOrigin() const {
    return origin;
}

// retorna a cidade de destino do trajeto
const City& Path::getDestination() const {
    return destination;
}

// retorna a distância entre as cidades de origem e destino
double Path::getDistance() const {
    return distance;
}

