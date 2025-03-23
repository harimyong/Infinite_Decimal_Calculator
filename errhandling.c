#include "errhandling.h"

int catchError(Expr *expr){
    int res;
    if(EisEmpty(expr)) return NOInput;
    if(expr==NULL) return Outofmemory;
    res=elementCheck(expr); if(res!=1) return res;
    res=parenthesesCheck(expr); if(res!=1) return res;
    res=SignCheck(expr); if(res!=1) return res;
    return true;
}

int SignCheck(Expr *expr){
    ExprNODE* now=expr->head;
    if(expr->head->next->oper=='*' || expr->head->next->oper=='/') return SOFisAO;
    if(isOper(expr->tail->prev) && !(expr->tail->prev->oper==')')) return EOFisAO;
    while(now->next!=expr->tail){
        now=now->next;
        if(now->next!=expr->tail){
            char nxtoper=now->next->oper;
            if(isAO(now) && isOper(now->next) && !(nxtoper=='(')) return SignPositionError;
            else if(now->oper=='('){
                if(nxtoper==')') return Pblank;
                if(nxtoper=='*' || nxtoper=='/') return SignPositionError;
            }
        }
    }
    return 1;
}

int parenthesesCheck(Expr *expr){
    ExprNODE* now=expr->head;
    int cnt=0;
    while(now->next!=expr->tail){
        now=now->next;
        if(now->oper=='(') cnt++;
        else if(now->oper==')'){
            if(cnt>0) cnt--;
            else return TooFewP;
        }
    }
    if(cnt>0) return TooManyP;
    else if(cnt<0) return TooFewP;
    return 1;
}

int elementCheck(Expr *expr){
    ExprNODE* now=expr->head;
    while(now->next!=expr->tail){
        now=now->next;
        if(isNUMBER(now)){
            if(!numberCheck(now)) return NotValidNForm;
        }else if(isOper(now)){
            if(!operCheck(now)) return NotValidOForm;
        }
    }
    return 1;
}

bool numberCheck(ExprNODE* N){ return !(N->isFloat==true && N->NUMBER->tail->prev->data=='.'); }

bool isP(ExprNODE *O){ return O->oper=='(' || O->oper==')'; }

bool isAO(ExprNODE *O){
    if(!isOper(O)) return false;
    switch(O->oper)
    {
        case '+': break;
        case '-': break;
        case '*': break;
        case '/': break;
        default: return false;
    }
    return true;
}

bool operCheck(ExprNODE* O){
    if(!isOper(O)) return false;
    switch(O->oper)
    {
        case '+': break;
        case '-': break;
        case '*': break;
        case '/': break;
        case '(': break;
        case ')': break;
        default: return false;
    }
    return true;
}

bool NO_InputERROR(LinkedList *L){
    if(L==NULL || LLisEmpty(L)) {printf("오류! 식을 입력하지 않았습니다.\n");return true;}
    return false;
}