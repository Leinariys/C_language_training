#include <stdio.h>

int main() {
    printf("Hello, B19!\n");

    int num;
    int sum = 0;
    int temp;

    printf("Введите натуральное число: ");
    scanf("%d", &num);

    while (num > 0) {
        temp = num % 10;
        sum += temp;
        num = num / 10;
    }

    if (sum == 10) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}
