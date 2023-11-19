#include <stdio.h>


void printDigitsInReverse(int n);

int main() {
    printf("Hello, В обратном порядке\n"
           "Дано целое неотрицательное число N. "
           "Выведите все его цифры по одной, в обратном порядке, разделяя их пробелами или новыми строками. !\n");

    int num = 0;
    scanf("%d", &num);
    printDigitsInReverse(num);

    return 0;
}


void printDigitsInReverse(int n) {
    if(n == 0) {
        return;
    }
    printf("%d ", n % 10);
    printDigitsInReverse(n / 10);
}
