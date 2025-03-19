#Infinite-Decimal-Calculator
무한 소수 계산기

일반 컴파일
gcc main.c node.c linkedList.c expression.c number.c calculator.c
메모리 누수 체크
gcc -g3 -fsanitize=address main.c node.c linkedList.c expression.c number.c calculator.c
./a.out < input.txt



해결해야할 과제

1. 에러 처리 미완 
    -괄호가 잘 열고 닫혀져있는지?
    -숫자에 소수점이 두개이상인가?
    -입력된 데이터 중 계산 중에 있어서 문제가 되는 데이터가 있는가?
    -식에서 연산기호가 연속으로 나왔는가?
    -공백이 포함되어있는가?
        -포함되어있다면 공백을 삭제한다. <- 할까말까 생각중...

2. 불필요한 코드 삭제