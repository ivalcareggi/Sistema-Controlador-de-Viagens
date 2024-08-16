# Definindo variáveis
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lsqlite3

# Lista dos arquivos de fonte
SRCS = main.cpp \
       DatabaseManager.cpp \
       TravelAgency.cpp \
       TravelRegister.cpp \
       TravelArithmetic.cpp \
       transport.cpp \
       path.cpp \
       passenger.cpp \
       city.cpp

# Lista dos arquivos objeto correspondentes
OBJS = $(SRCS:.cpp=.o)

# Nome do executável
TARGET = travel_management

# Regra padrão
all: $(TARGET)

# Regra para construir o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Regra para construir arquivos objeto a partir de arquivos fonte
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar arquivos gerados
clean:
	rm -f $(TARGET) $(OBJS)

# Regra para remover arquivos objeto e o executável
distclean: clean

# Regras de dependências
main.o: TravelAgency.h DatabaseManager.h TravelRegister.h
DatabaseManager.o: DatabaseManager.h city.h transport.h path.h passenger.h
TravelAgency.o: TravelAgency.h DatabaseManager.h TravelRegister.h city.h transport.h path.h passenger.h
TravelRegister.o: TravelRegister.h TravelAgency.h DatabaseManager.h city.h transport.h path.h passenger.h
TravelArithmetic.o: TravelAgency.h TravelRegister.h DatabaseManager.h
transport.o: transport.h passenger.h
path.o: path.h city.h
passenger.o: passenger.h city.h
city.o: city.h

.PHONY: all clean distclean
