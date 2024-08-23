#include "../include/DatabaseManager.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

DatabaseManager::DatabaseManager(const std::string& dbName) {
    int result = sqlite3_open(dbName.c_str(), &db);
    if (result != SQLITE_OK) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        throw std::runtime_error("Failed to open database");
    }

    // Cria as tabelas se não existirem
    createTables();
}

DatabaseManager::~DatabaseManager() {
    if (db) {
        sqlite3_close(db);
    }
}

void DatabaseManager::createTables() {
    std::string createCitiesTable = R"(
        CREATE TABLE IF NOT EXISTS cities (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL UNIQUE
        );
    )";

    std::string createTransportsTable = R"(
    CREATE TABLE IF NOT EXISTS transports (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL,
        capacity INTEGER NOT NULL,
        type BOOLEAN NOT NULL,
        city_id INTEGER,
        FOREIGN KEY(city_id) REFERENCES cities(id)
    );
)";

    std::string createPassengersTable = R"(
        CREATE TABLE IF NOT EXISTS travel_passengers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            city_id INTEGER NOT NULL,
            FOREIGN KEY (city_id) REFERENCES cities(id)
        );
    )";

    std::string createPathsTable = R"(
         CREATE TABLE IF NOT EXISTS travel_routes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            origin_id INTEGER NOT NULL,
            destination_id INTEGER NOT NULL,
            distance REAL NOT NULL,
            FOREIGN KEY (origin_id) REFERENCES cities(id),
            FOREIGN KEY (destination_id) REFERENCES cities(id)
        );
    )";
    std::string createTravelsTable = R"(
        CREATE TABLE IF NOT EXISTS travels (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            transport_id INTEGER NOT NULL,
            origin_id INTEGER NOT NULL,
            destination_id INTEGER NOT NULL,
            start_time TIMESTAMP,
            end_time TIMESTAMP,
            FOREIGN KEY (transport_id) REFERENCES transports(id),
            FOREIGN KEY (origin_id) REFERENCES cities(id),
            FOREIGN KEY (destination_id) REFERENCES cities(id)
        );
    )";

    std::string createTripLogsTable = R"(
        CREATE TABLE IF NOT EXISTS trip_logs (                                                          
             log_id INTEGER PRIMARY KEY AUTOINCREMENT,
             travel_id INTEGER NOT NULL,
             origin_city TEXT NOT NULL,
             destination_city TEXT NOT NULL,
             passengers TEXT NOT NULL,
             trip_status TEXT NOT NULL,
             FOREIGN KEY (travel_id) REFERENCES travels(id)
    );
)";
    executeSQL(createCitiesTable);
    executeSQL(createTransportsTable);
    executeSQL(createPassengersTable);
    executeSQL(createPathsTable);
    executeSQL(createTravelsTable);
    executeSQL(createTripLogsTable); // verificar 
}

void DatabaseManager::executeSQL(const std::string& sql) {
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "Erro ao executar SQL: " << errorMessage << std::endl;
        sqlite3_free(errorMessage); 
    } else {
        std::cout << "Comando SQL executado com sucesso." << std::endl;
    }
}

void DatabaseManager::saveCity(const std::string& cityName) {
    std::string sql = "INSERT INTO cities (name) VALUES (?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, cityName.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error saving city: " << sqlite3_errmsg(db) << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
    }
}

void DatabaseManager::logTrip(int travelId, const std::string& originCity, const std::string& destinationCity, const std::string& passengers, const std::string& tripStatus) {
    std::string sql = R"(
        INSERT INTO trip_logs (travel_id, origin_city, destination_city, passengers, trip_status)
        VALUES (?, ?, ?, ?, ?);
    )";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, travelId);
        sqlite3_bind_text(stmt, 2, originCity.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, destinationCity.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, passengers.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, tripStatus.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Erro ao registrar viagem no log: " << sqlite3_errmsg(db) << std::endl;
        }
    }
    sqlite3_finalize(stmt);
}
void DatabaseManager::updateTripStatus(int travelId, const std::string& status) {
    std::string sql = "UPDATE trip_logs SET trip_status = ? WHERE travel_id = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, status.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, travelId);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Erro ao atualizar status da viagem: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Erro ao preparar SQL: " << sqlite3_errmsg(db) << std::endl;
    }
}

