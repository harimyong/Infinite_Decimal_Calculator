#include "node.h"
NODE* makeNode(char data){
    NODE* newNode=(NODE*)malloc(sizeof(NODE));
    if(newNode==NULL) return NULL;
    newNode->data=data;
    newNode->prev=newNode;
    newNode->next=newNode;
    return newNode;
}