#Infinite-Decimal-Calculator
무한 소수 계산기

일반 컴파일<br/>
gcc main.c node.c linkedList.c expression.c number.c calculator.c errhandling.c<br/>
메모리 누수 체크<br/>
gcc -g3 -fsanitize=address main.c node.c linkedList.c expression.c number.c calculator.c errhandling.c<br/>
./a.out < input.txt<br/><br/><br/><br/>



해결해야할 과제<br/><br/>

1. 에러 처리 미완 <br/>
    -괄호가 잘 열고 닫혀져있는지? => P(=parentheses) Error -> fin<br/> 
    -숫자에 소수점이 두개이상인가? => Element Error -> fin<br/>
    -입력된 데이터 중 계산 중에 있어서 문제가 되는 데이터가 있는가? => Element Error -> fin<br/>
    -식에서 연산기호가 연속으로 나왔는가? => Sign Error -> fin<br/>
    -공백이 포함되어있는가? => WAIT<br/>
        -포함되어있다면 공백을 삭제한다. <- 할까말까 생각중...<br/>

<br/>
2. 불필요한 코드 삭제<br/>
<br>
3. 프로그램 최적화<br/>