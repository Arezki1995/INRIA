#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

//For MD5 hashing
#include <openssl/md5.h>

#define MAX 64                      //maximum characters in the word
#define DIGEST_LENGTH 8             //number of bytes for the digest
 
struct node{
   char data[MAX];
   struct node* next;
   unsigned char hash[DIGEST_LENGTH];
};

typedef struct node Node;
typedef struct node* NodePointer;

////////////////////////////////////////////////////////////////////////////

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
      
      //calculating 16bits MD5 hash of token  
      const unsigned char* mot = (const unsigned char*) token;
      MD5(mot, sizeof(newNode->data), newNode->hash);
      
      //insert at beginning of linked list
         newNode->next = current;
         *listHead = newNode; 
   }
}

////////////////////////////////////////////////////////////////////////////
void displayLinkedList(NodePointer current){
   if(NULL == current){
      printf("LIST EMPTY!\n\n");
      return;
   }
   printf("TOKENS LIST:\n");

   //loop through list
   while(NULL != current){
      printf("%s \t:\t", current->data);
      for(size_t i = 0; i < DIGEST_LENGTH; i++)
      {
          printf("%d", current->hash[i]);
      }
      printf("\n");
      
      current = current->next;
   }
   printf("\n\n");
}


////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]){
    
    const char* delim =argv[1];
    char* token; 
    char* myString = argv[2]; 

    NodePointer head = NULL;

    while ((token = strtok_r(myString, delim, &myString))) {
        insertIntoLinkedList(token, &head);
    }
    displayLinkedList(head);
    freeLinkedList(head);
    
    return 0;
}