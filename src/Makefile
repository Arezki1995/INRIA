#VARIABLES
CC 			= gcc
CFLAGS 		= -Wall -Werror

LIBS_PATH	= ../lib
CRYPTO		= -lcrypto

LIBRARY		= $(LIBS_PATH)/libhash.a


default: $(LIBRARY)


geoHash.o: geoHash.c geoHash.h
	$(CC) -c $^ $(CFLAGS)

simHash.o: simHash.c simHash.h
	$(CC) -c $^ $(CFLAGS) $(CRYPTO)


$(LIBRARY): geoHash.o simHash.o
	ar rcs $@ $^
	$(RM) -f core *.o *.gch

