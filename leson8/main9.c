#include <stdio.h>

int main() {
    printf("Hello, B12!\n");

    int number, digit;
    int min = 9;
    int max = 0;

    printf("Введите целое неотрицательное число: ");
    scanf("%d", &number);

    while (number != 0) {
        digit = number % 10;

        if (digit > max) {
            max = digit;
        }

        if (digit < min) {
            min = digit;
        }

        number = number / 10;
    }

    printf("Наименьшая и наибольшая цифра: %d %d\n", min, max);

    return 0;
}
