#include <stdio.h>


int factorial(int number1);

int main() {
    printf("Hello, Факториал\n"
           "Составить функцию вычисления N!. Использовать ее при вычислении факториала\n"
           "int factorial(int n)!\n");

    int number1 = 10;
    scanf("%d", &number1);

    int result = factorial(number1);

    printf("Факториал: %d\n", result);

    return 0;
}

int factorial(int number1) {
    int result = 1;
    for (int i = 1; i <= number1; ++i) {
        result *= i;
    }

    return result;
}
