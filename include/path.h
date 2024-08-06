#ifndef PATH_H
#define PATH_H

#include "city.h"

class Path {
private:
    City origin;                 // Cidade de origem do trajeto
    City destination;            // Cidade de destino do trajeto
    double distance;             // Distância entre as cidades de origem e destino

public:
    // Construtor com parâmetros para inicializar os atributos
    Path(const City& origin, const City& destination, double distance);

    // Métodos para acessar os atributos
    const City& getOrigin() const;
    const City& getDestination() const;
    double getDistance() const;
};

#endif // PATH_H
