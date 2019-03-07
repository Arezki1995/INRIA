#VARIABLES
CC = gcc
CFLAGS = -Wall -Werror
BIN_PATH = ./bin
SOURCE_PATH = ./src
TARGET=geoHash.exe

BINARY = $(BIN_PATH)/$(TARGET)
DEPENDENCIES = $(SOURCE_PATH)/geoHash.c


default : $(DEPENDENCIES)
	$(CC) -o $(BINARY) $(DEPENDENCIES) $(CFLAGS)

test : default
	./$(BINARY)

clean: 
	$(RM) $(BIN_PATH)/* 