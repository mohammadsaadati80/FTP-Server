CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++17 -lstdc++fs -Wall -Werror -I $(INCLUDE_DIR)

OBJECTS = \
	$(BUILD_DIR)/Main.o \
	$(BUILD_DIR)/Server.o \
	$(BUILD_DIR)/User.o \
	$(BUILD_DIR)/UserManager.o \
	$(BUILD_DIR)/ConfigurationParser.o \
	$(BUILD_DIR)/CommandHandler.o \
	$(BUILD_DIR)/ConnectedUser.o

ServerSensitivityList = $(SRC_DIR)/Server.cpp \
	$(INCLUDE_DIR)/ConfigurationParser.hpp \
	$(INCLUDE_DIR)/UserManager.hpp \
	$(INCLUDE_DIR)/CommandHandler.hpp

UserSensitivityList = $(SRC_DIR)/User.cpp

UserManagerSensitivityList = $(SRC_DIR)/UserManager.cpp \
	$(INCLUDE_DIR)/User.hpp \
	$(INCLUDE_DIR)/ConfigurationParser.hpp \
	$(INCLUDE_DIR)/ConnectedUser.hpp

ConfigurationParserSensitivityList = $(SRC_DIR)/ConfigurationParser.cpp \
	$(INCLUDE_DIR)/User.hpp \
	$(INCLUDE_DIR)/json.hpp

CommandHandlerSensitivityList = $(SRC_DIR)/CommandHandler.cpp \
	$(INCLUDE_DIR)/UserManager.hpp \

ConnectedUserSensitivityList = $(SRC_DIR)/ConnectedUser.cpp \
	$(INCLUDE_DIR)/User.hpp 

MainSensitivityList = \
	$(SRC_DIR)/main.cpp \
	$(INCLUDE_DIR)/Server.hpp

all: $(BUILD_DIR) server.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

server.out: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o server.out

$(BUILD_DIR)/Main.o: $(MainSensitivityList)
	$(CC) -c $(SRC_DIR)/main.cpp $(CFLAGS) -o $(BUILD_DIR)/Main.o

$(BUILD_DIR)/Server.o: $(ServerSensitivityList)
	$(CC) -c $(SRC_DIR)/Server.cpp $(CFLAGS) -o $(BUILD_DIR)/Server.o	

$(BUILD_DIR)/User.o: $(UserSensitivityList)
	$(CC) -c $(SRC_DIR)/User.cpp $(CFLAGS) -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/UserManager.o: $(UserManagerSensitivityList)
	$(CC) -c $(SRC_DIR)/UserManager.cpp $(CFLAGS) -o $(BUILD_DIR)/UserManager.o

$(BUILD_DIR)/ConfigurationParser.o: $(ConfigurationParserSensitivityList)
	$(CC) -c $(SRC_DIR)/ConfigurationParser.cpp $(CFLAGS) -o $(BUILD_DIR)/ConfigurationParser.o

$(BUILD_DIR)/CommandHandler.o: $(CommandHandlerSensitivityList)
	$(CC) -c $(SRC_DIR)/CommandHandler.cpp $(CFLAGS) -o $(BUILD_DIR)/CommandHandler.o

$(BUILD_DIR)/ConnectedUser.o: $(ConnectedUserSensitivityList)
	$(CC) -c $(SRC_DIR)/ConnectedUser.cpp $(CFLAGS) -o $(BUILD_DIR)/ConnectedUser.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out
