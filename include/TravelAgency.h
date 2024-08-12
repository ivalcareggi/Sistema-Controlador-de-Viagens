#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include <string>
#include <vector>
#include <map>
#include "city.h"
#include "transport.h"
#include "passenger.h"
#include "path.h"
#include "DatabaseManager.h"

class TravelAgency {
public:
    TravelAgency(const std::string& dbName);  // Construtor que exige o nome do banco de dados
    void addCity(const City& city);
    void addTransport(const Transport& transport);
    void addPassenger(const Passenger& passenger);
    void addPath(const Path& path);
    City& findCity(const std::string& name);
    Transport& findTransport(const std::string& name);
    Passenger& findPassenger(const std::string& name);
    double totalTravelTime(double distance, int speed, int distRest, int timeRest) const;
    void addPassengerToTransport(const std::string& transportName, const Passenger& passenger);
    void startJourney(Passenger& passenger, City& destination);
   
    void printPassengerReport() const;
    void printTransportReport() const;
    void printCityReport() const;
    std::vector<City*> calculateShortestPath(const City& origin, const City& destination);
    //void loadPassengersFromDatabase();
private:
    std::vector<City> cities;
    std::map<std::string, Transport> transports;
    std::vector<Passenger> passengers;
    std::vector<Path> paths;
    DatabaseManager dbManager;

    
};

#endif // TRAVELAGENCY_H
