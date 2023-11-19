#include <stdio.h>

int recurs_power(int n, int p) {
    if(p == 0)
        return 1;
    else
        return n * recurs_power(n, p - 1);
}

int main() {
    printf("Hello, D20 ДЗ\n"
           "Возвести в степень\n"
           "Написать рекурсивную функцию возведения целого числа n в степень p.\n"
           "int recurs_power(int n, int p)\n"
           "Используя данную функцию, решить задачу.!\n");

    int n, p;
    scanf("%d %d", &n, &p);
    printf("%d в степени %d: %d", n, p, recurs_power(n, p));

    return 0;
}


