CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -Wall -Werror -I$(INCLUDE_DIR)

OBJECTS = \
	$(BUILD_DIR)/Utilities.o \
	$(BUILD_DIR)/Link.o \

NetworkSensitivityList = \
	$(SRC_DIR)/Network.cpp \
	$(INCLUDE_DIR)/Network.h \

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

LinkSensitivityList = \
	$(SRC_DIR)/Link.cpp \
	$(INCLUDE_DIR)/Link.h \

UtilitiesSensitivityList = \
	$(SRC_DIR)/Utilities.cpp \
	$(INCLUDE_DIR)/Utilities.h \

all: $(BUILD_DIR) Network.out Client.out Server.out GroupServer.out Router.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

Network.out: $(BUILD_DIR)/Network.o $(OBJECTS)
	$(CC) $(CFLAGS) -o Network.out $(BUILD_DIR)/Network.o $(OBJECTS)

Client.out: $(BUILD_DIR)/Client.o $(OBJECTS)
	$(CC) $(CFLAGS) -o Client.out $(BUILD_DIR)/Client.o $(OBJECTS)

Server.out: $(BUILD_DIR)/Server.o $(OBJECTS)
	$(CC) $(CFLAGS) -o Server.out $(BUILD_DIR)/Server.o $(OBJECTS)

GroupServer.out: $(BUILD_DIR)/GroupServer.o $(OBJECTS)
	$(CC) $(CFLAGS) -o GroupServer.out $(BUILD_DIR)/GroupServer.o $(OBJECTS)

Router.out: $(BUILD_DIR)/Router.o $(OBJECTS)
	$(CC) $(CFLAGS) -o Router.out $(BUILD_DIR)/Router.o $(OBJECTS)

$(BUILD_DIR)/Network.o: $(NetworkSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Network.cpp -o $(BUILD_DIR)/Network.o

$(BUILD_DIR)/Client.o: $(ClientSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Client.cpp -o $(BUILD_DIR)/Client.o

$(BUILD_DIR)/Server.o: $(ServerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Server.cpp -o $(BUILD_DIR)/Server.o

$(BUILD_DIR)/GroupServer.o: $(GroupServerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/GroupServer.cpp -o $(BUILD_DIR)/GroupServer.o

$(BUILD_DIR)/Router.o: $(RouterSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Router.cpp -o $(BUILD_DIR)/Router.o

$(BUILD_DIR)/Link.o: $(LinkSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Link.cpp -o $(BUILD_DIR)/Link.o

$(BUILD_DIR)/Utilities.o: $(UtilitiesSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Utilities.cpp -o $(BUILD_DIR)/Utilities.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out switch* system*
