#include <stdio.h>

int main() {
    printf("Hello, B13!\n");

    int number, digit;
    int even = 0, odd = 0;

    printf("Введите целое неотрицательное число: ");
    scanf("%d", &number);

    while (number != 0) {
        digit = number % 10;

        if (digit % 2 == 0) {
            even++;
        } else {
            odd++;
        }

        number = number / 10;
    }

    printf("Количество четных и нечетных цифр: %d %d\n", even, odd);

    return 0;
}
