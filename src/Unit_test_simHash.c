    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h> 
    #include "simHash.h"


    //calcultates hamming distance between two simHashes

    int hammingDist(char* result1, char* result2){

        if(result1==NULL || result2==NULL)  return -1;
        
        int dist=0;
        for(size_t i = 0; i < SIMHASH_LENGTH; i++)
        {
            if(result1[i]!=result2[i])  dist+=1;
        }
        
        return dist;
    }


    void test(char* testName, int testType,char* delim, char* inputStr1, char* inputStr2, int expectedDist){
        
        char* str1;
        char* str2;
        
        if(inputStr1!=NULL && inputStr2!=NULL)
        {
            str1 = malloc( (strlen(inputStr1)+1)*sizeof(char));
            str2 = malloc( (strlen(inputStr2)+1)*sizeof(char));
            str1[strlen(inputStr1)]='\0';
            str2[strlen(inputStr2)]='\0';

            for(size_t i = 0; i < strlen(inputStr1); i++)
            {
                str1[i]=inputStr1[i];
            }
            
            for(size_t i = 0; i < strlen(inputStr2); i++)
            {
                str2[i]=inputStr2[i];
            }
            
        }else
        {
            str1=NULL;
            str2=NULL;
        }
        
        
        char mySimHash1[SIMHASH_LENGTH];
        char mySimHash2[SIMHASH_LENGTH]; 
        
        char* result1   =   simHash( delim, str1, mySimHash1);
        char* result2   =   simHash( delim, str2, mySimHash2);
        int   dist      =   hammingDist(result1, result2);
        
        
        if(testType==0) printf("%s Test: %-15s\tIN1: %-25s\tIN2: %-25s\tHamming dist: %3d\tExp: %3d\n",(expectedDist==dist) ? "(PASS)":"#FAIL#", testName, inputStr1, inputStr2, dist, expectedDist);
        if(testType==1) printf("------ Test: %-15s\tIN1: %-25s\tIN2: %-25s\tHamming dist: %3d\n",testName, inputStr1, inputStr2, dist);

        if(inputStr1!=NULL && inputStr2!=NULL){
            free(str1);
            free(str2);
        }

    }


    int main(){

        printf("---------------------------------------------[ simHash unit testing ]----------------------------------------------\n\n");

     
        //NULLITIES
    
        test("all-null"         ,0    ,NULL   ,NULL                       , NULL                           ,-1);
        test("delim-null"       ,0    ,NULL   ,"hello"                    ,"hello"                         ,-1);
        test("input-null"       ,0    ," "    ,NULL                       , NULL                           ,-1);
        test("one-str-null"     ,0    ," "    ,"hello"                    , NULL                           ,-1);
        test("all-empty"        ,0    ,""     ,""                         , ""                             ,-1);
    
        

        //SIMILARITIES
        test("similar-single"   ,0    ," "    ,"hello"                    ,"hello"                         ,0);
        test("similar-multi"    ,0    ," "    ,"Lorem ipsum dolor"        ,"Lorem ipsum dolor"             ,0);
        test("other-delimeter"  ,0    ,"m"    ,"Lorem ipsum dolor"       ,"Lorem ipsum dolor"              ,0);
        test("str-delimeter"    ,0    ,"ip"   ,"Lorem ipsum dolor"       ,"Lorem ipsum dolor"              ,0);


        //test hamming distance variation of simhashes with different level of similarities between inputs

        printf("\nEVOLUTION OF HAMMING DISTANCE EXAMPLE:\n");
        test("100%-sim"       ,1    ," "    ,"aaa bbb ccc ddd eee fff ggg hhh iii jjj"       
                                            ,"aaa bbb ccc ddd eee fff ggg hhh iii jjj"       
                                        ,0);

        test(" 90%-sim"        ,1    ," "    ,"aaa bbb ccc ddd eee fff ggg hhh iii jjj"       
                                            ,"aaa bbb ccc ddd eee fff ggg hhh iii 000"       
                                        ,0);

        test(" 80%-sim"        ,1    ," "    ,"aaa bbb ccc ddd eee fff ggg hhh iii jjj"       
                                            ,"aaa bbb ccc ddd eee fff ggg hhh 000 000"       
                                        ,0);

        test(" 70%-sim"        ,1    ," "    ,"aaa bbb ccc ddd eee fff ggg hhh iii jjj"       
                                            ,"aaa bbb ccc ddd eee fff ggg 000 000 000"       
                                        ,0); 

        test(" 60%-sim"        ,1    ," "    ,"aaa bbb ccc ddd eee fff ggg hhh iii jjj"       
                                            ,"aaa bbb ccc ddd eee fff 000 000 000 000"       
                                        ,0);

        test(" 50%-sim"        ,1    ," "    ,"aaa bbb ccc ddd eee fff ggg hhh iii jjj"       
                                            ,"aaa bbb ccc ddd eee 000 000 000 000 000"       
                                        ,0); 

        test(" 40%-sim"        ,1    ," "    ,"aaa bbb ccc ddd eee fff ggg hhh iii jjj"       
                                            ,"aaa bbb ccc ddd 000 000 000 000 000 000"       
                                        ,0);


        return 0;
    }
    