void DatabaseManager::listOngoingTrips() {
    std::string sql = R"(
        SELECT * FROM trip_logs WHERE trip_status = 'Em andamento';
    )";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int logId = sqlite3_column_int(stmt, 0);
            int travelId = sqlite3_column_int(stmt, 1);
            std::string originCity = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string destinationCity = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::string passengers = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            std::string tripStatus = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

            std::cout << "Log ID: " << logId << ", Viagem ID: " << travelId 
                      << ", Origem: " << originCity << ", Destino: " << destinationCity 
                      << ", Passageiros: " << passengers << ", Status: " << tripStatus << std::endl;
        }
    } else {
        std::cerr << "Erro ao listar viagens em andamento: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void DatabaseManager::listMostVisitedCities() {
    std::string sql = R"(
        SELECT destination_city, COUNT(*) as visit_count
        FROM trip_logs
        GROUP BY destination_city
        ORDER BY visit_count DESC;
    )";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string city = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            int visitCount = sqlite3_column_int(stmt, 1);

            std::cout << "Cidade: " << city << ", Visitas: " << visitCount << std::endl;
        }
    } else {
        std::cerr << "Erro ao listar as cidades mais visitadas: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void DatabaseManager::savePath(const std::string& origin, const std::string& destination, double distance) {
    int originId = getCityId(origin);
    int destinationId = getCityId(destination);

    if (originId == -1 || destinationId == -1) {
        std::cerr << "Erro ao encontrar IDs das cidades: " << origin << " e " << destination << std::endl;
        return;
    }

    std::stringstream sql;
    sql << "INSERT INTO travel_routes (origin_id, destination_id, distance) VALUES ("
        << originId << ", "
        << destinationId << ", "
        << distance << ");";

    std::string query = sql.str();
    
    executeSQL(query);
}

void DatabaseManager::saveTransport(const std::string& transportName, int capacity, bool type, int cityId) {
    // Cria a string SQL para inserir um novo transporte na tabela
    std::stringstream sql;
    sql << "INSERT INTO transports (name, capacity, type, city_id) VALUES ('"
        << transportName << "', "
        << capacity << ", "
        << (type ? 1 : 0) << ", "  
        << cityId << ");";

    // Converte o stringstream em string e executa o SQL
    std::string query = sql.str();
    executeSQL(query);
}
void DatabaseManager::savePassenger(const std::string& passengerName, const std::string& location) {
    int cityId = getCityId(location);

    if (cityId == -1) {  
        std::cerr << "City not found: " << location << std::endl;
        return;
    }

    std::stringstream sql;
    sql << "INSERT INTO travel_passengers (name, city_id) VALUES ('"
        << passengerName << "', " << cityId << ");";

    
    std::string query = sql.str();

   
    executeSQL(query);
}

int DatabaseManager::saveTravel(int transportId, int originCityId, int destinationCityId, const std::string& timestamp) {
    std::string query = "INSERT INTO travels (transport_id, origin_id, destination_id, start_time) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    int travelId = -1;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, transportId);
        sqlite3_bind_int(stmt, 2, originCityId);
        sqlite3_bind_int(stmt, 3, destinationCityId);
        sqlite3_bind_text(stmt, 4, timestamp.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            travelId = sqlite3_last_insert_rowid(db); // Obtém o ID da última inserção
        } else {
            std::cerr << "Erro ao inserir viagem: " << sqlite3_errmsg(db) << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Falha ao preparar a instrução SQL: " << sqlite3_errmsg(db) << std::endl;
    }

    return travelId;
}

void DatabaseManager::updateTravelEndTime(int travelId, const std::string& endTime) {
    std::string query = "UPDATE travels SET end_time = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, endTime.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, travelId);
        
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Erro ao atualizar o tempo de fim da viagem: " << sqlite3_errmsg(db) << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Falha ao preparar a instrução SQL: " << sqlite3_errmsg(db) << std::endl;
    }
}

