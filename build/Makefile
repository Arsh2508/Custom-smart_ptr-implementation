# Compiler and flags
CXX = g++
CFLAGS = -std=c++17 -Wall -Wextra -I$(INC_DIR) -pthread
LDFLAGS = -pthread

# Directories
SRC_DIR = ../src
INC_DIR = ../include
TEST_DIR = ../googletests
BUILD_DIR = .

# Executable names
TARGET = smart
TEST_TARGET = test

# Source files
SRC = $(SRC_DIR)/main.cpp
TEST_SRC = $(TEST_DIR)/test.cpp

# Object files
OBJ = $(BUILD_DIR)/main.o
TEST_OBJ = $(BUILD_DIR)/test.o

# Default target
all: $(TARGET)

# Build main executable
$(TARGET): $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(TARGET)

# Compile main source
$(OBJ): $(SRC)
	$(CXX) $(CFLAGS) -c $(SRC) -o $(OBJ)

# Build and run test
test: $(TEST_TARGET)
	@echo "Running tests..."
	./$(TEST_TARGET)

# Build test executable (linked with gtest)
$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(TEST_OBJ) -o $(TEST_TARGET) $(LDFLAGS) -lgtest -lgtest_main

# Compile test source
$(TEST_OBJ): $(TEST_SRC)
	$(CXX) $(CFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ)

# Clean
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET) $(TEST_TARGET)

.PHONY: all clean test
