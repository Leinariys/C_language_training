#include <stdio.h>


int sumToN(int N) {
    int sum = 0;
    for(int i = 1; i <= N; i++)
        sum += i;
    return sum;
}

int main() {
    printf("Hello, C5 ДЗ \n"
           "Сумма от 1 до N\n"
           "Составить функцию, которая определяет сумму всех чисел от 1 до N и привести пример ее использования. !\n");

    int number1 = 10;
    scanf("%d", &number1);

    int result = sumToN(number1);

    printf("Сумма: %d\n", result);

    return 0;
}
