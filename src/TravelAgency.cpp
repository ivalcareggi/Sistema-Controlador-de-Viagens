#include "../include/TravelAgency.h"
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <sstream>
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

std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time_t);

    std::stringstream ss;
    ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
void TravelAgency::addPassengerToTransport(std::string& transportName, const Passenger& passenger) {
    // Exibir a lista de transportes disponíveis
    std::vector<Transport> transportsList = dbManager.getAllTransports(); // Certifique-se de ter implementado este método
    std::cout << "Transportes disponíveis:\n";
    for (const auto& transport : transportsList) {
        std::cout << "Nome: " << transport.getName() 
                  << " (Capacidade: " << transport.getCapacity() << ")\n";
    }

    // Solicitar ao usuário que selecione um transporte
    std::cout << "Digite o nome do transporte desejado: ";
    std::cin >> transportName;

    // Buscar o transporte pelo nome no banco de dados
    Transport selectedTransport = dbManager.getTransportByName(transportName);

    if (!selectedTransport.getName().empty()) { // Verifica se o transporte foi encontrado
        // Verificar se há capacidade disponível
        if (selectedTransport.getCurrentOccupancy() < selectedTransport.getCapacity()) {
            // Adicionar o passageiro ao transporte
            selectedTransport.addPassenger(passenger);
            std::cout << "Passageiro adicionado ao transporte " << transportName << ".\n";

            // Atualizar o map de transportes na TravelAgency
            transports[transportName] = selectedTransport;
        } else {
            std::cout << "O transporte está cheio. Não é possível adicionar mais passageiros.\n";
        }
    } else {
        std::cout << "Transporte não encontrado.\n";
        transportName.clear(); // Limpar o nome do transporte para indicar falha
    }
}

void TravelAgency::updatePassengerLocation(Passenger& passenger, City* newLocation) {
    if (newLocation != nullptr) {
        // Atualiza a localização atual do passageiro
        passenger.setCurrentLocation(newLocation);

        // Atualiza a localização no banco de dados
        dbManager.updatePassengerLocation(passenger.getName(), newLocation->getId());
    }
}

void TravelAgency::startJourney(Passenger& passenger, const std::string& destinationName) {
    City* currentLocation = passenger.getCurrentLocation();
    if (!currentLocation) {
        std::cerr << "Passageiro não possui localização" << std::endl;
        std::cout << "AAAAAAAAAAAAAAAAAA" << std::endl;
        std::cout << "Nome do Passageiro: " << passenger.getName() << std::endl;
        return;
    }

    // Encontra a cidade de destino usando dbManager
    City* destinationCity = dbManager.findCityByName(destinationName);
    if (!destinationCity) {
        std::cerr << "Cidade de destino não encontrada" << std::endl;
        return;
    }

    // Calcula a melhor rota usando TravelArithmetic
   // std::vector<City*> shortestPath = travelArithmetic.calculateShortestPath(*currentLocation, *destinationCity, cities);
  // double totalDistance = 0.0;
    // Calcula a distância total da rota
/*    double totalDistance = 0.0;
    for (size_t i = 0; i < shortestPath.size() - 1; ++i) {
        for (const auto& path : shortestPath[i]->getPaths()) {
            if (path.getDestination() == shortestPath[i + 1]) {
                totalDistance += path.getDistance();
                break;
            }
        }
    }  */

    // Exibe a lista de transportes disponíveis e solicita ao usuário que selecione um
    std::string selectedTransportName;
    addPassengerToTransport(selectedTransportName, passenger);

    // Verifica se o nome do transporte foi corretamente definido
    if (selectedTransportName.empty()) {
        std::cerr << "Nenhum transporte foi selecionado." << std::endl;
        return;
    }

    // Recolhe o transporte escolhido usando o nome do transporte
    Transport* selectedTransport = nullptr;
    auto it = transports.find(selectedTransportName);
    if (it != transports.end()) {
        selectedTransport = &it->second;
    } else {
        std::cerr << "Transporte " << selectedTransportName << " não encontrado." << std::endl;
        return;
    }

    // Verifica se o transporte está disponível
    if (!selectedTransport->isAvailable()) {
        std::cerr << "Transporte " << selectedTransportName << " não está disponível" << std::endl;
        return;
    }
    double totalDistance = dbManager.getPathDistance(currentLocation->getName(), destinationCity->getName());

    if (totalDistance <= 0) {
        std::cerr << "Distância inválida entre as cidades" << std::endl;
        return;
    }

    // Solicita ao usuário a velocidade, tempo de descanso e distância entre os descansos
    int speed, distRest, timeRest;
    std::cout << "Por favor, forneça a velocidade do transporte (km/h): ";
    std::cin >> speed;
    std::cout << "Por favor, forneça a distância entre os descansos (km): ";
    std::cin >> distRest;
    std::cout << "Por favor, forneça o tempo de descanso (horas): ";
    std::cin >> timeRest;

    // Marca o transporte como em trânsito e indisponível
    selectedTransport->setInTransit(true);
    selectedTransport->setAvailable(false);

    // Calcula o tempo total de viagem
    double travelTime = travelArithmetic.totalTravelTime(totalDistance, speed, distRest, timeRest);

    // Atualiza o estado do passageiro e do transporte
    passenger.setPassengerOnRoute(true);
    passenger.setCurrentLocation(destinationCity);

    // Atualiza o banco de dados, se necessário
    std::string starttimestamp = getCurrentTimestamp(); // Obtém o timestamp atual
    dbManager.saveTravel(selectedTransport->getId(), currentLocation->getId(), destinationCity->getId(), starttimestamp);

    std::cout << "Viagem iniciada. Tempo estimado de viagem: " << travelTime << " horas." << std::endl;

    std::string endTimestamp = getCurrentTimestamp();
    dbManager.updateTravelEndTime(travelId, endTimestamp);
}