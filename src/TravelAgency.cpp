#include "TravelAgency.h"
#include <iostream>
#include <stdexcept>

// Construtor
TravelAgency::TravelAgency() {}

// Adiciona uma nova cidade
void TravelAgency::addCity(const City& city) {
    cities.push_back(city);
}

// Adiciona um novo transporte
void TravelAgency::addTransport(const Transport& transport) {
    transports[transport.getName()] = transport;
}

// Adiciona um novo passageiro
void TravelAgency::addPassenger(const Passenger& passenger) {
    passengers.push_back(passenger);
}

// Adiciona um novo trajeto
void TravelAgency::addPath(const Path& path) {
    paths.push_back(path);
}

// Encontrar cidade pelo nome
City& TravelAgency::findCity(const std::string& name) {
    for (auto& city : cities) {
        if (city.getName() == name) {
            return city;
        }
    }
    throw std::runtime_error("Cidade não encontrada.");
}

// Encontrar transporte pelo nome
Transport& TravelAgency::findTransport(const std::string& name) {
    auto it = transports.find(name);
    if (it != transports.end()) {
        return it->second;  // 'it->second' é o objeto Transport
    }
    throw std::runtime_error("Transporte não encontrado.");
}

// Encontrar passageiro pelo nome
Passenger& TravelAgency::findPassenger(const std::string& name) {
    for (auto& passenger : passengers) {
        if (passenger.getName() == name) {
            return passenger;
        }
    }
    throw std::runtime_error("Passageiro não encontrado.");
}

// Calcula o tempo total de viagem
double TravelAgency::totalTravelTime(double distance, int speed, int distRest, int timeRest) const {
    if (speed <= 0) {
        throw std::invalid_argument("Velocidade deve ser positiva.");
    }
    double travelTime = distance / speed;
    double restTime = (distance / distRest) * timeRest;
    return travelTime + restTime;
}

void TravelAgency::addPassengerToTransport(const std::string& transportName, const Passenger& passenger) {
    auto it = transports.find(transportName);
    if (it != transports.end()) {
        it->second.addPassenger(passenger);
    } else {
        std::cerr << "Transporte não encontrado!" << std::endl;
    }
}


// Inicia uma jornada
#include <iostream>
#include <map>
#include <string>
#include <vector>

void TravelAgency::startJourney(Passenger& passenger, City& destination) {
    City* currentLocation = passenger.getCurrentLocation();
    if (!currentLocation) {
        std::cerr << "Passageiro não possui localização" << std::endl;
        return;
    }

    // Busca o trajeto entre a localização atual e o destino
    for (const auto& path : paths) {
        if (path.getOrigin().getName() == currentLocation->getName() &&
            path.getDestination().getName() == destination.getName()) {

            std::map<std::string, Transport*> availableTransports;

            // Listar transportes disponíveis
            std::cout << "Transportes disponíveis:" << std::endl;
            for (auto& [key, transport] : transports) {
                if (transport.isAvailable()) {
                    std::cout << transport.getName() 
                              << " (Capacidade: " << transport.getCapacity() << ")" << std::endl;
                    availableTransports[transport.getName()] = &transport;
                }
            }

            if (availableTransports.empty()) {
                std::cerr << "Sem transportes disponíveis." << std::endl;
                return;
            }

            // Solicitar seleção do usuário
            std::string selection;
            std::cout << "Insira o transporte desejado: ";
            std::cin >> selection;

            // Verificar se o transporte existe e está disponível
            if (availableTransports.find(selection) == availableTransports.end()) {
                std::cerr << "Seleção inválida. Transporte indisponivel ou inexistente" << std::endl;
                return;
            }

            // Selecionar transporte com base na escolha do usuário
            Transport* selectedTransport = availableTransports[selection];

            // Marcar o transporte como indisponível e adicionar o passageiro
            selectedTransport->setAvailable(false);
            selectedTransport->addPassenger(passenger);

            std::cout << "Viagem de  " << currentLocation->getName() << " para " << destination.getName() 
                      << " usando  " << selectedTransport->getName() << std::endl;

            // Implemente a lógica de viagem aqui

            return;
        }
    }

    std::cerr << "Nenhum trajeeto encontrado para as cidades inseridas." << std::endl;
}


// Imprime relatório de passageiros
void TravelAgency::printPassengerReport() const {
    std::cout << "Dados dos passageiros:" << std::endl;
    for (const auto& passenger : passengers) {
        passenger.printInfo();
        std::cout << std::endl;
    }
}

// Imprime relatório de transportes
void TravelAgency::printTransportReport() const {
    std::cout << "Dados dos transportes:" << std::endl;
    for (const auto& pair : transports) {
        const Transport& transport = pair.second;
        std::cout << "Nome: " << transport.getName() << std::endl;
        std::cout << "Tipo: " << (transport.getType() ? "Terrestre" : "Aquatico") << std::endl;
        std::cout << "Capacidade: " << transport.getCapacity() << std::endl;
        std::cout << "Velocidade: " << transport.getSpeed() << std::endl;
        std::cout << "Distancia entre descansos: " << transport.getDistRest() << std::endl;
        std::cout << "Tempo de descanso: " << transport.getTimerest() << std::endl;
        std::cout << "Disponível: " << (transport.isAvailable() ? "Sim" : "Não") << std::endl;
        std::cout << std::endl;
    }
}

// Imprime relatório de cidades
void TravelAgency::printCityReport() const {
    std::cout << "City Report:" << std::endl;
    for (const auto& city : cities) {
        std::cout << "City: " << city.getName() << std::endl;
    }
}
