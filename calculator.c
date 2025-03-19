#include "calculator.h"

//Calcultaion Functions - Polynomial Processing
ExprNODE* EXPR_PROCESSOR(){
    ExprNODE* res=TERM_PROCESSOR();
    while(Input_NODE->oper=='+' || Input_NODE->oper=='-'){
        if(MatchSign(Input_NODE,'+')){
            Input_NODE=Input_NODE->next;
            res=ADD(res,TERM_PROCESSOR());
        }
        else if(MatchSign(Input_NODE,'-')){
            Input_NODE=Input_NODE->next;
            res=SUB(res,TERM_PROCESSOR());
        }
    }
    return res;
}
ExprNODE* TERM_PROCESSOR(){
    ExprNODE* res=FACTOR_PROCESSOR();
    while(Input_NODE->oper=='*' || Input_NODE->oper=='/' || Input_NODE->oper=='('){
        if(MatchSign(Input_NODE,'*')){
            Input_NODE=Input_NODE->next;
            res=MUL(res,FACTOR_PROCESSOR());
        }
        else if(MatchSign(Input_NODE,'/')){
            Input_NODE=Input_NODE->next;
            res=DIV(res,FACTOR_PROCESSOR());
        }
        else if(MatchSign(Input_NODE,'(')){
            Input_NODE=Input_NODE->next;
            res=MUL(res,EXPR_PROCESSOR());
            if(MatchSign(Input_NODE,')')){
                Input_NODE=Input_NODE->next;
            }else{
                return NULL;
            }
        }
    }
    return res;
}
ExprNODE* FACTOR_PROCESSOR(){
    ExprNODE* res=makeExprNODE(LLInit(),'+');
    LLpushBack(res->NUMBER,'0');
    char res_oper='+';
    if(!isNUMBER(Input_NODE) && MatchSign(Input_NODE,'-')){
        res_oper='-';
        Input_NODE=Input_NODE->next;
    }
    if(!isNUMBER(Input_NODE) && MatchSign(Input_NODE,'(')){
        Input_NODE=Input_NODE->next;
        res=EXPR_PROCESSOR();
        if(MatchSign(Input_NODE,')')){
            Input_NODE=Input_NODE->next;
            if(res->oper=='+'){
                if(res_oper=='-') res->oper='-';
            } else{
                if(res_oper=='-') res->oper='+';
            }
        }else{
            return NULL;
        }
    }
    else if(isNUMBER(Input_NODE)){
        res=CopyNumber(Input_NODE);
        Input_NODE=Input_NODE->next;
        if(res_oper=='-') res->oper='-';
    }else{
        return NULL;
    }
    return res;
}

//Calculation Functions - Binary Operation
ExprNODE* ADD(ExprNODE* A,ExprNODE* B){
    if(isZero(A)){ 
        DeleteExprNODE(A);
        ExprNODE* res=CopyNumber(B);
        DeleteExprNODE(B);
        return res; 
    }
    if(isZero(B)){ 
        DeleteExprNODE(B);
        ExprNODE* res=CopyNumber(A);
        DeleteExprNODE(A);
        return res; 
    }
    if(A->oper=='+' && B->oper=='-'){
        B->oper='+'; return SUB(A,B);
    }else if(A->oper=='-' && B->oper=='+'){
        A->oper='+'; return SUB(B,A);
    }

    char Res_oper='+';
    if(A->oper=='-') Res_oper='-'; 
    ExprNODE* Result=makeExprNODE(LLInit(),Res_oper);
    PopZero(A); PopZero(B);
    FillZero(A,B);
    NODE* Anow=A->NUMBER->tail;
    NODE* Bnow=B->NUMBER->tail;
    char UP=0;
    while(Anow->prev->data!=0 && Bnow->prev->data!=0){
        Anow=Anow->prev; Bnow=Bnow->prev;
        if(Anow->data=='.' && Bnow->data=='.'){
            LLpushFront(Result->NUMBER,'.');
            Result->isFloat=true;
            continue;
        }
        char tot=(Anow->data)+(Bnow->data)-96+UP; UP=0;
        if(tot>=10){
            tot-=10; 
            UP++;
        }
        LLpushFront(Result->NUMBER,tot+48);
    }
    if(UP!=0) LLpushFront(Result->NUMBER,UP+48);
    //+ + + -> ADD
    //+A + -B -> +A - +B -> SUB
    //-A + +B -> +B + -A -> +B - +A -> SUB 
    //-A + -B -> -(A+B) -> ADD
    PopZero(A); PopZero(B); PopZero(Result);
    DeleteExprNODE(A); DeleteExprNODE(B);
    return Result;
}

