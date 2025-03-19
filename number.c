#include "number.h"
LinkedList* NInit(){ LinkedList* N=LLInit(); return N; }
void NpushFront(LinkedList *N,char data){ LLpushFront(N,data); }
void NpushBack(LinkedList *N,char data){ LLpushBack(N,data); }
void NElementRemove(LinkedList *N){ LLElementRemove(N); }
void NHeadTailRemove(LinkedList *N){ LLHeadTailRemove(N); }
void NAllRemove(LinkedList *N){ LLAllRemove(N); }
void NPrint(LinkedList *N){ LLPrint(N); }
bool NisEmpty(LinkedList *N){ LLisEmpty(N); }