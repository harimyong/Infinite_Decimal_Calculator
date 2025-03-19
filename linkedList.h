#include "node.h"
typedef struct
{
    NODE* head;
    NODE* tail;
}LinkedList;


LinkedList* LLInit(); //LinkedList init
void LLpushFront(LinkedList *L,char data); //front에 push
void LLpushBack(LinkedList *L,char data); //back에 push
bool LLpopFront(LinkedList *L); //front에서 pop (Only ONE)
bool LLpopBack(LinkedList *L); //Back에서 pop (Only ONE)


bool LLElementRemove(LinkedList *L); //head와 tail 제외하고 모든 노드 삭제
void LLHeadTailRemove(LinkedList *L); //head, tail 삭제
bool LLAllRemove(LinkedList *L); //모든 노드 삭제
bool LLPrint(LinkedList *L); //LinkedList L 출력
bool LLisEmpty(LinkedList *L); //LinkedList L 비어있는지 여부 반환 