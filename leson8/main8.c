#include <stdio.h>

int main() {
    printf("Hello, B11 ДЗ 5!\n");

    int number, remainder, reverse = 0;

    printf("Введите целое неотрицательное число: ");
    scanf("%d", &number);

    while (number != 0) {
        remainder = number % 10;
        reverse = reverse * 10 + remainder;
        number = number / 10;
    }
    printf("Перевернутое число: %d\n", reverse);

    return 0;
}
