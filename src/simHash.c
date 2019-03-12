//Tokenization

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define MAX 64  //maximum characters in the word


struct node{
   char data[MAX];
   struct node* next;
};

typedef struct node Node;
typedef struct node* NodePointer;

void freeLinkedList(NodePointer listHead){
    if(listHead != NULL)    freeLinkedList(listHead->next);    
    
    free(listHead);       
}

void insertIntoLinkedList(char * token, NodePointer* listHead){

   NodePointer newNode = NULL;
   NodePointer current = *listHead;

    //create a node on the heap
   newNode = malloc(sizeof(Node));

   if(NULL != newNode){

      strcpy(newNode->data, token);

      //insert at beginning of linked list
         newNode->next = current;
         *listHead = newNode; 
   }
}


void displayLinkedList(NodePointer current){
   if(NULL == current){
      printf("LIST EMPTY!\n\n");
      return;
   }
   printf("TOKENS LIST:\n");

   //loop through list
   while(NULL != current){
      printf("%s, ", current->data);
      current = current->next;
   }
   printf("\n\n");
}




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