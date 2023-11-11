#include <stdio.h>

int main() {
    printf("Hello, B14 Практика 3!\n");

    int number;
    int count = 0;

    printf("Введите целые ненулевые числа. В конце последовательности введите ноль.\n");

    do {

        scanf("%d", &number);
        if (number != 0)
            count++;

    } while (number != 0);

    printf("Количество чисел в последовательности: %d\n", count);

    return 0;
}
