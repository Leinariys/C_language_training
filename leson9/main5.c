#include <stdio.h>

int nod(int number1, int number2);

int main() {
    printf("Hello, C11 ДЗ \n"
           "НОД\n"
           "Составить функцию, которая определяет наибольший общий делитель двух натуральных и привести пример ее использования.\n"
           "int nod(int a, int b)!\n");

    int number1 = 10;
    int number2 = 10;
    scanf("%d%d", &number1, &number2);

    int result = nod(number1, number2);

    printf("НОД: %d\n", result);

    return 0;
}


int nod(int number1, int number2) {
    while (number1 != 0 && number2 != 0) {
        if (number1 >number2) {
            number1 = number1 %number2;
        } else {
           number2 =number2 % number1;
        }
    }
    return number1 +number2;
}
