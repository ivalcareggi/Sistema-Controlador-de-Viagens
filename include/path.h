#ifndef PATH_H
#define PATH_H

class City;

class Path {
private:
    City* origin;               // Ponteiro para a cidade de origem
    City* destination;          // Ponteiro para a cidade de destino
    double distance;            // Distância do caminho

public:
    // Construtor
    Path(City* origin, City* destination, double distance);

    // Métodos getters
    City* getOrigin() const;
    City* getDestination() const;
    double getDistance() const;

    // Definição do operador de comparação ==
    bool operator==(const Path& other) const;
};

#endif // PATH_H

