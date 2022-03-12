CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -pthread -Wall -Werror -I$(INCLUDE_DIR)

OBJECTS = \
	$(BUILD_DIR)/Main.o \
	$(BUILD_DIR)/Client.o

ClientSensitivityList = $(SRC_DIR)/Client.cpp \

MainSensitivityList = \
	$(SRC_DIR)/main.cpp \
	$(INCLUDE_DIR)/Client.hpp

all: $(BUILD_DIR) client.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

client.out: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o client.out

$(BUILD_DIR)/Main.o: $(MainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/Main.o

$(BUILD_DIR)/Client.o: $(ClientSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Client.cpp -o $(BUILD_DIR)/Client.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out