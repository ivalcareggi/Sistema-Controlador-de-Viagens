#ifndef TRAVELREGISTER_H
#define TRAVELREGISTER_H

#include "TravelAgency.h"

class TravelRegister {
private:
    TravelAgency& agency;  // Referência para a agência de viagens

public:
    // Construtor que inicializa a referência para a agência
    TravelRegister(TravelAgency& agency);

    // Métodos para registrar diferentes entidades
    void registerCity();
    void registerPath();
    void registerTransport();
    void registerPassenger();

    // Método para exibir relatórios
    void displayReports();
};

#endif // TRAVELREGISTER_H

