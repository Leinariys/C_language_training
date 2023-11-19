#include <stdio.h>
#include <stdbool.h>


void print_digits(int n) {
    if(n < 10) {
        printf("%d ", n);
        return;
    }
    print_digits(n / 10);
    printf("%d ", n % 10);
}


int main() {
    printf("Hello, D18 Практик 2\n"
           "Цифры слева направо\n"
           "Написать рекурсивную функцию и используя ее решить задачу. "
           "Напечатать цифры введенного натурального числа в порядке следования(слева направо) через пробел.\n"
           "void print_digits(int n)!\n");


    int num;
    scanf("%d", &num);
    print_digits(num);

    return 0;
}
