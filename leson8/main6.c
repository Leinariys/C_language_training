#include <stdio.h>

int main() {
    printf("Hello, B9 Урок 5 ДЗ 3!\n");

    int number;
    scanf("%d", &number);

    while (number > 0) {
        if ((number % 10) % 2 != 0) {
            printf("NO\n");
            return 0;
        }
        number /= 10;
    }

    printf("YES\n");

    return 0;
}
