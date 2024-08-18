// TravelRegister.h

#ifndef TRAVELREGISTER_H
#define TRAVELREGISTER_H

#include <string>
#include <vector>
#include "../include/TravelAgency.h"
#include "../include/DatabaseManager.h"

class TravelRegister {
private:
    TravelAgency& agency;  // Referência para a agência de viagens
    DatabaseManager& dbManager;  // Referência para o gerenciador do banco de dados

public:
    // Construtor que inicializa as referências para a agência e o banco de dados
    TravelRegister(TravelAgency& agency, DatabaseManager& dbManager);

    // Métodos para registrar diferentes entidades
    void registerCity();
    void registerPath();
    void registerTransport();
    void registerPassenger();

    // Métodos auxiliares para adicionar dados
    void addCity(const std::string& cityName);
    void addTransport(const std::string& transportName, int capacity, bool type);
    void addPassenger(const std::string& passengerName, const std::string& location);
    void addPath(const std::string& origin, const std::string& destination, double distance);

    // Métodos de busca
    City* findCityByName(const std::string& cityName);
    Passenger* findPassengerByName(const std::string& passengerName);

    // Método para exibir relatórios
    void displayReports();
    
    // Métodos auxiliares para gerar relatórios
    void printPassengerReport() const;
    void printTransportReport() const;
    void printCityReport() const;
    void listCities() const;

    // Métodos de carregamento
    void loadCitiesFromDatabase(); 
    std::vector<Passenger>& getPassengers();  
    DatabaseManager& getDatabaseManager() const;
};

#endif // TRAVELREGISTER_H
