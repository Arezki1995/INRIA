#ifndef __GEOHASH_H
#define __GEOHASH_H

#define NB_BITS (5*NB_characters)
#define LAT_MAX_VAL 180.0
#define LNG_MAX_VAL 90.0

typedef struct
{
    double left;
    double right;
    double up;
    double down;
    int bit;
} Zone;


void geoHash(double latitude, double longitude, int NB_characters, char* geoHash);

#endif