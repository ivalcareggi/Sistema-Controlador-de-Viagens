# Definições do compilador e flags
CXX = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -lncurses

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
TARGET = $(BUILD_DIR)/travel_system

# Lista de arquivos de origem
SOURCES = main.cpp TravelAgency.cpp TravelRegister.cpp passenger.cpp city.cpp path.cpp transport.cpp

# Arquivos objeto gerados
OBJECTS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Regra padrão: compilar o executável
$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Regra para compilar arquivos .cpp em .o
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar arquivos gerados
clean:
	rm -rf $(BUILD_DIR)

# Regra para forçar a recompilação
.PHONY: clean
