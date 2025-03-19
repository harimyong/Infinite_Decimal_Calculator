#include "expression.h"

bool isNUM_ASCII(char data){ return '0'<=data && data<='9'; }

Expr* NumPreprocessing(LinkedList *expr){
    Expr* EXPR=EInit();
    if(LLisEmpty(expr)) return NULL;
    NODE* now=expr->head->next;
    while(now->next!=NULL){
        if(isNUM_ASCII(now->data)){
            LinkedList* NUMBER=LLInit();
            bool flag=False;
            while(isNUM_ASCII(now->data) || now->data=='.'){
                if(now->data=='.'){
                    if(!flag) flag=True;
                    else return NULL;
                } 
                LLpushBack(NUMBER,now->data);
                now=now->next;
            }
            ExprNODE* newElement=makeExprNODE(NUMBER,'+');
            if(flag) newElement->isFloat=true;
            EpushBack(EXPR,newElement);
        }else{
            ExprNODE* newElement=makeExprNODE(NULL,now->data);
            now=now->next;
            EpushBack(EXPR,newElement);
        }
    }
    LLAllRemove(expr);
    return EXPR;
}

Expr* EInit(){ 
    Expr* EXPR=(Expr*)malloc(sizeof(Expr)); 
    if(EXPR==NULL) return NULL;
    EXPR->head=makeExprNODE(NULL,0); if(EXPR->head==NULL) return NULL;
    EXPR->tail=makeExprNODE(NULL,0); if(EXPR->tail==NULL) return NULL;
    EXPR->head->prev=NULL;
    EXPR->head->next=EXPR->tail;
    EXPR->tail->prev=EXPR->head;
    EXPR->tail->next=NULL;
    return EXPR;
}
ExprNODE* makeExprNODE(LinkedList* NUMBER,char oper){
    ExprNODE* newNode=(ExprNODE*)malloc(sizeof(ExprNODE));
    if(newNode==NULL) return NULL;
    newNode->oper=oper;
    newNode->NUMBER=NUMBER;
    newNode->prev=newNode;
    newNode->next=newNode;
    newNode->isFloat=False;
    return newNode;
}

void EpushFront(Expr *E,ExprNODE *data){
    data->next=E->head->next;
    data->prev=E->head;
    E->head->next->prev=data;
    E->head->next=data;
}
void EpushBack(Expr *E,ExprNODE *data){
    data->next=E->tail;
    data->prev=E->tail->prev;
    E->tail->prev->next=data;
    E->tail->prev=data;
}

bool EPrint(Expr *E){
    if(EisEmpty(E)) return false;
    ExprNODE* now=E->head->next;
    while(now!=NULL && now->next!=NULL){
        if(now->NUMBER!=NULL) { ENumberPrint(now); }  
        else { printf("%c",now->oper); }
        now=now->next;
    }
    return true;
}

bool EisEmpty(Expr *E){ return E->head->next->oper==0 && E->head->next->NUMBER==NULL; }

bool EElementRemove(Expr *E){
    if(EisEmpty(E)) return false;
    ExprNODE* now=E->head->next;
    E->head->next=E->tail;
    E->tail->prev=E->head;
    while(now->NUMBER!=NULL || now->oper!=0){
        ExprNODE* nxt=now->next;
        free(now->NUMBER);
        free(now);
        now=nxt;
    }
    return true;
}
void EHeadTailRemove(Expr *E){
    ExprNODE* H=E->head;
    ExprNODE* T=E->tail;
    free(H->NUMBER);
    free(T->NUMBER);
    free(H); free(T);
}
bool EAllRemove(Expr *E){
    if(EElementRemove(E)==false) return false;
    EHeadTailRemove(E); free(E);
    return true;
}
bool MatchSign(ExprNODE* EN,char oper){
    if(EN->NUMBER!=NULL) return false;
    return EN->oper==oper;
}
bool isNUMBER(ExprNODE* EN){ return EN->NUMBER!=NULL && (EN->oper=='+' || EN->oper=='-'); }
bool isOper(ExprNODE* EN){ return EN->NUMBER==NULL && EN->oper!=0; }
bool isZero(ExprNODE* N){
    NODE* now=N->NUMBER->head;
    while(now->next->data!=0){
        now=now->next;
        if(now->data!='0') return false;
    }
    return true;
}

void ENumberPrint(ExprNODE *EN){
    if(isNUMBER(EN)==false) printf("숫자가 아닙니다!\n");
    else { /*printf("%d / ",EN->isFloat); printf("%c",EN->oper);*/ LLPrint(EN->NUMBER); }
}

void DeleteExprNODE(ExprNODE *E){
    LLAllRemove(E->NUMBER); 
    E->prev->next=E->next;
    E->next->prev=E->prev;
    free(E);
}