ExprNODE* SUB(ExprNODE* A,ExprNODE* B){
    if(isZero(A)){
        if(B->oper=='+') B->oper='-';
        else B->oper='+';
        DeleteExprNODE(A);
        ExprNODE* res=CopyNumber(B);
        DeleteExprNODE(B);
        return res; 
    }
    if(isZero(B)) { 
        DeleteExprNODE(B); 
        ExprNODE* res=CopyNumber(A);
        DeleteExprNODE(A);
        return res; 
    }

    if(A->oper=='+' && B->oper=='-'){
        B->oper='+'; return ADD(A,B);
    }else if(A->oper=='-' && B->oper=='+'){
        B->oper='-'; return ADD(A,B);
    }else if(A->oper=='-' && B->oper=='-'){
        A->oper='+'; B->oper='+';
        return SUB(B,A);
    }
    if(CompareAB(A,B)==false){ ExprNODE* res=SUB(B,A); res->oper='-'; return res; }

    ExprNODE* Result=makeExprNODE(LLInit(),'+');
    PopZero(A); PopZero(B);
    FillZero(A,B);
    NODE* Anow=A->NUMBER->tail;
    NODE* Bnow=B->NUMBER->tail;
    char DOWN=0;
    while(Anow->prev->data!=0 && Bnow->prev->data!=0){
        Anow=Anow->prev; Bnow=Bnow->prev;
        if(Anow->data=='.'){ LLpushFront(Result->NUMBER,'.'); Result->isFloat=true;}
        if(Anow->data!='.'){
            char tot=(Anow->data)-(Bnow->data)+DOWN; DOWN=0;
            if(tot<0){ tot+=10; DOWN-=1; }
            //printf("%d\n",tot);
            LLpushFront(Result->NUMBER,tot+48);
        }
    }
    //+A - +B -> SUB (If A<B, -sub(B,A))
    //+A - -B -> +A + +B -> ADD
    //-A - +B -> -A + -B -> ADD 
    //-A - -B -> -A + +B -> +B + -A -> +B - +A -> SUB
   
    PopZero(A); PopZero(B); PopZero(Result);
    DeleteExprNODE(A); DeleteExprNODE(B);
    return Result;
}

