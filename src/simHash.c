#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

//For MD5 hashing
#include <openssl/md5.h>

#define MAX 64                      //maximum characters in the word
#define DIGEST_LENGTH   16           //number of bytes for the digest
#define CHAR_SIZE       8           //this is fixed not to be changed

struct node{
   char data[MAX];
   struct node* next;
   unsigned char hash[DIGEST_LENGTH];
   int columnVal[DIGEST_LENGTH][CHAR_SIZE];
};

typedef struct node Node;
typedef struct node* NodePointer;

////////////////////////////////////////////////////////////////////////////
void displayColumnVal(NodePointer n){
   for(size_t i = 0; i < DIGEST_LENGTH; i++)
   {
      for(size_t j = 0; j < CHAR_SIZE; j++)
      {
         printf("[%2d]", (n->columnVal[i][j]) );
      }
      printf("\n");
      
   }
   

}

////////////////////////////////////////////////////////////////////////////
void setColumnVal(NodePointer np){
    
    for(size_t i=0; i< DIGEST_LENGTH ;i++){
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
      
      //calculating 16bits MD5 hash of token  
      const unsigned char* mot = (const unsigned char*) token;
      MD5(mot, sizeof(newNode->data), newNode->hash);
      setColumnVal(newNode);
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

      printf("\n\n%s \t:\t", current->data);
      for(size_t i = 0; i < DIGEST_LENGTH; i++)
      {
          printf("%03d ", current->hash[i]);
      }
      printf("\n");
      printf("COLUMN VALUES:\n");
      displayColumnVal(current);
      
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