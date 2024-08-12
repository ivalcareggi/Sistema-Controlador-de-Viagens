#include <iostream>
#include "TravelAgency.h"
#include "TravelRegister.h"
#include "DatabaseManager.h"
#include <limits>

int main() {
    std::string dbName = "travel_management.db";  // Nome do banco de dados
    TravelAgency agency(dbName);  // Passa o nome do banco de dados para o construtor
    TravelRegister travelRegister(agency);
    DatabaseManager dbManager(dbName); // Inicializa o gerenciador de banco de dados

    while (true) {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Registrar Cidade" << std::endl;
        std::cout << "2. Registrar Trajeto" << std::endl;
        std::cout << "3. Registrar Transporte" << std::endl;
        std::cout << "4. Registrar Passageiro" << std::endl;
        std::cout << "5. Exibir Relatórios" << std::endl;
        std::cout << "6. Iniciar Viagem" << std::endl;
        std::cout << "7. Sair" << std::endl;

        int choice;
        std::cout << "Escolha uma opção: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpar buffer

        switch (choice) {
        case 1:
            travelRegister.registerCity();
            break;
        case 2:
            travelRegister.registerPath();
            break;
        case 3:
            travelRegister.registerTransport();
            break;
        case 4: {
            // Get passenger details
            std::string passengerName;
            std::cout << "Nome do passageiro: ";
            std::getline(std::cin, passengerName);

            std::string currentLocationName;
            std::cout << "Localização atual: ";
            std::getline(std::cin, currentLocationName);

            // Find the current location city
            City* currentLocation = nullptr;
            try {
                currentLocation = &agency.findCity(currentLocationName);
            } catch (const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
                break;
            }

            // Save to database
            if (dbManager.savePassenger(passengerName, currentLocationName)) {
                std::cout << "Passageiro registrado no banco de dados." << std::endl;

                // Add to memory
                Passenger newPassenger(passengerName, currentLocation);
                agency.addPassenger(newPassenger);
            } else {
                std::cerr << "Erro ao salvar passageiro no banco de dados." << std::endl;
            }
            break;
        }
        case 5:
            travelRegister.displayReports();
            break;
        case 6: {
            std::string passengerName, destinationName;
            std::cout << "Digite o nome do passageiro: ";
            std::getline(std::cin, passengerName);
            std::cout << "Digite o nome da cidade de destino: ";
            std::getline(std::cin, destinationName);

            try {
                Passenger& passenger = agency.findPassenger(passengerName);
                City& destination = agency.findCity(destinationName);
                agency.startJourney(passenger, destination);
            } catch (const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
            }
            break;
        }
        case 7:
            std::cout << "Encerrando o programa." << std::endl;
            return 0;
        default:
            std::cout << "Escolha inválida." << std::endl;
            break;
        }
    }
}
