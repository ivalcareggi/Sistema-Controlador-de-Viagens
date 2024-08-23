#include "../include/showMenu.h"
#include "../include/DatabaseManager.h"
#include "../include/TravelAgency.h"
#include "../include/TravelRegister.h"

int main() {
    try {
       
        DatabaseManager dbManager("traveldata.db");
        TravelAgency travelAgency(dbManager);
        TravelRegister travelRegister(travelAgency, dbManager);

        int choice;

        while (true) {
            
            showMenu();
            std::cout << "Escolha uma opção: ";
            choice = readOption(); 

           
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
