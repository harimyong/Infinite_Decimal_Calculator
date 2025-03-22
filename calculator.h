#include "errhandling.h"
#define Operation_Count 100
#define Cutting_digit Operation_Count/10

//Calcultaion Functions - Polynomial Processing
ExprNODE* EXPR_PROCESSOR();
ExprNODE* TERM_PROCESSOR();
ExprNODE* FACTOR_PROCESSOR();

//Calculation Functions - Binary Operation
ExprNODE* ADD(ExprNODE* A,ExprNODE* B);
ExprNODE* SUB(ExprNODE* A,ExprNODE* B);
ExprNODE* MUL(ExprNODE* A,ExprNODE* B); 
ExprNODE* DIV(ExprNODE* A,ExprNODE* B);

//Utilitys
ExprNODE* CopyNumber(ExprNODE *N);
bool CompareAB(ExprNODE* A,ExprNODE* B);
bool isSameAB(ExprNODE* A,ExprNODE* B);

void FillZero(ExprNODE* A,ExprNODE* B); //숫자 front,back에 0 push -> 숫자 자릿수 balancing
void PopZero(ExprNODE *E); // 숫자 front,back에 있는 0 pop
void MULbyTen(ExprNODE *N); //곱하기 10
void DIVbyTen(ExprNODE *N); //나누기 10
void CuttingDecimal(ExprNODE *N); //특정 소수점자리(Cutting_Digit)까지 자르기
