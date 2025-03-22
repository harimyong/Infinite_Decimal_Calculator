#include "calculator.h"

LinkedList* ExprInput();

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
        EAllRemove(Aft_input);
        return 0;
    }else{
        PopZero(res);
        printf("Caculated Result\n%c",res->oper); ENumberPrint(res); printf("\n");
    }

    //Print Caculated Result

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