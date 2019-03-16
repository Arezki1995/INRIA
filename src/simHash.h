#ifndef __SIMHASH_H
#define __SIMHASH_H

#include <openssl/md5.h>
#define MAX             64                          //maximum characters in the word
#define CHAR_SIZE       8                           //this is fixed not to be changed
#define SIMHASH_LENGTH  CHAR_SIZE*MD5_DIGEST_LENGTH+1

struct node{                                        //linked list node data structure
    char data[MAX];                                 //token data
    struct node* next;                              //pointer to next node
    unsigned char hash[MD5_DIGEST_LENGTH];          //MD5 token Hash
    int columnVal[MD5_DIGEST_LENGTH][CHAR_SIZE];    //token Column values to compute simHash
};

typedef struct node Node;
typedef struct node* NodePointer;

char* simHash(const char* delim, // delimeter string 
              char* inputStr,    // input string to be hashed
              char* simHash      // char Simhash[CHAR_SIZE*MD5_DIGEST_LENGTH+1] to store the hash in
              );


#endif