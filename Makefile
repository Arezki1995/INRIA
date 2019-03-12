#VARIABLES
CC = gcc
CFLAGS = -Wall -Werror
BIN_PATH = ./bin
SOURCE_PATH = ./src
TARGET=simHash.exe


BINARY = $(BIN_PATH)/$(TARGET)
DEPENDENCIES = $(SOURCE_PATH)/simHash.c


default : $(DEPENDENCIES)
	$(CC) -o $(BINARY) $(DEPENDENCIES) $(CFLAGS)

test : default
	./$(BINARY)

clean: 
	$(RM) $(BIN_PATH)/* 

memory: default
	valgrind $(BINARY) " " "this is a axample of ..qssd.d 2qsd qdhkj sdklj sslqj-*/qsdqkhqskj data"