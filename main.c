#include "calculator.h"

LinkedList* ExprInput();

int main(){
    LinkedList* Bef_input=ExprInput(); //Input Expression
    if(NO_InputERROR(Bef_input)) { LLHeadTailRemove(Bef_input); free(Bef_input); return 0; } //If NO inputError, memory free -> exit program
    Expr* Aft_input=NumPreprocessing(Bef_input);//number of inputed Expression preprocessing
    int ErrorCode=1;
    if((ErrorCode=catchError(Aft_input))!=1){ //If NOTVALID inputError, exit program
        printf("error! code : %d\n",ErrorCode);
        if(Aft_input!=NULL) EAllRemove(Aft_input);
        return 0;
    }

    printf("Inputed Expression\n"); EPrint(Aft_input); printf("\n\n"); //Print inputed expression

    //Caculate
    Input_NODE=Aft_input->head->next;
    ExprNODE* res=EXPR_PROCESSOR();
    //Print Caculated Result
    if(res==NULL){  EAllRemove(Aft_input); return 0; }
    else{ PopZero(res); printf("Caculated Result\n%c",res->oper); ENumberPrint(res); printf("\n"); }


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