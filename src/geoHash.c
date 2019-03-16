#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "geoHash.h"

static const char BASE32_TABLE[33] = "0123456789bcdefghjkmnpqrstuvwxyz";


///////////////////////////////////////////////////////////////////////////
char toBase32(int dec){
    return BASE32_TABLE[dec];
}

///////////////////////////////////////////////////////////////////////////
void splitLat(Zone* pZone, double latitude){

    double Mlat = ((pZone->left) + (pZone->right))/2;
    if( latitude <= Mlat){
        pZone->right = Mlat;
        pZone->bit = 0;
    }else
    {
        pZone->left = Mlat; 
        pZone->bit = 1; 
    }
}

///////////////////////////////////////////////////////////////////////////
void splitLong(Zone* pZone, double longitude){
    double Mlong = ( (pZone->up) + (pZone->down) )/2;
    if( longitude <= Mlong){
        pZone->up = Mlong;
        pZone->bit = 0;
    }else
    {
        pZone->down = Mlong; 
        pZone->bit = 1; 
    }
}

///////////////////////////////////////////////////////////////////////////
char* geoHash(double latitude, double longitude, int NB_characters, char* geoHash){

    //INPUT VALIDATION
    if( !((latitude>=(-LAT_MAX_VAL))  && (latitude <= (LAT_MAX_VAL))) ) return NULL;
    if( !((longitude>=(-LNG_MAX_VAL)) && (longitude <= (LNG_MAX_VAL))) ) return NULL;
    if( !(NB_characters>=1) ) return NULL;

    Zone z;
    
    //init
    z.left=-180; z.right=180; z.up=90; z.down=-90;

    #ifdef __DEBUG
        printf("ENCODING : lat: %f  long: %f  \n", latitude,longitude);
    #endif
    char* sequence = (char*)malloc((NB_characters + 1) * sizeof(char));
    sequence[NB_characters] = '\0';


    int index = 0;

    for(int i=0; i<NB_BITS; i++){

        if(i%2==0)  splitLat(&z,longitude);
        else        splitLong(&z,latitude);

        if(i%5==0 && i!=0)   index++;
        
        #ifdef __DEBUG
            printf("%d",z.bit);
        #endif
        
        if(z.bit==1)    sequence[index] |=   ( 1 << (4-i%5) );
        else            sequence[index] &=  ~( 1 << (4-i%5) );

    }

    
    for(int k=0 ;k<NB_BITS/5;k++){
        sequence[k] = toBase32(sequence[k]);
    }

    strcpy(geoHash,sequence);
    #ifdef __DEBUG
        printf("\n");
        printf("%s\n",sequence);
    #endif
    return geoHash;
}