void DatabaseManager::updateTransportLocation(int transportId, int cityId) {
    std::stringstream sql;
    sql << "UPDATE transports SET city_id = " << cityId << " WHERE id = " << transportId << ";";
    executeSQL(sql.str());
}
void DatabaseManager::listCities() const {
     sqlite3_stmt* stmt;
    const std::string query = "SELECT id, name FROM cities;";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "O banco de dados não conseguiu recuperar os dados: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

   
    std::cout << "Lista das cidades:" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);

        std::cout << "ID: " << id << ", Name: " << name << std::endl;
    }

   
    sqlite3_finalize(stmt);

}

void DatabaseManager::listTransports() const {
    sqlite3_stmt* stmt;
    const std::string query = "SELECT id, name, capacity, type FROM transports;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "O banco de dados não conseguiu recuperar os dados: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    
    std::cout << "Lista de transportes:" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        int capacity = sqlite3_column_int(stmt, 2);
        int type = sqlite3_column_int(stmt, 3);

      
        bool isTerrestrial = type == 1;

        std::cout << "ID: " << id << ", Nome: " << name 
                  << ", Capacidade: " << capacity 
                  << ", Tipo: " << (isTerrestrial ? "Terrestre" : "Aquatico") 
                  << std::endl;
    }

   
    sqlite3_finalize(stmt);
}

void DatabaseManager::listPassengers() const {
    sqlite3_stmt* stmt;
    const std::string query = "SELECT id, name, city_id FROM travel_passengers;";

    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "O banco de dados não conseguiu recuperar os dados: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

   
    std::cout << "Lista de passageiros:" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        int cityId = sqlite3_column_int(stmt, 2);


        std::cout << "ID: " << id << ", Nome: " << name 
                  << ", ID da Cidade: " << cityId 
                  << std::endl;
    }

   
    sqlite3_finalize(stmt);
}

void DatabaseManager::listPaths() const {
    sqlite3_stmt* stmt;
    const std::string query = "SELECT id, origin_id, destination_id, distance FROM travel_routes;";


    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Falha em recuperar os dados " << sqlite3_errmsg(db) << std::endl;
        return;
    }


    std::cout << "Lista de caminhos:" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int originId = sqlite3_column_int(stmt, 1);
        int destinationId = sqlite3_column_int(stmt, 2);
        double distance = sqlite3_column_double(stmt, 3);

      
        std::string originCityQuery = "SELECT name FROM cities WHERE id = " + std::to_string(originId) + ";";
        sqlite3_stmt* originStmt;
        if (sqlite3_prepare_v2(db, originCityQuery.c_str(), -1, &originStmt, nullptr) == SQLITE_OK) {
            std::string originCityName = "Unknown";
            if (sqlite3_step(originStmt) == SQLITE_ROW) {
                const unsigned char* originCityNameText = sqlite3_column_text(originStmt, 0);
                originCityName = reinterpret_cast<const char*>(originCityNameText);
            }
            sqlite3_finalize(originStmt);

            std::string destinationCityQuery = "SELECT name FROM cities WHERE id = " + std::to_string(destinationId) + ";";
            sqlite3_stmt* destinationStmt;
            if (sqlite3_prepare_v2(db, destinationCityQuery.c_str(), -1, &destinationStmt, nullptr) == SQLITE_OK) {
                std::string destinationCityName = "Unknown";
                if (sqlite3_step(destinationStmt) == SQLITE_ROW) {
                    const unsigned char* destinationCityNameText = sqlite3_column_text(destinationStmt, 0);
                    destinationCityName = reinterpret_cast<const char*>(destinationCityNameText);
                }
                sqlite3_finalize(destinationStmt);

                // Print the path information
                std::cout << "ID: " << id
                          << ", De: " << originCityName
                          << ", Para: " << destinationCityName
                          << ", Distancia: " << distance
                          << std::endl;
            }
        }
    }

   
    sqlite3_finalize(stmt);
}

City* DatabaseManager::findCityByName(const std::string& cityName) {
    sqlite3_stmt* stmt;
    const std::string query = "SELECT id, name FROM cities WHERE name = ?;";

    // Prepara a instrução SQL
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Falha ao preparar a instrução: " << sqlite3_errmsg(db) << std::endl;
        return nullptr; // Retorna nullptr em caso de erro
    }

    // Vincula o parâmetro
    if (sqlite3_bind_text(stmt, 1, cityName.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Falha ao vincular o parâmetro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return nullptr;
    }

    City* city = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        // Cria um novo objeto City com os dados retornados
        city = new City(id, name); // Ajuste o construtor conforme necessário
    } else {
        std::cerr << "Cidade não encontrada" << std::endl;
    }

    
    sqlite3_finalize(stmt);
    return city; // Retorna o ponteiro para a cidade encontrada ou nullptr se não encontrada
}

