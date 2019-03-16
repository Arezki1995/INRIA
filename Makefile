#VARIABLES
CC 			= gcc
CFLAGS 		= -Wall -Werror -g
BIN_PATH 	= ./bin
SOURCE_PATH = ./src
LIBS_PATH	= ./lib
TARGET		= $(BIN_PATH)/exec


default: libhash $(SOURCE_PATH)/main.c
	$(CC) -o $(TARGET) $(SOURCE_PATH)/main.c $(CFLAGS) -L$(LIBS_PATH) -lhash -lcrypto


libhash: $(SOURCE_PATH)/geoHash.* $(SOURCE_PATH)/simHash.*
	cd $(SOURCE_PATH) && $(MAKE)

exec: default
	$(TARGET)

geoUnitTest: libhash $(SOURCE_PATH)/Unit_test_geoHash.c
	$(CC) -o $(BIN_PATH)/geoUnitTest $(SOURCE_PATH)/Unit_test_geoHash.c -L$(LIBS_PATH) -lhash
	$(BIN_PATH)/geoUnitTest

simUnitTest: libhash $(SOURCE_PATH)/Unit_test_simHash.c
	$(CC) -o $(BIN_PATH)/simUnitTest $(SOURCE_PATH)/Unit_test_simHash.c -L$(LIBS_PATH) -lhash -lcrypto -g
	$(BIN_PATH)/simUnitTest

clean:
	$(RM) $(LIBS_PATH)/* $(BIN_PATH)/*