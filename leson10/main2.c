#include <stdio.h>



void print_num(int num) {
    if(num == 0) {
        return;
    }

    print_num(num / 10);
    printf("%d ", num % 10);
}

int main() {
    printf("Hello, В прямом порядке\n"
           "Дано натуральное число N. Выведите все его цифры по одной, "
           "в прямом порядке, разделяя их пробелами или новыми строками. "
           "Необходимо реализовать рекурсивную функцию.!\n");

    int num = 0;
    scanf("%d", &num);
    print_num(num);

    return 0;
}