std::vector<std::string> DatabaseManager::getAllCityNames() {
    std::vector<std::string> cityNames;
    sqlite3_stmt* stmt;
    const std::string query = "SELECT name FROM cities;";

   
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Falha em recuperar os dados: " << sqlite3_errmsg(db) << std::endl;
        return cityNames;
    }

   
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* nameText = sqlite3_column_text(stmt, 0);
        std::string name(reinterpret_cast<const char*>(nameText));
        cityNames.push_back(name);
    }

   
    sqlite3_finalize(stmt);

    return cityNames;
}

std::vector<City> DatabaseManager::getAllCities() {
    std::vector<City> cities;
    sqlite3_stmt* stmt;
    const std::string query = "SELECT id, name FROM cities;";

   
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Falha em recuperar os dados: " << sqlite3_errmsg(db) << std::endl;
        return cities;
    }

 
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* nameText = sqlite3_column_text(stmt, 1);
        std::string name(reinterpret_cast<const char*>(nameText));

        City city(id, name);
        cities.push_back(city);
    }

   
    sqlite3_finalize(stmt);

    return cities;
}

std::vector<Transport> DatabaseManager::getAllTransports() {
    std::vector<Transport> transports;
    sqlite3_stmt* stmt;
    const std::string query = "SELECT id, name, capacity, type FROM transports;";


    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return transports;
    }

    // Execute the query and collect results
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* nameText = sqlite3_column_text(stmt, 1);
        int capacity = sqlite3_column_int(stmt, 2);
        bool type = sqlite3_column_int(stmt, 3) != 0; 

        std::string name(reinterpret_cast<const char*>(nameText));

        
        Transport transport(id, name, type, capacity);
        transports.push_back(transport);
    }

    // Finalize the SQL statement
    sqlite3_finalize(stmt);

    return transports;
}
Transport DatabaseManager::getTransportByName(const std::string& transportName) const {
    std::stringstream sql;
    sql << "SELECT id, name, capacity, type FROM transports WHERE name = ?;";

    sqlite3_stmt* stmt;
    Transport transport; 

   
    if (sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
       
        sqlite3_bind_text(stmt, 1, transportName.c_str(), -1, SQLITE_STATIC);

       
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            int capacity = sqlite3_column_int(stmt, 2);
            bool type = sqlite3_column_int(stmt, 3) != 0; 

          
            transport = Transport(id, name, type, capacity);
        } else {
           
            std::cerr << "Transporte não encontrado: " << transportName << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
    }

    return transport; 
}

Path DatabaseManager::getPath(const City& origin, const City& destination) {
    std::stringstream sql;
    sql << "SELECT distance FROM travel_routes WHERE origin_id = " << origin.getId()
        << " AND destination_id = " << destination.getId() << ";";

    sqlite3_stmt* stmt;
    double distance = 0.0;

 
    if (sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            distance = sqlite3_column_double(stmt, 0);
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Falha ao recuperar dados: " << sqlite3_errmsg(db) << std::endl;
    }

    
    return Path(const_cast<City*>(&origin), const_cast<City*>(&destination), distance);
}


double DatabaseManager::getPathDistance(const std::string& originCityName, const std::string& destinationCityName) {
    int originCityId = getCityId(originCityName);
    int destinationCityId = getCityId(destinationCityName);

    if (originCityId == -1 || destinationCityId == -1) {
        std::cerr << "Erro ao encontrar IDs das cidades: " << originCityName << " e " << destinationCityName << std::endl;
        return -1.0;
    }

    std::stringstream sql;
    sql << "SELECT distance FROM travel_routes WHERE origin_id = " << originCityId
        << " AND destination_id = " << destinationCityId << ";";

    sqlite3_stmt* stmt;
    double distance = -1.0; 

    if (sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            distance = sqlite3_column_double(stmt, 0);
        } else {
            std::cerr << "Nenhum caminho encontrado entre IDs " << originCityId << " e " << destinationCityId << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Falha ao recuperar dados: " << sqlite3_errmsg(db) << std::endl;
    }

    return distance;
}

