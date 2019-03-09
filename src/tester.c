#include<stdio.h>
#include<stdlib.h>


int main(){
    printf("###############################\n");
    printf("            TEST\n");
    printf("###############################\n");

    __uint8_t num=15;

    //num |=   ( 1 << 4 );
    num &=  ~( 1 << 2 ); 
    
    printf("%d\n",num);
    return 0;
}