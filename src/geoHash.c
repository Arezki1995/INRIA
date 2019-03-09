
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>

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


static const char BASE32_TABLE[33] = "0123456789bcdefghjkmnpqrstuvwxyz";

char toBase32(int dec){
    return BASE32_TABLE[dec];
}

void usage(){
    printf( "./executable <latitude> <longitude> <precision>\n"
            "\t-->precision is the number of letters in the geoHash\n"
            "\t-->latitude is a double in the range {-180,180}\n"
            "\t-->longitude is a double in the range {-90,90}\n");
}


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


void geoHash(double latitude, double longitude, int NB_characters){
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
    #ifdef __DEBUG
        printf("\n");
        printf("%s\n",sequence);
    #endif
}

int main(int argc , char* argv[]){
    
    if(argc==4){
        double latitude     =atof(argv[1]);
        double longitude    =atof(argv[2]);
        int precision       =atoi(argv[3]);

        //INPUT VALIDATION
        assert( (latitude>=(-LAT_MAX_VAL))  && (latitude <= (LAT_MAX_VAL)) );
        assert( (longitude>=(-LNG_MAX_VAL)) && (longitude <= (LNG_MAX_VAL)) );
        assert( precision>=1 );


        geoHash(
            latitude,
            longitude,
            precision
        );
    }else
    {
        usage();
    }
    
    return 0;
}