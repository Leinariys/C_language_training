#include <stdio.h>

int main() {
    printf("Hello, B17 ДЗ 5!\n");

    int n, i, num, sum, product, temp;

    printf("Введите ОДНО натуральное число большее 10: ");
    scanf("%d", &n);

    for (i = 10; i <= n; i++) {
        num = i;
        sum = 0;
        product = 1;

        while (num != 0) {
            temp = num % 10;

            sum += temp;
            product *= temp;

            num = num / 10;
        }

        if (sum == product) {
            printf("%d ", i);
        }
    }

    return 0;
}
