#include "calculator.h"

LinkedList* ExprInput();

//ERROR Catch Functions
bool NO_InputERROR(LinkedList *L);
bool NOTVALID_InputERROR(Expr *E);

int main(){
    LinkedList* Bef_input=ExprInput(); //Input Expression
    if(NO_InputERROR(Bef_input)) { LLHeadTailRemove(Bef_input); free(Bef_input); return 0; } //If NO inputError, memory free -> exit program
    Expr* Aft_input=NumPreprocessing(Bef_input);//number of inputed Expression preprocessing
    if(NOTVALID_InputERROR(Aft_input)) return 0; //If NOTVALID inputError, exit program

    //Print inputed expression
    printf("Inputed Expression\n"); EPrint(Aft_input); printf("\n\n");

    //Caculate
    Input_NODE=Aft_input->head->next;
    ExprNODE* res=EXPR_PROCESSOR();
    if(res==NULL){
        printf("error!\n");
    }

    //Print Caculated Result
    printf("Caculated Result\n%c",res->oper); ENumberPrint(res); printf("\n");

    //Memory free(Result Memory free, inputed expression)
    DeleteExprNODE(res);
    EAllRemove(Aft_input);
    return 0;
}

LinkedList* ExprInput(){
    char c=getchar();
    LinkedList* LL=LLInit();
    while(c!=EOF){
        LLpushBack(LL,c);
        c=getchar();
    }
    return LL;    
}

bool NO_InputERROR(LinkedList *L){
    if(L==NULL || LLisEmpty(L)) {printf("오류! 식을 입력하지 않았습니다.\n");return true;}
    return false;
}
bool NOTVALID_InputERROR(Expr *E){
    if(E==NULL) {printf("오류! 메모리가 부족하거나 식이 잘못된 형태입니다.\n"); return true;}
    return false;
}