#include "TravelAgency.h"
#include <iostream>
#include <stdexcept>
#include <map>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

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

// Adiciona passageiro ao transporte
void TravelAgency::addPassengerToTransport(const std::string& transportName, const Passenger& passenger) {
    auto it = transports.find(transportName);
    if (it != transports.end()) {
        it->second.addPassenger(passenger);
    } else {
        std::cerr << "Transporte não encontrado!" << std::endl;
    }
}

// Inicia a viagem
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
                std::cerr << "Seleção inválida. Transporte indisponível ou inexistente." << std::endl;
                return;
            }

            // Selecionar transporte com base na escolha do usuário
            Transport* selectedTransport = availableTransports[selection];

            // Marcar o transporte como indisponível e adicionar o passageiro
            selectedTransport->setAvailable(false);
            selectedTransport->addPassenger(passenger);

            std::cout << "Viagem de " << currentLocation->getName() << " para " << destination.getName() 
                      << " usando " << selectedTransport->getName() << std::endl;

            int distance = path.getDistance();
            int speed = selectedTransport->getSpeed();
            int distRest = selectedTransport->getDistRest();
            int timeRest = selectedTransport->getTimerest();

            try {
                // Calcular o tempo total de viagem em horas
                double travelTime = distance / static_cast<double>(speed);
                double restTime = (distance / static_cast<double>(distRest)) * timeRest;
                double totalTime = travelTime + restTime;

                std::cout << "Iniciando viagem, levará " << totalTime << " horas considerando o tempo de descanso." << std::endl;

                int currentHour = 0;
                double elapsedTime = 0.0;
                while (elapsedTime < totalTime) {
                    // Atualizar e imprimir a hora atual
                    int hour = currentHour % 24; // Simular um relógio de 24 horas
                    std::cout << "Hora atual: " << hour << ":00" << std::endl;

                    // Solicitar avanço de tempo do usuário
                    char userInput;
                    std::cout << "Pressione 'a' para avançar 1 hora ou 'q' para sair: ";
                    std::cin >> userInput;

                    if (userInput == 'q') {
                        std::cout << "Viagem interrompida pelo usuário." << std::endl;
                        break;
                    } else if (userInput == 'a') {
                        elapsedTime += 1.0; // Avançar 1 hora
                        currentHour++;
                        if (static_cast<int>(elapsedTime) % distRest == 0) {
                            std::cout << "Descanso por " << timeRest << " horas." << std::endl;
                            for (int rest = 0; rest < timeRest; ++rest) {
                                // Avançar o tempo durante o descanso
                                std::this_thread::sleep_for(std::chrono::seconds(1));
                                currentHour++;
                                std::cout << "Hora de descanso: " << currentHour % 24 << ":00" << std::endl;
                            }
                        }
                    } else {
                        std::cout << "Entrada inválida. Use 'a' para avançar o tempo ou 'q' para sair." << std::endl;
                    }
                }

                std::cout << "Viagem concluída! Chegada ao destino: " << destination.getName() << std::endl;

            } catch (const std::exception& e) {
                std::cerr << "Erro durante a viagem: " << e.what() << std::endl;
            }

            return;
        }
    }
    std::cerr << "Trajeto não encontrado." << std::endl;
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
        std::cout << "Distância entre descansos: " << transport.getDistRest() << std::endl;
        std::cout << "Tempo de descanso: " << transport.getTimerest() << std::endl;
        std::cout << "Disponível: " << (transport.isAvailable() ? "Sim" : "Não") << std::endl;
        std::cout << std::endl;
    }
}

// Imprime relatório de cidades
void TravelAgency::printCityReport() const {
    std::cout << "Dados das cidades:" << std::endl;
    for (const auto& city : cities) {
        std::cout << "Cidade: " << city.getName() << std::endl;
    }
}
