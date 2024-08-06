#include <iostream>
#include "TravelAgency.h"
#include "TravelRegister.h"
#include <limits>

int main() {
    TravelAgency agency;
    TravelRegister travelRegister(agency);  

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
        case 4:
            travelRegister.registerPassenger();
            break;
        case 5:
            travelRegister.displayReports();
            break;
        case 6: { // Caso para iniciar viagem
            std::string passengerName, destinationName;
            std::cout << "Digite o nome do passageiro: ";
            std::getline(std::cin, passengerName);
            std::cout << "Digite o nome da cidade de destino: ";
            std::getline(std::cin, destinationName);

            try {
                // Encontrar o passageiro e a cidade
                Passenger& passenger = agency.findPassenger(passengerName);
                City& destination = agency.findCity(destinationName);

                // Iniciar a viagem
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
