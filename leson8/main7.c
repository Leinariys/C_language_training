#include <stdio.h>

int main() {
    printf("Hello, B10!\n");

    int number;
    scanf("%d", &number);

    int lastDigit = 10;
    while (number > 0) {
        if (number % 10 > lastDigit) {
            printf("NO\n");
            return 0;
        }
        lastDigit = number % 10;
        number /= 10;
    }

    printf("YES\n");

    return 0;
}
