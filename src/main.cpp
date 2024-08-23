#include <iostream>
#include <string>
#include <algorithm>
#include <limits> 
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
    std::cout << "9. Avançar Tempo" << std::endl;
    std::cout << "10. Relatar Viagens em Andamento" << std::endl;
    std::cout << "11. Relatar Cidades Mais Visitadas" << std::endl;
    std::cout << "12. Sair" << std::endl;
}

void handleListOngoingTrips(DatabaseManager& dbManager) {
    dbManager.listOngoingTrips();
}

void handleListMostVisitedCities(DatabaseManager& dbManager) {
    dbManager.listMostVisitedCities();
}

void handleAdvanceTime(TravelAgency& travelAgency) {
    travelAgency.simulateTimeAdvance();
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
    int cityId;
    std::cout << "Digite o nome do transporte: ";
    std::getline(std::cin, transportName);
    std::cout << "Digite a capacidade: ";
    std::cin >> capacity;
    std::cout << "Digite o tipo (1 para terrestre, 0 para aquático): ";
    std::cin >> type;
    std::cin.ignore(); 
    std::cout << "Digite o ID da cidade em que o transporte está localizado: ";
    std::cin >> cityId;
    travelRegister.addTransport(transportName, capacity, type, cityId);
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
    std::cin.ignore();  
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

void handleStartJourney(TravelRegister& travelRegister, TravelAgency& travelAgency) {
    std::string passengerName;
    std::string destinationName;

    std::cout << "Digite o nome do passageiro: ";
    std::getline(std::cin, passengerName);

    std::cout << "Digite o nome da cidade de destino: ";
    std::getline(std::cin, destinationName);

    // Verifica se o passageiro existe no banco de dados
    Passenger* passenger = travelRegister.findPassengerByName(passengerName);
    if (!passenger) {
        std::cout << "Passageiro não encontrado no banco de dados.\n";
        return;
    }

  
    City* destinationCity = travelRegister.findCityByName(destinationName);
    if (!destinationCity) {
        std::cout << "Cidade de destino não encontrada.\n";
        return;
    }

  
    travelAgency.startJourney(*passenger, destinationName);
}



int main() {
    try {
        DatabaseManager dbManager("traveldata.db");
        TravelAgency travelAgency(dbManager);
        TravelRegister travelRegister(travelAgency, dbManager);

        int choice;

        while (true) {
            showMenu();
            std::cout << "Escolha uma opção: ";
            if (!(std::cin >> choice)) {
                std::cerr << "Entrada inválida. Por favor, insira um número." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cin.ignore();  

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
                    handleStartJourney(travelRegister, travelAgency);
                    break;
                case 9:
                    handleAdvanceTime(travelAgency);  
                    break;
                case 10:
                    handleListOngoingTrips(dbManager);
                    break;
                case 11:
                    handleListMostVisitedCities(dbManager);
                    break;
                case 12:
                    std::cout << "Saindo..." << std::endl;
                    return 0;
                default:
                    std::cout << "Opção inválida. Tente novamente." << std::endl;
                    break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}