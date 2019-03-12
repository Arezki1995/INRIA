#VARIABLES
CC = gcc
CFLAGS = -Wall -Werror
BIN_PATH = ./bin
SOURCE_PATH = ./src
TARGET=simHash.exe


BINARY = $(BIN_PATH)/$(TARGET)
DEPENDENCIES = $(SOURCE_PATH)/simHash.c


default : $(DEPENDENCIES)
	$(CC) -o $(BINARY) $(DEPENDENCIES) $(CFLAGS) -lcrypto

test : default
	./$(BINARY)  " " "lkrgkklkj65d6  df2s454s14 opg132dfg 8ee5rg4ev  6r5465gfdsg  gf43se46e5g4e eytrtt6e4"

clean: 
	$(RM) $(BIN_PATH)/* 

memory: default
	valgrind $(BINARY) " " "lkrgkklkj65d6  df2s454s14 opg132dfg 8ee5rg4ev  6r5465gfdsg  gf43se46e5g4e eytrtt6e4"