#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

//For MD5 hashing
#include <openssl/md5.h>
#include "simHash.h"

////////////////////////////////////////////////////////////////////////////
void calcuteSimHash(NodePointer current, char* simHash){
   if(NULL == current) return;
   
   int columnValSum[MD5_DIGEST_LENGTH][CHAR_SIZE];

   //init sum array to zeros
   for(size_t i = 0; i < MD5_DIGEST_LENGTH; i++)
   {
      for(size_t j = 0; j < CHAR_SIZE; j++)
      {
         columnValSum[i][j] =0 ;
      }
   }
   
   //loop through list
   while(NULL != current){
      for(size_t i = 0; i < MD5_DIGEST_LENGTH; i++)
      {
         for(size_t j = 0; j < CHAR_SIZE; j++)
         {
            columnValSum[i][j] += (current->columnVal[i][j]) ;
         }
      }
      current = current->next;
   }

   simHash[CHAR_SIZE*MD5_DIGEST_LENGTH]='\0';

   for(size_t i = 0; i < MD5_DIGEST_LENGTH; i++)
   {
      for(size_t j = 0; j < CHAR_SIZE; j++)
      {
         sprintf( simHash+ 8*i +j,"%d", ((columnValSum[i][j]) > 0) ? 1:0 );
      }

   }

}
////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG
void displayColumnVal(NodePointer n){
   for(size_t i = 0; i < MD5_DIGEST_LENGTH; i++)
   {
      for(size_t j = 0; j < CHAR_SIZE; j++)
      {
         printf("[%2d]", (n->columnVal[i][j]) );
      }
      printf("\n");  
   }
}
#endif
////////////////////////////////////////////////////////////////////////////
void setColumnVal(NodePointer np){
    
    for(size_t i=0; i< MD5_DIGEST_LENGTH ;i++)
    {
       //setting column values a digest byte at a time
        np->columnVal[i][0]= ( ((np->hash[i] >>7) & (1))  == 1) ? 1:-1;
        np->columnVal[i][1]= ( ((np->hash[i] >>6) & (1))  == 1) ? 1:-1;
        np->columnVal[i][2]= ( ((np->hash[i] >>5) & (1))  == 1) ? 1:-1;
        np->columnVal[i][3]= ( ((np->hash[i] >>4) & (1))  == 1) ? 1:-1;
        np->columnVal[i][4]= ( ((np->hash[i] >>3) & (1))  == 1) ? 1:-1;
        np->columnVal[i][5]= ( ((np->hash[i] >>2) & (1))  == 1) ? 1:-1;
        np->columnVal[i][6]= ( ((np->hash[i] >>1) & (1))  == 1) ? 1:-1;
        np->columnVal[i][7]= ( ((np->hash[i] >>0) & (1))  == 1) ? 1:-1; 
    }

}
////////////////////////////////////////////////////////////////////////////
void freeLinkedList(NodePointer listHead){
    if(listHead != NULL)    freeLinkedList(listHead->next);    
    free(listHead);       
}

////////////////////////////////////////////////////////////////////////////
void insertIntoLinkedList(char * token, NodePointer* listHead){

   NodePointer newNode = NULL;
   NodePointer current = *listHead;

    //create a node on the heap
   newNode = malloc(sizeof(Node));

   if(NULL != newNode){

      strcpy(newNode->data, token);
      
      //calculating MD5 hash of token  
      MD5((const unsigned char *)token, strlen(newNode->data), newNode->hash);
      
      setColumnVal(newNode);
      //insert at beginning of linked list
         newNode->next = current;
         *listHead = newNode; 
   }
}

////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG
void displayLinkedList(NodePointer current){
   if(NULL == current){
      printf("LIST EMPTY!\n\n");
      return;
   }

   //loop through list
   while(NULL != current){

      printf("\n\n[%s]\t:\t", current->data);
      for(size_t i = 0; i < MD5_DIGEST_LENGTH; i++)
      {
          printf("%02x ", current->hash[i]);
      }
      printf("\n");
      printf("COLUMN VALUES:\n");
      
         displayColumnVal(current);
      
      current = current->next;
   }
   printf("\n\n");
}
#endif

////////////////////////////////////////////////////////////////////////////
char* simHash(const char* delim, char* inputStr, char* simHash){
    
   char* token; 
   NodePointer head = NULL;

   while ((token = strtok_r(inputStr, delim, &inputStr))) {
        insertIntoLinkedList(token, &head);
   }

   #ifdef __DEBUG
      displayLinkedList(head);
   #endif
   //calculating simHash
   
   calcuteSimHash(head, simHash);
   freeLinkedList(head);
    
   return simHash;
}




