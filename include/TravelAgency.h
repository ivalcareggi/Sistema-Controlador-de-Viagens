#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include "../include/DatabaseManager.h"
#include "../include/TravelArithmetic.h"
#include "../include/city.h"
#include "../include/path.h"
#include "../include/transport.h"
#include "../include/passenger.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <map>

class TravelAgency {
private:
    TravelArithmetic travelArithmetic;
    std::vector<City> cities;
    std::unordered_map<std::string, Transport> transports;
    std::vector<Passenger> passengers;
    DatabaseManager dbManager;
    bool isFinished = false; // para saber se a viagem terminou, valor padrão false até o fim de alguma viagem, quando a variavel se torna true
    int travelId;

public:
    TravelAgency(const DatabaseManager& db);
    ~TravelAgency();
    void updatePassengerLocation(Passenger& passenger, City* newLocation);
    void addCity(const City& city);
    void addPassengerToTransport(std::string& transportName, const Passenger& passenger);
    void startJourney(Passenger& passenger, const std::string& destinationName);  
    void endJourney(int travelId, Passenger& passenger);
    std::vector<Passenger>& getPassengers();
    
};

#endif 


// STATUS DA VIAGEM(ACABEI DE CRIAR), PASSAGEIROS(JA TENHO) E O ID DA CIDADE DESTINO(JA TENHO) E O ID DA VIAGEM(NÃO TENHO)