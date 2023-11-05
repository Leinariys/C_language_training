#include <stdio.h>
#include <complex.h>


int main() {
    int number;
    printf("Дано трехзначное число, напечатать максимальную цифру: \n");
    scanf("%d", &number);

    int digit1 = number / 100;
    int digit2 = (number / 10) % 10;
    int digit3 = number % 10;

    int max_digit = digit1;
    if (digit2 > max_digit) max_digit = digit2;
    if (digit3 > max_digit) max_digit = digit3;

    printf(" %d\n", max_digit);
    return 0;
}
