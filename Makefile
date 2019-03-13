#VARIABLES
CC = gcc
CFLAGS = -Wall -Werror
BIN_PATH = ./bin
SOURCE_PATH = ./src
TARGET=simHash.exe


BINARY = $(BIN_PATH)/$(TARGET)
DEPENDENCIES = $(SOURCE_PATH)/simHash.c


default: $(DEPENDENCIES)
	$(CC) -o $(BINARY) $(DEPENDENCIES) $(CFLAGS) -lcrypto

debug: $(DEPENDENCIES)
	$(CC) -o $(BINARY) $(DEPENDENCIES) $(CFLAGS) -lcrypto -D__DEBUG -g

test1: default
	./$(BINARY)  " " "There is no one who loves pain itself, who seeks after it and wants to have it, simply because it is pain..."

test2: default
	./$(BINARY)  " " "There is no one who loves pain itself, who seeks after it and wants to have it, simply because it is Pain..."

test3: default
	./$(BINARY)  " " "THeRe iS nO oNe wHo LovEs pAin iTseLf, wHo seEks afTer iT aNd wAnts To haVe it, SiMply beCaUse iT Is pAiN..."

test4: default
	./$(BINARY)  " " "Feel like you can't read as well as you could when you were 14 years old? You're not alone"

clean: 
	$(RM) $(BIN_PATH)/* 

memory: default
	valgrind $(BINARY) " " "There is no one who loves pain itself, who seeks after it and wants to have it, simply because it is pain..."