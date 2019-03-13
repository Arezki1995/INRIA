#VARIABLES
CC 			= gcc
CFLAGS 		= -Wall -Werror
BIN_PATH 	= ./bin
SOURCE_PATH = ./src
LIBS_PATH	= ./lib
TARGET		= $(BIN_PATH)/exec


default: libhash $(SOURCE_PATH)/main.c
	$(CC) -o $(TARGET) $(SOURCE_PATH)/main.c $(CFLAGS) -L$(LIBS_PATH) -lhash


libhash: $(SOURCE_PATH)/geoHash.* $(SOURCE_PATH)/simHash.*
	cd $(SOURCE_PATH) && $(MAKE)


exec: default
	$(TARGET)

clean:
	$(RM) $(LIBS_PATH)/* $(BIN_PATH)/*