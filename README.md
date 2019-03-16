# INRIA
## Technical test - INRIA

###Part 01

The implementation of the hash functions has been made in several phases:

At first, understanding the principle behind Geohash working principle and analysis of the requirements. Then implementation and test. The same process has been followed for the simHash.

Each functionnality has been developped independently in it's own git branch and could be tested seperately.

Since the expected result of a geohash is unique across different implementations test results have been verified against several online [APIs](https://www.movable-type.co.uk/scripts/geohash.html) and and revealed to be positive.  

SimHash in the other hand can be implemented using different hash functions at the token hashing phase thus different implementations do not necessarily provide the same result but the similarity propoerty must be respected.

My implementation of this hash functions is build on this phases:
    **1. Tokenization**: split input data into tokens depending on a given delimiter. Store the resulting tokens in a list.
    **2. Token Hashing**: calculate the 16bytes MD5 hash (openssl library) of every token and store it in the same dataStructure 
    **3. Setting Column Values** : one way to implement the algorithm is to attribute a symbole to every bit in the md5 hash ("1" if bit is set "-1" otherwise)
    **4. Summing column Values**: sum the column values of the hashes of all the tokens and at each column if the sum is positive the corresponding simHash column takes a "1" and "0" if the column sum is negative.

With several different tests, nearly similar inputs gave small hamming distance between their simHashes compared to the ones with different inputs.
At this level I did not find a way to test more exhaustively test this. 


##Running unit tests
To reproduce the unit tests performed move to top level makefile location and run:
    ``   make geoUnitTest``
    ``   make simUnitTest``


##Library
Once implemented and I verified the working of the functions, I decided to incapsulate them in a static library. This code snippet explaines how to use them:
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h> 
    #include "geoHash.h" 
    #include "simHash.h"

    #define GEO_LENGTH 10

    int main(){
        char myGeoHash[GEO_LENGTH];
        geoHash( 90,                //latitude  [-180, 180] 
                 15,                //longitude [-90 , 90 ]
                 GEO_LENGTH,        //number of characters of geohash -> precision
                 myGeoHash          //where to store the goehash
                );
        printf("GEO:%s\n",myGeoHash);

        char mySimHash[SIMHASH_LENGTH];
        char input[] ="no one would think it is gonna work";
        char delim[] = " "; 
        simHash(delim,input ,mySimHash);
        printf("SIM:%s\n",mySimHash);

        return 0;
    }
