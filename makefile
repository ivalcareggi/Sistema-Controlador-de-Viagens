CC = g++
CFLAGS = -Wall -std=c++17 -I/usr/include -Iinclude
LDFLAGS = -L/usr/lib -lsqlite3
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
TARGET = $(BIN_DIR)/main

# Lista de arquivos-fonte
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Cria objetos dos cpp
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Regra padrão
all: $(TARGET)

# Criar executável
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Criar os arquivos objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Limpa arquivos gerados
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

# Instrução para executar o target default quando make é chamado sem argumentos
.PHONY: all clean test