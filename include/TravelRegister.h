#ifndef TRAVELREGISTER_H
#define TRAVELREGISTER_H

#include "TravelAgency.h"

class TravelRegister {
private:
    TravelAgency& agency;  // Referência para a TravelAgency

public:
    // Construtor
    TravelRegister(TravelAgency& agency);

    // Métodos para ler e registrar dados
    void registerCity();
    void registerPath();
    void registerTransport();
    void registerPassenger();

    // Método para exibir relatórios
    void displayReports() const;
};

#endif // TRAVELREGISTER_H
