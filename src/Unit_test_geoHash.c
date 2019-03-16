//EXPECTED VALUES ARE TAKEN FROM : http://geohash.co/

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h> 
    #include "geoHash.h" 

    #define GEO_LENGTH 10
    #define PASSED 1
    #define FAILED 0
    
    int verify(char * result, char* expected){
        
        if (result==NULL && expected==NULL)     return PASSED;
        if (result!=NULL && expected!=NULL){
           if(strlen(result) != strlen(expected))  return FAILED;
            
            if(strcmp(result,expected)==0){
                return PASSED;
            }else
            {
                return FAILED;
            }
        }else
        {
            return FAILED;
        }
        

    }

    void test( double latitude,double longitude,int precision, char* expected, char* testName){

        char* myGeoHash = malloc(precision*sizeof(char));
        char* result=geoHash(latitude,longitude,precision,myGeoHash);
        int status=verify(result, expected);
        printf("%s Test:%-15s\tLAT:%12f\tLONG:%12f\tPREC: %02d\t\tRES: %-15s\tEXP: %s\n",(status)? "(PASS)" : "#FAIL#", testName, latitude, longitude, precision, result, expected );

        free(myGeoHash);
    }


    int main(){
        printf("------------------------------[Geohash unit testing]------------------------------\n");

        //BOUNDARIES
        test(    0,    0,  0,         NULL,    "all-zero"    );
        test(    0,    0,  9,  "7zzzzzzzz",    "lat-lng-zero");
        test(  180,    0,  9,  "gzzzzzzzz",    "lat-max"     );
        test( -180,    0,  9,  "5bpbpbpbp",    "lat-min"     );
        test(    0,   90,  9,  "mzzzzzzzz",    "lng-max"     );
        test(    0,  -90,  9,  "3zzzzzzzz",    "lng-min"     );
        test( -180,   90,  9,  "jbpbpbpbp",    "north-west"  );
        test( -180,  -90,  9,  "1bpbpbpbp",    "south-west"  );
        test(  180,   90,  9,  "vzzzzzzzz",    "north-east"  );
        test(  180,  -90,  9,  "czzzzzzzz",    "south-east"  );
        
        //INVALID
        test( -500,    0,  9,         NULL,    "lat-below"    );
        test(  500,    0,  9,         NULL,    "lat-above"    );
        test(    0, -500,  9,         NULL,    "lng-below"    );
        test(    0,  500,  9,         NULL,    "lng-above"    );
        test(    0,    0, -1,         NULL,    "neg-precision");

        //PRECISION
        test(  50.633795,    3.0184188,  12,     "u140h9tgnr80",    "inria");

        return 0;
    }