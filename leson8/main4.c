#include <stdio.h>

int main() {
    printf("Hello, B6 Урок 5 Практика №2!\n");

    int number;
    scanf("%d", &number);

    int lastDigit = number % 10;
    number /= 10;

    while (number > 0) {
        if (lastDigit == number % 10) {
            printf("YES\n");
            return 0;
        }
        lastDigit = number % 10;
        number /= 10;
    }

    printf("NO\n");

    return 0;
}
