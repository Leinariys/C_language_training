#include <stdio.h>

int middle(int a, int b) {
    return (a + b) / 2;
}

int main() {
    printf("Hello, C3 Практ 1\n"
           "Среднее арифметическое чисел\n"
           "Написать функцию, которая возвращает среднее арифметическое двух переданных ей аргументов (параметров).\n"
           "int middle(int a, int b)!\n");

    int number1 = 10;
    int number2 = 20;

    scanf("%d %d", &number1, &number2);

    int result = middle(number1, number2);
    printf("Среднее значение: %d\n", result);

    return 0;
}
