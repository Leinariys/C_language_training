#include <stdio.h>

int countOnesInBinary(int n);

int main() {
    printf("Hello, Количество 1\n"
           "Дано натуральное число N. Посчитать количество «1» в двоичной записи числа. !\n");

    int num = 0;
    scanf("%d", &num);
    printf("%d", countOnesInBinary(num));

    return 0;
}

int countOnesInBinary(int n) {
    if(n == 0) {
        return 0;
    }
    return (n % 2) + countOnesInBinary(n / 2);
}

