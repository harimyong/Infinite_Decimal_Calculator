# Infinite-decimal-decimal-number-Calculator
무한 소수 계산기

일반 컴파일
gcc main.c node.c linkedList.c expression.c number.c calculator.c
메모리 누수 체크
gcc -g3 -fsanitize=address main.c node.c linkedList.c expression.c number.c calculator.c
./a.out < input.txt

에러 처리 미완 <- 이것만 하면 완성