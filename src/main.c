#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geoHash.h"
#include "simHash.h"


int main(){
    char myGeoHash[10];
    geoHash(110.9, 15, 10, myGeoHash);
    printf("GEO:%s\n",myGeoHash);

    return 0;
}