#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "city.h"
#include "passenger.h"
#include "transport.h"
#include "path.h"

class TravelAgency {
private:
    std::vector<City> cities;
    std::map<std::string, Transport> transports;
    std::vector<Passenger> passengers;
    std::vector<Path> paths;

public:
    TravelAgency();

    void addCity(const City& city);
    void addTransport(const Transport& transport);
    void addPassenger(const Passenger& passenger);
    void addPath(const Path& path);
    void addPassengerToTransport(const std::string& transportName, const Passenger& passenger);

    City& findCity(const std::string& name);
    Transport& findTransport(const std::string& name);
    Passenger& findPassenger(const std::string& name);

    double totalTravelTime(double distance, int speed, int distRest, int timeRest) const;
    void startJourney(Passenger& passenger, City& destination);

    void printPassengerReport() const;
    void printTransportReport() const;
    void printCityReport() const;
};

#endif // TRAVELAGENCY_H
