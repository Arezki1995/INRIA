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