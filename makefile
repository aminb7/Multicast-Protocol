CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -Wall -Werror -I$(INCLUDE_DIR)

ClientSensitivityList = \
	$(SRC_DIR)/Client.cpp \
	$(INCLUDE_DIR)/Client.h \

ServerSensitivityList = \
	$(SRC_DIR)/Server.cpp \
	$(INCLUDE_DIR)/Server.h \

GroupServerSensitivityList = \
	$(SRC_DIR)/GroupServer.cpp \
	$(INCLUDE_DIR)/GroupServer.h \

RouterSensitivityList = \
	$(SRC_DIR)/Router.cpp \
	$(INCLUDE_DIR)/Router.h \

all: $(BUILD_DIR) Client.out Server.out GroupServer.out Router.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

Client.out: $(BUILD_DIR)/Client.o $(OBJECTS)
	$(CC) $(CFLAGS) -o Client.out $(BUILD_DIR)/Client.o $(OBJECTS)

Server.out: $(BUILD_DIR)/Server.o $(OBJECTS)
	$(CC) $(CFLAGS) -o Server.out $(BUILD_DIR)/Server.o $(OBJECTS)

GroupServer.out: $(BUILD_DIR)/GroupServer.o $(OBJECTS)
	$(CC) $(CFLAGS) -o GroupServer.out $(BUILD_DIR)/GroupServer.o $(OBJECTS)

Router.out: $(BUILD_DIR)/Router.o $(OBJECTS)
	$(CC) $(CFLAGS) -o Router.out $(BUILD_DIR)/Router.o $(OBJECTS)

$(BUILD_DIR)/Client.o: $(ClientSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Client.cpp -o $(BUILD_DIR)/Client.o

$(BUILD_DIR)/Server.o: $(ServerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Server.cpp -o $(BUILD_DIR)/Server.o

$(BUILD_DIR)/GroupServer.o: $(GroupServerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/GroupServer.cpp -o $(BUILD_DIR)/GroupServer.o

$(BUILD_DIR)/Router.o: $(RouterSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Router.cpp -o $(BUILD_DIR)/Router.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out switch* system*
