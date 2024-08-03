
#include <iostream>
#include <vector>
#include <cmath>
#include "path.h"
#include "transport.h"  
#include "passenger.h"
#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H




class TravelAgency {
private:
    std::vector<City> cities;                // Lista de cidades
    std::vector<Path> paths;                // Lista de trajetos
    std::vector<Transport> transports;      // Lista de transportes
    std::vector<Passenger> passengers;      // Lista de passageiros

public:
    // Construtor
    TravelAgency();

    // Métodos para gerenciamento de cidades
    void addCity(const City& city);
    City findCity(const std::string& name) const;

    // Métodos para gerenciamento de trajetos
    void addPath(const Path& path);
    Path findPath(const City& origin, const City& destination) const;

    // Métodos para gerenciamento de transportes
    void addTransport(const Transport& transport);
    Transport findTransport(const std::string& name) const;

    // Métodos para gerenciamento de passageiros
    void addPassenger(const Passenger& passenger);
    Passenger findPassenger(const std::string& name) const;

    // Métodos para gestão de viagens
    void startJourney(const Passenger& passenger, const City& destination);
    void updateJourney();  // Atualiza o status das viagens em andamento
    void reportCurrentStatus() const; // Relatório do status atual das viagens

    //Métodos para cálculos
    double totaltraveltime(double distance, int speed, int distrest, int timerest) const;
    

    // Métodos de relatório
    void printPassengerReport() const;
    void printTransportReport() const;
    void printCityReport() const;
};

#endif // TRAVELAGENCY_H
