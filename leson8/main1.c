#include <stdio.h>

int main() {
    printf("Hello, B2 Урок 4 Практика 1!\n");

    int a, b;
    scanf("%d %d", &a, &b);

    for (int i = a; i <= b; i++) {
        printf("%d ", i * i);
    }

    return 0;
}
