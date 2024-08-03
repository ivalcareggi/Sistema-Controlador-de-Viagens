#include "TravelRegister.h"
#include <iostream>

// Construtor
TravelRegister::TravelRegister(TravelAgency& agency) : agency(agency) {}

// Função para registrar uma cidade
void TravelRegister::registerCity() {
    std::string cityName;
    std::cout << "Digite o nome da cidade: ";
    std::getline(std::cin, cityName);

    City city(cityName); // Supondo que o construtor de City recebe apenas o nome
    agency.addCity(city);

    std::cout << "Cidade registrada com sucesso!" << std::endl;
}

// Função para registrar um trajeto
void TravelRegister::registerPath() {
    std::string originName, destinationName;
    bool type;
    double distance;

    std::cout << "Digite o nome da cidade de origem: ";
    std::getline(std::cin, originName);

    std::cout << "Digite o nome da cidade de destino: ";
    std::getline(std::cin, destinationName);

    std::cout << "Digite a distância do trajeto: ";
    std::cin >> distance;

    std::cout << "O trajeto é terrestre? (1 = Sim, 0 = Não): ";
    std::cin >> type;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpar buffer

    try {
        City origin = agency.findCity(originName);
        City destination = agency.findCity(destinationName);
        Path path(origin, destination, type, distance);
        agency.addPath(path);
        std::cout << "Trajeto registrado com sucesso!" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

// Função para registrar um transporte
void TravelRegister::registerTransport() {
    std::string name;
    bool type;
    int capacity, speed, rest;
    double timerest;

    std::cout << "Digite o nome do transporte: ";
    std::getline(std::cin, name);

    std::cout << "O transporte é terrestre? (1 = Sim, 0 = Não): ";
    std::cin >> type;

    std::cout << "Digite a capacidade do transporte: ";
    std::cin >> capacity;

    std::cout << "Digite a velocidade do transporte: ";
    std::cin >> speed;

    std::cout << "Digite a distância entre descansos: ";
    std::cin >> rest;

    std::cout << "Digite o tempo de descanso: ";
    std::cin >> timerest;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpar buffer

    Transport transport(name, type, capacity, speed, rest, timerest);
    agency.addTransport(transport);

    std::cout << "Transporte registrado com sucesso!" << std::endl;
}

// Função para registrar um passageiro
void TravelRegister::registerPassenger() {
    std::string name;
    std::cout << "Digite o nome do passageiro: ";
    std::getline(std::cin, name);

    try {
        Passenger passenger(name);
        agency.addPassenger(passenger);
        std::cout << "Passageiro registrado com sucesso!" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

// Função para exibir relatórios
void TravelRegister::displayReports() const {
    std::cout << "Relatórios disponíveis:" << std::endl;
    std::cout << "1. Relatório de Passageiros" << std::endl;
    std::cout << "2. Relatório de Transportes" << std::endl;
    std::cout << "3. Relatório de Cidades" << std::endl;

    int choice;
    std::cout << "Escolha um relatório para exibir: ";
    std::cin >> choice;

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
        std::cout << "Escolha inválida." << std::endl;
        break;
    }
}