ExprNODE* MUL(ExprNODE* A,ExprNODE* B){
    if(isZero(A)){ 
        DeleteExprNODE(B);
        ExprNODE* res=CopyNumber(A);
        DeleteExprNODE(A);
        return res; 
    }
    if(isZero(B)){ 
        DeleteExprNODE(A);
        ExprNODE* res=CopyNumber(B);
        DeleteExprNODE(B);
        return res; 
    }
    char res_oper='+';
    if(A->oper!=B->oper) res_oper='-';
    NODE* Zeronow;
    PopZero(A); PopZero(B);
    
    //Mutliply
    ExprNODE* Tot_E=makeExprNODE(LLInit(),'+');
    LLpushBack(Tot_E->NUMBER,'0');
    NODE* Bnow=B->NUMBER->tail;
    while(Bnow->prev->data!=0){
        Zeronow=B->NUMBER->tail->prev;
        Bnow=Bnow->prev;
        if(Bnow->data=='.' || Bnow->data=='0') continue;
        ExprNODE* temp=makeExprNODE(LLInit(),'+');
        NODE* Anow=A->NUMBER->tail;
        char UP=0;
        while(Anow->prev->data!=0){
            Anow=Anow->prev;
            if(Anow->data=='.') continue;
            char tot=((Anow->data)-48)*((Bnow->data)-48)+UP;
            UP=tot/10;
            if(tot>=10) tot%=10;
            LLpushFront(temp->NUMBER,tot+48);
        }
        if(UP) LLpushFront(temp->NUMBER,UP+48);
        while(Zeronow!=Bnow){
            Zeronow=Zeronow->prev;
            if(Zeronow->data!='.')
            LLpushBack(temp->NUMBER,'0');
        }
        Tot_E=ADD(Tot_E,temp);
    }

    NODE* temp=A->NUMBER->tail;
    while(A->isFloat && temp->prev->data!='.'){ temp=temp->prev; DIVbyTen(Tot_E); }
    temp=B->NUMBER->tail;
    while(B->isFloat && temp->prev->data!='.'){ temp=temp->prev; DIVbyTen(Tot_E); }
    Tot_E->oper=res_oper;
    DeleteExprNODE(A); DeleteExprNODE(B);
    PopZero(Tot_E);
    return Tot_E;
}

ExprNODE* DIV(ExprNODE* A,ExprNODE* B){
    if(isZero(B)) return NULL; //Division By Zero Error
    if(isZero(A)){ DeleteExprNODE(B); return CopyNumber(A); } // 0 / B = 0
    PopZero(A); PopZero(B);
    CuttingDecimal(A); CuttingDecimal(B);
    ExprNODE* CopiedA=CopyNumber(A);
    ExprNODE* CopiedB=CopyNumber(B);
    CopiedA->oper='+'; CopiedB->oper='+';
    int cnt=0;
    char Q_oper='+';
    if(A->oper!=B->oper) Q_oper='-';

    ExprNODE* Q_EN=makeExprNODE(LLInit(),'+');
    ExprNODE* R_EN=makeExprNODE(LLInit(),'+');
    //Divide
    int aDecimalDigit=0, bDecimalDigit=0;
    NODE* now;
    now=CopiedA->NUMBER->tail;
    if(CopiedA->isFloat){
        while(now->prev->data!='.'){
            aDecimalDigit++;
            now=now->prev;
        }
        now=now->prev;
        now->prev->next=now->next;
        now->next->prev=now->prev;
        free(now);
        CopiedA->isFloat=false;
    }
    now=CopiedB->NUMBER->tail;
    if(CopiedB->isFloat){
        while(now->prev->data!='.'){
            bDecimalDigit++;
            now=now->prev;
        }
        now=now->prev;
        now->prev->next=now->next;
        now->next->prev=now->prev;
        free(now);
        CopiedB->isFloat=false;
    }
    int moveDecimalDigit=aDecimalDigit-bDecimalDigit;

    PopZero(CopiedA); PopZero(CopiedB);
    
    now=CopiedA->NUMBER->head;
    while(cnt<Operation_Count){
        if(now->next->data!=0){
            now=now->next;
            LLpushBack(R_EN->NUMBER,now->data);
        }else{
            if(!Q_EN->isFloat){
                LLpushBack(Q_EN->NUMBER,'.');
                Q_EN->isFloat=true;
                continue;
            }
            cnt++;
            LLpushBack(R_EN->NUMBER,48);
        }
        if(!isSameAB(CopiedB,R_EN) && CompareAB(CopiedB,R_EN)) LLpushBack(Q_EN->NUMBER,48); //나누는 수 B > 나머지 R
        else{ //B<=R
            ExprNODE* temp=makeExprNODE(LLInit(),'+');
            LLpushBack(temp->NUMBER,'0');
            int idx=0;
            for(int i=1;i<10;i++){
                temp=ADD(temp,CopyNumber(CopiedB));
                if(CompareAB(R_EN,temp)){ //R>=temp
                    idx=i;
                }else{
                    temp=SUB(temp,CopyNumber(CopiedB));
                    break;
                }
            }
            LLpushBack(Q_EN->NUMBER,idx+48);
            R_EN=SUB(R_EN,temp);
        }
    }
    if(moveDecimalDigit>0) {
        for(int i=0;i<moveDecimalDigit;i++)   
        DIVbyTen(Q_EN);
    }else if(moveDecimalDigit<0){
        for(int i=0;i<(-moveDecimalDigit);i++)   
        MULbyTen(Q_EN);
    }
    DeleteExprNODE(CopiedA); DeleteExprNODE(CopiedB);
    DeleteExprNODE(A); DeleteExprNODE(B); DeleteExprNODE(R_EN);
    PopZero(Q_EN);
    Q_EN->oper=Q_oper;
    return Q_EN;
}

