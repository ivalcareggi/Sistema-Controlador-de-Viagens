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
std::map<std::string, std::tuple<double, int, Passenger*>> ongoingTravels;

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
        transportName.clear(); 
    }
}

void TravelAgency::updatePassengerLocation(Passenger& passenger, City* newLocation) {
    if (newLocation != nullptr) {
        
        passenger.setCurrentLocation(newLocation);

    
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

    int transportCityId = dbManager.getTransportCityId(selectedTransport->getId());
    if (transportCityId != currentLocation->getId()) {
        std::cerr << "Transporte " << selectedTransportName << " não está na cidade de origem." << std::endl;
        return;
    }

    std::vector<City*> shortestPath = travelArithmetic.calculateShortestPath(*currentLocation, *destinationCity, cities);

    double totalDistance = 0.0;
    for (size_t i = 0; i < shortestPath.size() - 1; ++i) {
        for (const auto& path : shortestPath[i]->getPaths()) {
            if (path.getDestination() == shortestPath[i + 1]) {
                totalDistance += path.getDistance();
                break;
            }
        }
    }

    if (totalDistance <= 0) {
        totalDistance = dbManager.getPathDistance(currentLocation->getName(), destinationCity->getName());
        if (totalDistance <= 0) {
            std::cerr << "Distância inválida entre as cidades" << std::endl;
            return;
        }
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

    std::string startTimestamp = getCurrentTimestamp();
    int travelId = dbManager.saveTravel(selectedTransport->getId(), currentLocation->getId(), destinationCity->getId(), startTimestamp);

    ongoingTravels[selectedTransportName] = std::make_tuple(travelTime, travelId, &passenger);

    dbManager.logTrip(travelId, currentLocation->getName(), destinationCity->getName(), passenger.getName(), "Em andamento");

    std::cout << "Viagem iniciada. Tempo estimado de viagem: " << travelTime << " horas." << std::endl;

    passenger.setCurrentLocation(destinationCity);
}

void TravelAgency::simulateTimeAdvance() {
    double elapsedTime = 0.0;
    std::time_t currentTime = std::time(nullptr);

    while (true) {
        std::tm* localTime = std::localtime(&currentTime);
        std::cout << "Hora atual: " << std::put_time(localTime, "%H:%M") << std::endl;

        int hoursToAdvance = 0;
        char userInput;
        std::cout << "Pressione 'a' para avançar 1 hora, 'n' para avançar múltiplas horas, ou 'q' para sair: ";
        std::cin >> userInput;

        if (userInput == 'q') {
            std::cout << "Simulação de avanço do tempo interrompida." << std::endl;
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
        currentTime += hoursToAdvance * 3600;

        std::this_thread::sleep_for(std::chrono::seconds(1));

        for (auto& [transportName, transport] : transports) {
            if (transport.isInTransit()) {
                auto it = ongoingTravels.find(transportName);
                if (it != ongoingTravels.end()) {
                    double travelTime = std::get<0>(it->second);
                    int travelId = std::get<1>(it->second);
                    Passenger* passenger = std::get<2>(it->second);

                    if (elapsedTime >= travelTime) {
                        elapsedTime = travelTime;
                        if (passenger) {
                            endJourney(*passenger, transport, travelId);
                            ongoingTravels.erase(it);
                        }
                    }
                }
            }
        }
    }
}

void TravelAgency::endJourney(Passenger& passenger, Transport& transport, int travelId) {
    std::string endTimestamp = getCurrentTimestamp();
    dbManager.updateTravelEndTime(travelId, endTimestamp);

    City* destinationCity = passenger.getCurrentLocation();
    dbManager.updatePassengerLocation(passenger.getName(), destinationCity->getId());
    dbManager.updateTransportLocation(transport.getId(), destinationCity->getId());

    transport.setAvailable(true);
    passenger.setPassengerOnRoute(false);

    
    dbManager.updateTripStatus(travelId, "Finalizada");

    std::cout << "Viagem finalizada. Chegada ao destino: " << destinationCity->getName() << std::endl;
}