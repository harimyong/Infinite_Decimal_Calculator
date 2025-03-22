#include "expression.h"

//AO(=Arithmetic operator) Error
#define TooManyAO -1//If AO next AO, if is Error
#define EOFisAO -2 //If End of FILE is AO, it is Error (but without ')')
#define SOFisAO -3 //If Start of FILE is AO, if is Error (but without '+','-','(')

//P(=parentheses) Error
#define TooManyP -4//If ('(' count )  <  (')' count ), it is Error
#define TooFewP -5//If ('(' count )  >  (')' count ), it is Error

//Element Error
#define NotValidNForm -6 //If Number is float and End of Number is decimal point, if is Error
#define NotValidOForm -7 //If Operator is not valid operator, it is Error

//Input Error
#define NOInput -8 //If FILE is EMPTY, it is Error



//Error Catch Functions
int catchError(Expr *expr); //<- 이름을 나중에 NOTVALID_InputERROR로 바꿔야 함.
bool numberCheck(ExprNODE* N);
bool operCheck(ExprNODE* O);

bool NO_InputERROR(LinkedList *L);
bool NOTVALID_InputERROR(Expr *E); // <- 추후에 삭제 예정, catchError
