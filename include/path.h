#ifndef PATH_H
#define PATH_H

class City;  

class Path {
private:
    City* origin;               
    City* destination;
    double distance;

public:
    // Construtor com parâmetros para inicializar os atributos
    Path(City* origin, City* destination, double distance);

    // Métodos para acessar os atributos
    City* getOrigin() const;
    City* getDestination() const;
    double getDistance() const;
};

#endif // PATH_H