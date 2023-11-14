#include <stdio.h>
#include <stdbool.h>


bool theSumDigitsEqualProduct(int number1);

int main() {
    printf("Hello, C17 ДЗ\n"
           "Сумма цифр равна произведению\n"
           "\n"
           "Составить логическую функцию, которая определяет, верно ли, что в данном числе сумма цифр равна произведению.\n"
           "\n"
           "int is_happy_number(int n)!\n");



    int number1 = 10;
    scanf("%d", &number1);

    if (theSumDigitsEqualProduct(number1)) {
        printf("YES \n");
    } else {
        printf("NO \n");
    }

    return 0;
}


bool theSumDigitsEqualProduct(int number1) {
    int sum = 0, prod = 1, digit;
    while (number1 != 0) {
        digit = number1 % 10;
        sum += digit;
        prod *= digit;
        number1 /= 10;
    }
    return sum == prod;
}
