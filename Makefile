CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

SRC_DIR = src
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
EXES = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%,$(SRCS))

all: $(EXES)

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean