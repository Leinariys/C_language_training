#include <stdio.h>
#include <math.h>


//A(m, n) = n + 1, если m = 0
//A(m, n) = A(m - 1, 1), если m > 0 и n = 0
//A(m, n) = A(m - 1, A(m, n - 1)), если m > 0 и n > 0

int akkerman(int m, int n) {
    if (m == 0) {
        return n + 1;
    }
    else if (n == 0) {
        return akkerman(m - 1, 1);
    }
    else {
        return akkerman(m - 1, akkerman(m, n - 1));
    }
}
//todo не понял функцию 3 пункт как рисовать на бумаге
int main() {
    printf("Hello, D17 ДЗ 5 ДЗ*\n"
           "Функция Аккермана\n"
           "Функция Аккермана определяется рекурсивно для неотрицательных целых чисел m и n следующим образом:\n"
           "\n"
           "Функция Аккермана — Википедия https://ru.wikipedia.org/wiki/Функция_Аккермана \n"
           "Реализуйте данную функцию по прототипу\n"
           "int akkerman(int m, int n)!\n");

    int m, n;
    scanf("%d %d", &m, &n);
    printf("%d", akkerman(m, n));

    return 0;//Process finished with exit code -1073741571 (0xC00000FD)
}
