#include "TravelRegister.h"
#include <iostream>
#include <string>
#include <limits>

// Construtor que inicializa a referência para a agência
TravelRegister::TravelRegister(TravelAgency& agency) : agency(agency) {}

// Método para registrar uma cidade
void TravelRegister::registerCity() {
    std::string name;
    std::cout << "Digite o nome da cidade: ";
    std::getline(std::cin, name);
    City city(name);
    agency.addCity(city);
    std::cout << "Cidade registrada com sucesso." << std::endl;
}

// Método para registrar um trajeto
void TravelRegister::registerPath() {
    std::string originName, destinationName;
    double distance;
    std::cout << "Digite o nome da cidade de origem: ";
    std::getline(std::cin, originName);
    std::cout << "Digite o nome da cidade de destino: ";
    std::getline(std::cin, destinationName);
    std::cout << "Digite a distância entre as cidades: ";
    std::cin >> distance;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpar buffer

    try {
      
        City& origin = agency.findCity(originName);
        City& destination = agency.findCity(destinationName);

       
        Path path(&origin, &destination, distance);
        agency.addPath(path);
        std::cout << "Trajeto registrado com sucesso." << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

// Método para registrar um transporte
void TravelRegister::registerTransport() {
    std::string name;
    int type, capacity, speed, distRest, timeRest;
    std::cout << "Digite o nome do transporte: ";
    std::getline(std::cin, name);
    std::cout << "Digite o tipo do transporte (0 para aquático, 1 para terrestre): ";
    std::cin >> type;
    std::cout << "Digite a capacidade do transporte: ";
    std::cin >> capacity;
    std::cout << "Digite a velocidade do transporte: ";
    std::cin >> speed;
    std::cout << "Digite a distância para descanso: ";
    std::cin >> distRest;
    std::cout << "Digite o tempo de descanso: ";
    std::cin >> timeRest;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpar buffer

    Transport transport(name, type, capacity, speed, distRest, timeRest);
    agency.addTransport(transport);
    std::cout << "Transporte registrado com sucesso." << std::endl;
}

// Método para registrar um passageiro
void TravelRegister::registerPassenger() {
    std::string name, cityName;
    std::cout << "Digite o nome do passageiro: ";
    std::getline(std::cin, name);
    std::cout << "Digite a cidade atual do passageiro: ";
    std::getline(std::cin, cityName);

    try {
        City* currentLocation = nullptr;
        if (!cityName.empty()) {
            try {
                currentLocation = &agency.findCity(cityName);
            } catch (const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
            }
        }

        Passenger passenger(name, currentLocation);
        agency.addPassenger(passenger);
        std::cout << "Passageiro registrado com sucesso." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erro ao registrar passageiro: " << e.what() << std::endl;
    }
}

// Métodos auxiliares para gerar relatórios
void TravelRegister::printPassengerReport() const {
    // Implementar a lógica para exibir o relatório de passageiros
    std::cout << "Relatório de Passageiros:" << std::endl;
   
}

void TravelRegister::printTransportReport() const {
    // Implementar a lógica para exibir o relatório de transportes
    std::cout << "Relatório de Transportes:" << std::endl;
    
}

void TravelRegister::printCityReport() const {
    // Implementar a lógica para exibir o relatório de cidades
    std::cout << "Relatório de Cidades:" << std::endl;
    
}

// Método para exibir relatórios
void TravelRegister::displayReports() {
    std::cout << "\nRelatórios Disponíveis:" << std::endl;
    std::cout << "1. Relatório de Passageiros" << std::endl;
    std::cout << "2. Relatório de Transportes" << std::endl;
    std::cout << "3. Relatório de Cidades" << std::endl;

    int choice;
    std::cout << "Escolha uma opção: ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpar buffer

    switch (choice) {
    case 1:
        agency.printPassengerReport();
        break;
    case 2:
        agency.printTransportReport();
        break;
    case 3:
        agency.printCityReport();
        break;
    default:
        std::cout << "Opção inválida." << std::endl;
        break;
    }
}

