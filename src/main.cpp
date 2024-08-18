#include <iostream>
#include <string>
#include "../include/TravelRegister.h"

void showMenu() {
    std::cout << "----- Menu -----" << std::endl;
    std::cout << "1. Adicionar Cidade" << std::endl;
    std::cout << "2. Adicionar Transporte" << std::endl;
    std::cout << "3. Adicionar Passageiro" << std::endl;
    std::cout << "4. Adicionar Caminho" << std::endl;
    std::cout << "5. Listar Cidades" << std::endl;
    std::cout << "6. Listar Transportes" << std::endl;
    std::cout << "7. Listar Passageiros" << std::endl;
    std::cout << "8. Iniciar Viagem" << std::endl;
    std::cout << "9. Sair" << std::endl;
}

void handleAddCity(TravelRegister& travelRegister) {
    std::string cityName;
    std::cout << "Digite o nome da cidade: ";
    std::getline(std::cin, cityName);
    travelRegister.addCity(cityName);
}

void handleAddTransport(TravelRegister& travelRegister) {
    std::string transportName;
    int capacity;
    bool type;
    std::cout << "Digite o nome do transporte: ";
    std::getline(std::cin, transportName);
    std::cout << "Digite a capacidade: ";
    std::cin >> capacity;
    std::cout << "Digite o tipo (1 para terrestre, 0 para aquático): ";
    std::cin >> type;
    std::cin.ignore();  // Limpa o caractere de nova linha
    travelRegister.addTransport(transportName, capacity, type);
}

void handleAddPassenger(TravelRegister& travelRegister) {
    std::string passengerName;
    std::string location;
    std::cout << "Digite o nome do passageiro: ";
    std::getline(std::cin, passengerName);
    std::cout << "Digite o nome da cidade de localização: ";
    std::getline(std::cin, location);
    travelRegister.addPassenger(passengerName, location);
}

void handleAddPath(TravelRegister& travelRegister) {
    std::string origin;
    std::string destination;
    double distance;
    std::cout << "Digite a cidade de origem: ";
    std::getline(std::cin, origin);
    std::cout << "Digite a cidade de destino: ";
    std::getline(std::cin, destination);
    std::cout << "Digite a distância: ";
    std::cin >> distance;
    std::cin.ignore();  // Limpa o caractere de nova linha
    travelRegister.addPath(origin, destination, distance);
}

void handleListCities(const TravelRegister& travelRegister) {
    travelRegister.listCities();
}

void handleListTransports(const DatabaseManager& dbManager) {
    dbManager.listTransports();
}

void handleListPassengers(const DatabaseManager& dbManager) {
    dbManager.listPassengers();
}

int main() {
    DatabaseManager dbManager("traveldata.db");
    TravelAgency travelAgency(dbManager);
    TravelRegister travelRegister(travelAgency, dbManager);

    int choice;

    while (true) {
        showMenu();
        std::cout << "Escolha uma opção: ";
        std::cin >> choice;
        std::cin.ignore();  // Limpa o caractere de nova linha

        switch (choice) {
            case 1:
                handleAddCity(travelRegister);
                break;
            case 2:
                handleAddTransport(travelRegister);
                break;
            case 3:
                handleAddPassenger(travelRegister);
                break;
            case 4:
                handleAddPath(travelRegister);
                break;
            case 5:
                handleListCities(travelRegister);
                break;
            case 6:
                handleListTransports(dbManager);
                break;
            case 7:
                handleListPassengers(dbManager);
                break;
            case 8:
                std::cout << "Funcionalidade de iniciar viagem ainda não implementada." << std::endl;
                break;
            case 9:
                std::cout << "Saindo..." << std::endl;
                return 0;
            default:
                std::cout << "Opção inválida. Tente novamente." << std::endl;
                break;
        }
    }

    return 0;
}
