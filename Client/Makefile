CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++17 -lstdc++fs -Wall -Werror -I $(INCLUDE_DIR)

OBJECTS = \
	$(BUILD_DIR)/Main.o \
	$(BUILD_DIR)/Client.o \
	$(BUILD_DIR)/ConfigurationParser.o

ClientSensitivityList = $(SRC_DIR)/Client.cpp \
	$(INCLUDE_DIR)/ConfigurationParser.hpp

ConfigurationParserSensitivityList = $(SRC_DIR)/ConfigurationParser.cpp \
	$(INCLUDE_DIR)/json.hpp

MainSensitivityList = \
	$(SRC_DIR)/main.cpp \
	$(INCLUDE_DIR)/Client.hpp

all: $(BUILD_DIR) client.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

client.out: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o client.out

$(BUILD_DIR)/Main.o: $(MainSensitivityList)
	$(CC) -c $(SRC_DIR)/main.cpp $(CFLAGS) -o $(BUILD_DIR)/Main.o

$(BUILD_DIR)/Client.o: $(ClientSensitivityList)
	$(CC) -c $(SRC_DIR)/Client.cpp $(CFLAGS) -o $(BUILD_DIR)/Client.o

$(BUILD_DIR)/ConfigurationParser.o: $(ConfigurationParserSensitivityList)
	$(CC) -c $(SRC_DIR)/ConfigurationParser.cpp $(CFLAGS) -o $(BUILD_DIR)/ConfigurationParser.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out