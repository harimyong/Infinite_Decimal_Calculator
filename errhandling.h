#include "expression.h"

//Sign Error
#define SignPositionError -1 //If the position of the operator is not appropriate, it is Error
#define EOFisAO -2 //If End of FILE is Sign, it is Error (but without ')')
#define SOFisAO -3 //If Start of FILE is Sign, if is Error (but without '+','-','(')


//P(=parentheses) Error
#define TooManyP -11//If ('(' count )  <  (')' count ), it is Error
#define TooFewP -12//If ('(' count )  >  (')' count ), it is Error
#define Pblank -13//IF '(' next is ')', it is Error

//Element Error
#define NotValidNForm -21 //If Number is float and End of Number is decimal point, if is Error
#define NotValidOForm -22 //If Operator is not valid operator, it is Error

//Input Error
#define NOInput -31 //If FILE is EMPTY, it is Error
#define Outofmemory -32

//Calculation Error
#define NotValidResult -99



//Error Catch Functions
int catchError(Expr *expr); //<- 이름을 나중에 NOTVALID_InputERROR로 바꿔야 함.
int SignCheck(Expr *expr); //산술연산자 위치 체크
int parenthesesCheck(Expr *expr); //단순히 괄호 개수만 체크
int elementCheck(Expr *expr); //element data 값을 체크
bool numberCheck(ExprNODE* N); //number의 형식인가?
bool operCheck(ExprNODE* O); //제공하는 Operator의 형식인가?
bool isAO(ExprNODE *O);
bool isP(ExprNODE* O);
bool NO_InputERROR(LinkedList *L);//bool NOTVALID_InputERROR(Expr *E); // <- 추후에 삭제 예정, catchError
