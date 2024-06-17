CC = gcc

CXXFLAGS = -std=c++17 -Wall -Wextra -g

SRC_DIR = /mnt/c/Users/kng20/OneDrive/Documents/csce412/project_three
OBJ_DIR = $(SRC_DIR)/obj
BIN_DIR = $(SRC_DIR)/bin
DOC_DIR = $(SRC_DIR)/docs

EXECUTABLE = loadbalancer

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/LoadBalancer.cpp $(SRC_DIR)/Request.cpp $(SRC_DIR)/RequestQueue.cpp $(SRC_DIR)/WebServer.cpp
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
HEADERS = $(wildcard $(SRC_DIR)/*.h)
DOXYFILE = $(SRC_DIR)/Doxyfile

# Targets
all: loadbalancer
loadbalancer: $(BIN_DIR)/$(EXECUTABLE)

$(BIN_DIR)/$(EXECUTABLE): $(OBJS) | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -o $@ $^ -lstdc++

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(DOC_DIR)

.PHONY: docs
docs: $(DOXYFILE)
	doxygen $(DOXYFILE)

.PHONY: run
run: $(BIN_DIR)/$(EXECUTABLE)
	$(BIN_DIR)/$(EXECUTABLE)
