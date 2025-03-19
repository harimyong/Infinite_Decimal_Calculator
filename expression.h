#include "number.h"
typedef struct ExprNODE{
    LinkedList* NUMBER;
    char oper;
    struct ExprNODE* next;
    struct ExprNODE* prev;
    bool isFloat;
}ExprNODE;

typedef struct 
{
    ExprNODE* head;
    ExprNODE* tail;
}Expr;

ExprNODE* Input_NODE;

ExprNODE* makeExprNODE(LinkedList* NUMBER,char oper);
Expr* EInit();
Expr* NumPreprocessing(LinkedList *expr);
bool isNUM_ASCII(char data);
void EpushFront(Expr *E,ExprNODE *data);
void EpushBack(Expr *E,ExprNODE *data);
bool EisEmpty(Expr *E);
bool EPrint(Expr *E);
bool EElementRemove(Expr *E);
void EHeadTailRemove(Expr *E);
bool EAllRemove(Expr *E);
bool MatchSign(ExprNODE* EN,char oper);
bool isZero(ExprNODE* N);
bool isNUMBER(ExprNODE* EN);
bool isOper(ExprNODE* EN);
void ENumberPrint(ExprNODE *EN);
void DeleteExprNODE(ExprNODE *E);