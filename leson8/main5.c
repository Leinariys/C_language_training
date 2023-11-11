#include <stdio.h>

int main() {
    printf("Hello, B8!\n");

    int number;
    scanf("%d", &number);

    int count = 0;
    while (number > 0) {
        if (number % 10 == 9) {
            count++;
        }
        number /= 10;
    }

    if (count == 1) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}
