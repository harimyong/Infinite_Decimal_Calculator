#include "errhandling.h"

int catchError(Expr *expr){





    return true;
}

bool numberCheck(ExprNODE* N){
    return !(N->isFloat==true && N->NUMBER->tail->prev->data=='.');
}

bool operCheck(ExprNODE* O){
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
bool NOTVALID_InputERROR(Expr *E){
    if(E==NULL) {printf("오류! 메모리가 부족하거나 식이 잘못된 형태입니다.\n"); return true;}
    return false;
}