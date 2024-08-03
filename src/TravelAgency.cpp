#include "TravelAgency.h"
#include <algorithm>

// Construtor da classe TravelAgency
TravelAgency::TravelAgency() {
   
}
double TravelAgency::totaltraveltime(double distance, int speed, int distrest, int timerest) const{
    if (speed <= 0 || distrest <= 0 || timerest < 0) {
        throw std::invalid_argument("valores inválidos.");
    }
    double traveltime = distance / speed;
    int restsnumber = std::ceil(distance / distrest) - 1;
    double totalresttime = restsnumber * timerest;
    double totaltraveltime = traveltime + totalresttime;
    
    return totaltraveltime;
}


// Métodos para gerenciamento de cidades
void TravelAgency::addCity(const City& city) {
    cities.push_back(city);
}

City TravelAgency::findCity(const std::string& name) const {
    for (const auto& city : cities) {
        if (city.getName() == name) {
            return city;
        }
    }
    throw std::runtime_error("cidade não encontrada");
}

// Métodos para gerenciamento de trajetos
void TravelAgency::addPath(const Path& path) {
    paths.push_back(path);
}

Path TravelAgency::findPath(const City& origin, const City& destination) const {
    for (const auto& path : paths) {
        if (path.getOrigin().getName() == origin.getName() &&
            path.getDestination().getName() == destination.getName()) {
            return path;
        }
    }
    throw std::runtime_error("trajeto não encontrado");
}

// Métodos para gerenciamento de transportes
void TravelAgency::addTransport(const Transport& transport) {
    transports.push_back(transport);
}

Transport TravelAgency::findTransport(const std::string& name) const {
    for (const auto& transport : transports) {
        if (transport.getName() == name) {
            return transport;
        }
    }
    throw std::runtime_error("transporte não encontrado");
}

// Métodos para gerenciamento de passageiros
void TravelAgency::addPassenger(const Passenger& passenger) {
    passengers.push_back(passenger);
}

Passenger TravelAgency::findPassenger(const std::string& name) const {
    for (const auto& passenger : passengers) {
        if (passenger.getName() == name) {
            return passenger;
        }
    }
    throw std::runtime_error("Passenger not found");
}

// Métodos para gestão de viagens
void TravelAgency::startJourney(const Passenger& passenger, const City& destination) {
    
 
}

void TravelAgency::updateJourney() {
    // Implementar lógica para atualizar status das viagens

}

void TravelAgency::reportCurrentStatus() const {
    // Relatar o status atual das viagens
    std::cout << "Current status of journeys:" << std::endl;
    // Exibir informações relevantes
}

// Relatórios
void TravelAgency::printPassengerReport() const {
    std::cout << "Passenger Report:" << std::endl;
    for (const auto& passenger : passengers) {
        passenger.printInfo();
    }
}

void TravelAgency::printTransportReport() const {
    std::cout << "Transport Report:" << std::endl;
    for (const auto& transport : transports) {
        std::cout << "Name: " << transport.getName() << std::endl;
        std::cout << "Type: " << (transport.getType() ? "Terrestre" : "Aquático") << std::endl;
        std::cout << "Capacity: " << transport.getCapacity() << std::endl;
        std::cout << "Speed: " << transport.getSpeed() << std::endl;
        std::cout << "Rest Distance: " << transport.getRest() << std::endl;
        std::cout << "Rest Time: " << transport.getTimerest() << std::endl;
    }
}

void TravelAgency::printCityReport() const {
    std::cout << "City Report:" << std::endl;
    for (const auto& city : cities) {
        std::cout << "City Name: " << city.getName() << std::endl;
        // Imprimir mais informações conforme o andamento do projeto
    }
}
