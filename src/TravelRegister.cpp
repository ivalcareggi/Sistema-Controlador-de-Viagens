
#include "../include/TravelRegister.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
// Construtor
TravelRegister::TravelRegister(TravelAgency& agency, DatabaseManager& dbManager)
    : agency(agency), dbManager(dbManager) {}

// Método para registrar cidades
void TravelRegister::registerCity() {
    std::string cityName;
    std::cout << "Enter city name: ";
    std::getline(std::cin, cityName);
    addCity(cityName);
}

// Método para registrar caminhos
void TravelRegister::registerPath() {
    std::string origin, destination;
    double distance;
    std::cout << "Enter origin city name: ";
    std::getline(std::cin, origin);
    std::cout << "Enter destination city name: ";
    std::getline(std::cin, destination);
    std::cout << "Enter distance: ";
    std::cin >> distance;
    std::cin.ignore();  // Clear newline character left in the input buffer
    addPath(origin, destination, distance);
}

// Método para registrar transportes
void TravelRegister::registerTransport() {
    std::string transportName;
    int capacity;
    bool type;
    std::cout << "Enter transport name: ";
    std::getline(std::cin, transportName);
    std::cout << "Enter capacity: ";
    std::cin >> capacity;
    std::cout << "Enter type (1 for terrestrial, 0 for aquatic): ";
    std::cin >> type;
    std::cin.ignore();  // Clear newline character left in the input buffer
    addTransport(transportName, capacity, type);
}

// Método para registrar passageiros
void TravelRegister::registerPassenger() {
    std::string passengerName, location;
    std::cout << "Enter passenger name: ";
    std::getline(std::cin, passengerName);
    std::cout << "Enter location city name: ";
    std::getline(std::cin, location);
    addPassenger(passengerName, location);
}

// Adiciona uma cidade ao banco de dados
void TravelRegister::addCity(const std::string& cityName) {
    dbManager.saveCity(cityName);
}

// Adiciona um transporte ao banco de dados
void TravelRegister::addTransport(const std::string& transportName, int capacity, bool type) {
    dbManager.saveTransport(transportName, capacity, type);
}

// Adiciona um passageiro ao banco de dados
void TravelRegister::addPassenger(const std::string& passengerName, const std::string& location) {
    dbManager.savePassenger(passengerName, location);
}

// Adiciona um caminho ao banco de dados
void TravelRegister::addPath(const std::string& origin, const std::string& destination, double distance) {
    dbManager.savePath(origin, destination, distance);
}

// Busca uma cidade pelo nome
City* TravelRegister::findCityByName(const std::string& cityName) {
    return dbManager.findCityByName(cityName);
}

// Exibe relatórios
void TravelRegister::displayReports() {
    printPassengerReport();
    printTransportReport();
    printCityReport();
}

// Imprime o relatório de passageiros
void TravelRegister::printPassengerReport() const {
    std::cout << "Passenger Report:\n";
    dbManager.listPassengers(); 
}

// Imprime o relatório de transportes
void TravelRegister::printTransportReport() const {
    std::vector<Transport> transports = dbManager.getAllTransports();
    std::cout << "Transport Report:\n";
    for (const auto& transport : transports) {
        std::cout << "Name: " << transport.getName() << ", Capacity: " << transport.getCapacity() << ", Type: " << (transport.getType() ? "Terrestrial" : "Aquatic") << "\n";
    }
}

// Imprime o relatório de cidades
void TravelRegister::printCityReport() const {
    std::vector<City> cities = dbManager.getAllCities();
    std::cout << "City Report:\n";
    for (const auto& city : cities) {
        std::cout << "ID: " << city.getId() << ", Name: " << city.getName() << "\n";
    }
}

// Lista todas as cidades
void TravelRegister::listCities() const {
    std::vector<std::string> cityNames = dbManager.getAllCityNames();
    std::cout << "List of Cities:\n";
    for (const auto& name : cityNames) {
        std::cout << name << "\n";
    }
}

// Carrega as cidades do banco de dados
void TravelRegister::loadCitiesFromDatabase() {
    std::vector<City> cities = dbManager.getAllCities();
    for (const auto& city : cities) {
        
         agency.addCity(city); 
    }
}

// Obtém a lista de passageiros
std::vector<Passenger>& TravelRegister::getPassengers() {
    
    return agency.getPassengers();
}

DatabaseManager& TravelRegister::getDatabaseManager() const {
    return dbManager;
}

Passenger* TravelRegister::findPassengerByName(const std::string& passengerName) {
    std::string name = dbManager.getPassengerName(passengerName);
    if (name.empty()) {
        return nullptr;  // Passageiro não encontrado
    }

    City* location = nullptr;
    // Suponha que você tenha uma função para obter a localização do passageiro
    int cityId = dbManager.getPassengerCityId(name);
    if (cityId > 0) {
        location = dbManager.findCityById(cityId);
    }

    return new Passenger(name, location);  // Retorna um novo objeto Passenger com a localização
}