//Utilitys
bool CompareAB(ExprNODE* A,ExprNODE* B){ 
    if(isSameAB(A,B)==true) return true;
    FillZero(A,B);
    NODE* Anow=A->NUMBER->head;
    NODE* Bnow=B->NUMBER->head;
    while(Anow->next->data!=0 && Bnow->next->data!=0){
        Anow=Anow->next; Bnow=Bnow->next;
        if(Anow->data==Bnow->data) continue;
        else if(Anow->data>Bnow->data) { PopZero(A); PopZero(B); return true; }
        else { PopZero(A); PopZero(B); return false; }
    }
}

bool isSameAB(ExprNODE* A,ExprNODE* B){ 
    FillZero(A,B);
    NODE* Anow=A->NUMBER->head;
    NODE* Bnow=B->NUMBER->head;
    while(Anow->next->data!=0 && Bnow->next->data!=0){
        Anow=Anow->next; Bnow=Bnow->next;
        if(Anow->data!=Bnow->data) { PopZero(A); PopZero(B); return false; }
    }
    PopZero(A); PopZero(B);
    return true;
}

void FillZero(ExprNODE* A,ExprNODE* B){
    //Fill Front
    NODE* Anow=A->NUMBER->tail;
    if(A->isFloat){
        while(Anow->prev->data!='.') Anow=Anow->prev;
        Anow=Anow->prev;
    }
    NODE* Bnow=B->NUMBER->tail;
    if(B->isFloat){
        while(Bnow->prev->data!='.') Bnow=Bnow->prev;
        Bnow=Bnow->prev;
    }
    while(Anow->prev!=NULL || Bnow->prev!=NULL){
        if(Anow->prev!=NULL) Anow=Anow->prev;
        else LLpushFront(A->NUMBER,'0');
        if(Bnow->prev!=NULL) Bnow=Bnow->prev;
        else LLpushFront(B->NUMBER,'0');
    }
    LLpushFront(A->NUMBER,'0');
    LLpushFront(B->NUMBER,'0');

    if(!A->isFloat and !B->isFloat) return;

    //Fill Back
    if(A->isFloat){
        Anow=A->NUMBER->tail;
        while(Anow->prev->data!='.') Anow=Anow->prev;
        Anow=Anow->prev;
    }else{
        LLpushBack(A->NUMBER,'.');
        A->isFloat=true;
        Anow=A->NUMBER->tail->prev;
    }
    if(B->isFloat){
        Bnow=B->NUMBER->tail;
        while(Bnow->prev->data!='.') Bnow=Bnow->prev;
        Bnow=Bnow->prev;
    }else{
        LLpushBack(B->NUMBER,'.');
        B->isFloat=true;
        Bnow=B->NUMBER->tail->prev;
    }
    while(Anow->next!=NULL || Bnow->next!=NULL){
        if(Anow->next!=NULL) Anow=Anow->next;
        else LLpushBack(A->NUMBER,'0');
        if(Bnow->next!=NULL) Bnow=Bnow->next;
        else LLpushBack(B->NUMBER,'0');
    }
}

