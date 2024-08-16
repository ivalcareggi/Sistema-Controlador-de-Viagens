#include "TravelAgency.h"
#include <algorithm>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <iostream>

TravelAgency::TravelAgency(const DatabaseManager& db) : dbManager(db) {}

TravelAgency::~TravelAgency() {}

void TravelAgency::addCity(const City& city) {
    cities.push_back(city);
}

std::vector<Passenger>& TravelAgency::getPassengers() {
    return passengers;
}

void TravelAgency::addPassengerToTransport(const std::string& transportName, const Passenger& passenger) {
    // Exibir a lista de transportes disponíveis
    std::cout << "Transportes disponíveis:\n";
    for (const auto& transportPair : transports) {
        const Transport& transport = transportPair.second;
        std::cout << "Nome: " << transportPair.first 
                  << " (Capacidade: " << transport.getCapacity() << ")\n";
    }

    // Solicitar ao usuário que selecione um transporte
    std::string selectedTransportName;
    std::cout << "Digite o nome do transporte desejado: ";
    std::cin >> selectedTransportName;

    // Verificar se o transporte existe
    auto it = transports.find(selectedTransportName);
    if (it != transports.end()) {
        Transport& selectedTransport = it->second;

        // Verificar se há capacidade disponível
        if (selectedTransport.getCurrentOccupancy() < selectedTransport.getCapacity()) {
            // Adicionar o passageiro ao transporte
            selectedTransport.addPassenger(passenger);
            std::cout << "Passageiro adicionado ao transporte " << selectedTransportName << ".\n";
        } else {
            std::cout << "O transporte está cheio. Não é possível adicionar mais passageiros.\n";
        }
    } else {
        std::cout << "Transporte não encontrado.\n";
    }
}