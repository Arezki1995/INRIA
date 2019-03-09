#VARIABLES
CC = gcc
CFLAGS = -Wall -Werror
BIN_PATH = ./bin
SOURCE_PATH = ./src
TARGET=geoHash.exe

TESTER_DEP=$(SOURCE_PATH)/tester.c
TESTER_BIN=$(BIN_PATH)/tester

BINARY = $(BIN_PATH)/$(TARGET)
DEPENDENCIES = $(SOURCE_PATH)/geoHash.c

DEBUG = -g -D__DEBUG

#TARGETS
default : $(DEPENDENCIES)
	$(CC) -o $(BINARY) $(DEPENDENCIES) $(CFLAGS)


#SMALL BIT LEVEL OPERATIONS TESTER
tester : $(TESTER_DEP)
	$(CC) -o $(TESTER_BIN) $(TESTER_DEP) $(CFLAGS)

test : tester
	./$(TESTER_BIN)


#DEBUG AND CLEAN
debug : $(DEPENDENCIES) 
	$(CC) -o $(BINARY) $(DEPENDENCIES) $(CFLAGS) $(DEBUG)

clean : 
	$(RM) $(BIN_PATH)/* 