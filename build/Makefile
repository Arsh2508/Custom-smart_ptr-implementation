CXX = g++
CFLAGS = -std=c++17 -Wall -Wextra -I$(INC_DIR)

SRC_DIR = ../src
INC_DIR = ../include
BUILD_DIR = .
TARGET = smart

SRC = $(SRC_DIR)/main.cpp
OBJ = $(BUILD_DIR)/main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(TARGET)

$(OBJ): $(SRC)
	$(CXX) $(CFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)

.PHONY: all clean
