#include "../include/showMenu.h"

void showMenu() {
    clearScreen(); 
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

int readOption() {
    int option;
    while (!(std::cin >> option)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida. Por favor, insira um número: ";
    }
    std::cin.ignore();
    return option;
}

std::string readString(const std::string& message) {
    std::string input;
    std::cout << message;
    std::getline(std::cin, input);
    return input;
}

int readInt(const std::string& message) {
    int number;
    std::cout << message;
    while (!(std::cin >> number)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida. Por favor, insira um número: ";
    }
    std::cin.ignore();
    return number;
}

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void pauseScreen() {
    std::cout << "Pressione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void handleListOngoingTrips(DatabaseManager& dbManager) {
    clearScreen();
    dbManager.listOngoingTrips();
    pauseScreen();
}

void handleListMostVisitedCities(DatabaseManager& dbManager) {
    clearScreen();
    dbManager.listMostVisitedCities();
    pauseScreen();
}

void handleAdvanceTime(TravelAgency& travelAgency) {
    clearScreen();
    travelAgency.simulateTimeAdvance();
    pauseScreen();
}

void handleAddCity(TravelRegister& travelRegister) {
    clearScreen();
    std::string cityName = readString("Digite o nome da cidade: ");
    travelRegister.addCity(cityName);
    pauseScreen();
}

void handleAddTransport(TravelRegister& travelRegister) {
    clearScreen();
    std::string transportName = readString("Digite o nome do transporte: ");
    int capacity = readInt("Digite a capacidade: ");
    bool type = readInt("Digite o tipo (1 para terrestre, 0 para aquático): ");
    int cityId = readInt("Digite o ID da cidade em que o transporte está localizado: ");
    travelRegister.addTransport(transportName, capacity, type, cityId);
    pauseScreen();
}

void handleAddPassenger(TravelRegister& travelRegister) {
    clearScreen();
    std::string passengerName = readString("Digite o nome do passageiro: ");
    std::string location = readString("Digite o nome da cidade de localização: ");
    travelRegister.addPassenger(passengerName, location);
    pauseScreen();
}

void handleAddPath(TravelRegister& travelRegister) {
    clearScreen();
    std::string origin = readString("Digite a cidade de origem: ");
    std::string destination = readString("Digite a cidade de destino: ");
    double distance = readInt("Digite a distância: ");
    travelRegister.addPath(origin, destination, distance);
    pauseScreen();
}

void handleListCities(const TravelRegister& travelRegister) {
    clearScreen();
    travelRegister.listCities();
    pauseScreen();
}

void handleListTransports(const DatabaseManager& dbManager) {
    clearScreen();
    dbManager.listTransports();
    pauseScreen();
}

void handleListPassengers(const DatabaseManager& dbManager) {
    clearScreen();
    dbManager.listPassengers();
    pauseScreen();
}

void handleStartJourney(TravelRegister& travelRegister, TravelAgency& travelAgency) {
    clearScreen();
    std::string passengerName = readString("Digite o nome do passageiro: ");
    std::string destinationName = readString("Digite o nome da cidade de destino: ");

    Passenger* passenger = travelRegister.findPassengerByName(passengerName);
    if (!passenger) {
        std::cout << "Passageiro não encontrado no banco de dados.\n";
        pauseScreen();
        return;
    }

    City* destinationCity = travelRegister.findCityByName(destinationName);
    if (!destinationCity) {
        std::cout << "Cidade de destino não encontrada.\n";
        pauseScreen();
        return;
    }

    travelAgency.startJourney(*passenger, destinationName);
    std::cout << "Pressione Enter para continuar..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