int DatabaseManager::getTransportId(const std::string& transportName) {  
    std::stringstream sql;
    sql << "SELECT id FROM transports WHERE name = '" << transportName << "';";

    sqlite3_stmt* stmt;
    int transportId = -1; 

    
    if (sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            transportId = sqlite3_column_int(stmt, 0);
        } else {
            std::cerr << "Transporte não encontrado: " << transportName << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Falha ao recuperar dados: " << sqlite3_errmsg(db) << std::endl;
    }

    return transportId;
}

int DatabaseManager::getPassengerCityId(const std::string& passengerName) const {
    sqlite3_stmt* stmt;
    std::string query = "SELECT city_id FROM travel_passengers WHERE name = ?";
    int cityId = -1;  

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, passengerName.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            cityId = sqlite3_column_int(stmt, 0);
        }

        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error preparing SQL statement for getPassengerCityId." << std::endl;
    }

    return cityId;
}

City* DatabaseManager::findCityById(int cityId) const {
    sqlite3_stmt* stmt;
    std::string query = "SELECT id, name FROM cities WHERE id = ?";
    City* city = nullptr;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, cityId);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            city = new City(id, name);  
        }

        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error preparing SQL statement for findCityById." << std::endl;
    }

    return city;
}
int DatabaseManager::getCityId(const std::string& cityName) const {
    sqlite3_stmt* stmt;
    std::string query = "SELECT id FROM cities WHERE name = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Falha ao preparar a instrução: " << sqlite3_errmsg(db) << std::endl;
        return -1; 
    }

    if (sqlite3_bind_text(stmt, 1, cityName.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Falha ao vincular o parâmetro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    int cityId = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cityId = sqlite3_column_int(stmt, 0);
    } else {
        std::cerr << "Cidade não encontrada: " << cityName << std::endl;
    }

    sqlite3_finalize(stmt);
    return cityId;
}

    std::string DatabaseManager::getCityName(int cityId) const {
    sqlite3_stmt* stmt;
    std::string query = "SELECT name FROM cities WHERE id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Falha ao preparar a instrução: " << sqlite3_errmsg(db) << std::endl;
        return "";
    }

    if (sqlite3_bind_int(stmt, 1, cityId) != SQLITE_OK) {
        std::cerr << "Falha ao vincular o parâmetro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return "";
    }

    std::string cityName;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cityName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    } else {
        std::cerr << "Cidade não encontrada com ID: " << cityId << std::endl;
    }

    sqlite3_finalize(stmt);
    return cityName;
}

int DatabaseManager::getTransportCityId(int transportId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT city_id FROM transports WHERE id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Falha ao preparar a instrução: " << sqlite3_errmsg(db) << std::endl;
        return -1; 
    }

    if (sqlite3_bind_int(stmt, 1, transportId) != SQLITE_OK) {
        std::cerr << "Falha ao vincular o parâmetro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    int cityId = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cityId = sqlite3_column_int(stmt, 0);
    } else {
        std::cerr << "Transport ID " << transportId << " não encontrado." << std::endl;
    }

    sqlite3_finalize(stmt);
    return cityId;
}

void DatabaseManager::updatePassengerLocation(const std::string& name, int cityId) {
    std::stringstream sql;

    sql << "UPDATE travel_passengers SET city_id = " << cityId << " WHERE name = '" << name << "';";

   
    std::cout << "Atualizando localização do passageiro: " << name << " para a cidade com ID: " << cityId << std::endl;

    executeSQL(sql.str());
}
std::string DatabaseManager::getPassengerName(const std::string& passengerName) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT name FROM travel_passengers WHERE name = ?";
    std::string result;

    // Preparar a instrução SQL
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
        return result;  
    }

    
    sqlite3_bind_text(stmt, 1, passengerName.c_str(), -1, SQLITE_STATIC);

  
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    
    sqlite3_finalize(stmt);

    std::cout << "Passageiro encontrado: " << result << std::endl;
    return result;
}