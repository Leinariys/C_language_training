#include <stdio.h>

int main() {
    printf("Hello, B3 Урок 5 ДЗ 1!\n");

    int a, b;
    int sum = 0;
    scanf("%d %d", &a, &b);

    for (int i = a; i <= b; i++) {
        sum += i * i;
    }
    printf("%d\n", sum);

    return 0;
}