void PopZero(ExprNODE *N){
    NODE* now=N->NUMBER->head;
    while(now->next->data=='0') LLpopFront(N->NUMBER);
    if(N->isFloat){
        if(N->NUMBER->head->next->data=='.') LLpushFront(N->NUMBER,'0');
        now=N->NUMBER->tail;
        while(now->prev->data=='0') LLpopBack(N->NUMBER);
        if(N->NUMBER->tail->prev->data=='.'){
            LLpopBack(N->NUMBER);
            N->isFloat=false;
        }
    }
    if(LLisEmpty(N->NUMBER) || (N->isFloat && N->NUMBER->head->next->data=='.')) LLpushFront(N->NUMBER,'0');
}

void MULbyTen(ExprNODE *N){
    if(N->isFloat==false) LLpushBack(N->NUMBER,'0'); 
    else{
        if(N->NUMBER->tail->prev->prev->data=='.'){
            NODE* removeNODE=N->NUMBER->tail->prev->prev;
            N->isFloat=true;
            N->NUMBER->tail->prev->prev->prev->next=N->NUMBER->tail->prev;
            N->NUMBER->tail->prev->prev=N->NUMBER->tail->prev->prev->prev;
            free(removeNODE);
            N->isFloat=false;
            PopZero(N);
        }else{
            NODE* Anow=N->NUMBER->head;
            while(Anow->next->data!='.') Anow=Anow->next;
            Anow=Anow->next;
            NODE* Bnow=Anow->next;
            char temp=Anow->data;
            Anow->data=Bnow->data;
            Bnow->data=temp;
            PopZero(N);
            if(N->NUMBER->head->next->data=='.') LLpushFront(N->NUMBER,'0');
        }   
    }
}

void DIVbyTen(ExprNODE *N){
    if(N->isFloat==false){
        if(N->NUMBER->tail->prev->data=='0') LLpopBack(N->NUMBER);
        else{
            LLpushBack(N->NUMBER,'.');
            NODE* point=N->NUMBER->tail->prev;
            NODE* num=point->prev;
            char temp=point->data;
            point->data=num->data;
            num->data=temp;
            N->isFloat=true;
        }
    }
    else{
        if(N->NUMBER->head->next->next->data=='.'){
            NODE* removeNODE=N->NUMBER->head->next->next;
            removeNODE->prev->next=removeNODE->next;
            removeNODE->next->prev=removeNODE->prev;
            free(removeNODE);
            LLpushFront(N->NUMBER,'.');
            LLpushFront(N->NUMBER,'0');
        }else{
            NODE* point=N->NUMBER->head;
            while(point->next->data!='.') point=point->next;
            point=point->next;
            NODE* num=point->prev;
            char temp=point->data;
            point->data=num->data;
            num->data=temp;
        }
    }
}

void CuttingDecimal(ExprNODE *N){
    if(!N->isFloat) return;
    int cnt=0;
    NODE* now=N->NUMBER->head;
    while(now->next->data!='.'){ 
        now=now->next; 
    }
    now=now->next;
    while(now->next->data!=0 && cnt<Cutting_digit){
        cnt++;
        now=now->next;
    }
    if(cnt<=Cutting_digit) return;
    while(now!=N->NUMBER->tail->prev){
        LLpopBack(N->NUMBER);
    }
}

ExprNODE* CopyNumber(ExprNODE *N){
    ExprNODE* new=makeExprNODE(LLInit(),N->oper);
    new->isFloat=N->isFloat;
    NODE* now=N->NUMBER->head;
    while(now->next->data!=0){
        now=now->next;
        LLpushBack(new->NUMBER,now->data);
    }
    return new;
}