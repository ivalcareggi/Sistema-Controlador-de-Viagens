#include <iostream>
#include "TravelAgency.h"
#include "TravelRegister.h"

int main() {
    TravelAgency agency;
    TravelRegister travelRegister(agency);  // Renomeado para evitar conflito

    while (true) {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Registrar Cidade" << std::endl;
        std::cout << "2. Registrar Trajeto" << std::endl;
        std::cout << "3. Registrar Transporte" << std::endl;
        std::cout << "4. Registrar Passageiro" << std::endl;
        std::cout << "5. Exibir Relatórios" << std::endl;
        std::cout << "6. Sair" << std::endl;

        int choice;
        std::cout << "Escolha uma opção: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpar buffer

        switch (choice) {
        case 1:
            travelRegister.registerCity();  // Usar o novo nome da instância
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
        case 6:
            std::cout << "Encerrando o programa." << std::endl;
            return 0;
        default:
            std::cout << "Escolha inválida." << std::endl;
            break;
        }
    }
}

