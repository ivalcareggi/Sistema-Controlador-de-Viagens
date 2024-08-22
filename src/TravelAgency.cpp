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
        return;
    }

    City* destinationCity = dbManager.findCityByName(destinationName);
    if (!destinationCity) {
        std::cerr << "Cidade de destino não encontrada" << std::endl;
        return;
    }

    // Calcula a melhor rota usando TravelArithmetic
    std::vector<City*> shortestPath = travelArithmetic.calculateShortestPath(*currentLocation, *destinationCity, cities);
 
    // Calcula a distância total da rota
    double totalDistance = 0.0;
    for (size_t i = 0; i < shortestPath.size() - 1; ++i) {
        for (const auto& path : shortestPath[i]->getPaths()) {
            if (path.getDestination() == shortestPath[i + 1]) {
                totalDistance += path.getDistance();
                break;
            }
        }
    }  

    // Exibe a lista de transportes disponíveis e solicita ao usuário que selecione um
  std::string selectedTransportName;
    addPassengerToTransport(selectedTransportName, passenger);

    if (selectedTransportName.empty()) {
        std::cerr << "Nenhum transporte foi selecionado." << std::endl;
        return;
    }

    Transport* selectedTransport = nullptr;
    auto it = transports.find(selectedTransportName);
    if (it != transports.end()) {
        selectedTransport = &it->second;
    } else {
        std::cerr << "Transporte " << selectedTransportName << " não encontrado." << std::endl;
        return;
    }

    if (!selectedTransport->isAvailable()) {
        std::cerr << "Transporte " << selectedTransportName << " não está disponível" << std::endl;
        return;
    }

    double totalDistance = dbManager.getPathDistance(currentLocation->getName(), destinationCity->getName());
    if (totalDistance <= 0) {
        std::cerr << "Distância inválida entre as cidades" << std::endl;
        return;
    }

    int speed, distRest, timeRest;
    std::cout << "Por favor, forneça a velocidade do transporte (km/h): ";
    std::cin >> speed;
    std::cout << "Por favor, forneça a distância entre os descansos (km): ";
    std::cin >> distRest;
    std::cout << "Por favor, forneça o tempo de descanso (horas): ";
    std::cin >> timeRest;

    selectedTransport->setInTransit(true);
    selectedTransport->setAvailable(false);

    double travelTime = travelArithmetic.totalTravelTime(totalDistance, speed, distRest, timeRest);
    passenger.setPassengerOnRoute(true);
    passenger.setCurrentLocation(destinationCity);

    std::string startTimestamp = getCurrentTimestamp();
    int travelId = dbManager.saveTravel(selectedTransport->getId(), currentLocation->getId(), destinationCity->getId(), startTimestamp);

    std::cout << "Viagem iniciada. Tempo estimado de viagem: " << travelTime << " horas." << std::endl;

    std::time_t currentTime = std::time(nullptr); // Obtem o tempo atual
    double elapsedTime = 0.0;

    while (elapsedTime < travelTime) {
        std::tm* localTime = std::localtime(&currentTime);
        std::cout << "Hora atual: " << std::put_time(localTime, "%H:%M") << std::endl;

        int hoursToAdvance = 0;
        char userInput;
        std::cout << "Pressione 'a' para avançar 1 hora, 'n' para avançar múltiplas horas, ou 'q' para sair: ";
        std::cin >> userInput;

        if (userInput == 'q') {
            std::cout << "Viagem interrompida pelo usuário." << std::endl;
            break;
        } else if (userInput == 'a') {
            hoursToAdvance = 1;
        } else if (userInput == 'n') {
            std::cout << "Quantas horas deseja avançar? ";
            std::cin >> hoursToAdvance;
        } else {
            std::cerr << "Entrada inválida!" << std::endl;
            continue;
        }

        elapsedTime += hoursToAdvance;
        currentTime += hoursToAdvance * 3600; // Avança o tempo em horas

        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulação de tempo

        if (elapsedTime >= travelTime) {
            elapsedTime = travelTime;
            std::cout << "Chegada ao destino: " << destinationCity->getName() << std::endl;
        }
    }

    std::string endTimestamp = getCurrentTimestamp();
    dbManager.updateTravelEndTime(travelId, endTimestamp);

    selectedTransport->setAvailable(true);
    passenger.setPassengerOnRoute(false);
}