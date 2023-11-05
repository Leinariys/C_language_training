#include <stdio.h>
#include <complex.h>


int main() {
    int num1, num2;
    printf("Ввести два числа. Если первое число больше второго, "
           "то программа печатает слово Above. Если первое число меньше второго, "
           "то программа печатает слово Less. А если числа равны, "
           "программа напечатает сообщение Equal: \n");
    scanf("%d %d", &num1, &num2);

    if (num1 > num2) {
        printf("Above\n");
    } else if (num1 < num2) {
        printf("Less\n");
    } else {
        printf("Equal\n");
    }
    return 0;
}
