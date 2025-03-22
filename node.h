#include <malloc.h>
#include <stdio.h>
typedef int bool;
#define false 0
#define true 1
#define False 0
#define True 1
#define and &&
#define or ||
typedef struct NODE
{
    char data;
    struct NODE *next;
    struct NODE *prev;
}NODE;

NODE* makeNode(char data);