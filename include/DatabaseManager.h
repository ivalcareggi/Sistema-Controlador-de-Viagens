#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <string>
#include <vector>
#include <sqlite3.h>
#include "city.h"
#include "transport.h"
#include "path.h"
#include "TravelAgency.h"

class DatabaseManager {
public:
    DatabaseManager(const std::string& dbName);
    ~DatabaseManager();

    // Métodos de salvamento
    void saveCity(const std::string& cityName);
    void savePath(const std::string& origin, const std::string& destination, double distance);
    void saveTransport(const std::string& transportName, int capacity, bool type);
    void savePassenger(const std::string& passengerName, const std::string& location); // continuar amanha
    void saveTravel(int transportId, int originCityId, int destinationCityId, const std::string& timestamp);
    void updateTravelEndTime(int travelId, const std::string& endTime);

    // Métodos de listagem
    void listCities() const;
    void listTransports() const;
    void listPassengers() const;
    void listPaths() const;

    // Métodos de consulta
    City* findCityByName(const std::string& cityName);
    std::vector<std::string> getAllCityNames();
    std::vector<City> getAllCities(); 
    std::vector<Transport> getAllTransports(); 
    Transport getTransportByName(const std::string& name) const;
    Path getPath(const City& origin, const City& destination); 
    double getPathDistance(int originCityId, int destinationCityId); 
    int getTransportId(const std::string& transportName); 
    int getCityId(const std::string& cityName) const;

private:
    sqlite3* db;

    void executeSQL(const std::string& sql);
    void createTables();
    void createTable(const std::string& createTableSQL);
};

#endif // DATABASEMANAGER_H