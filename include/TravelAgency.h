#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include "DatabaseManager.h"
#include "TravelArithmetic.h"
#include "city.h"
#include "path.h"
#include "transport.h"
#include "passenger.h"

#include <string>
#include <vector>
#include <map>

class TravelAgency {
private:
    std::vector<City> cities;
    std::map<std::string, Transport> transports;
    std::vector<Passenger> passengers;
    DatabaseManager dbManager;

public:
    TravelAgency(const DatabaseManager& db);
    ~TravelAgency();
    
    void addCity(const City& city);
    void addPassengerToTransport(const std::string& transportName, const Passenger& passenger);
    void startJourney(Passenger& passenger, const std::string& destinationName);  
    std::vector<Passenger>& getPassengers();
    
};

#endif 
