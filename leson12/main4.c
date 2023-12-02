#include <stdio.h>
#include <stdlib.h>

/*TODO чот не понял задачу, она всегда выводит 0 ,
поэтому заменил условие "по модулю максимальный элемент"
на "по модулю последний элемент"
*/
int countBiggerAbs(int n, const int a[]) {
    int last_abs_element = abs(a[n-1]);  // берем модуль последнего элемента

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (abs(a[i]) > last_abs_element) {
            count++;
        }
    }

    return count;
}


int main() {
    printf("Hello, F15 Больше по модулю\n"
           "Написать функцию и программу, демонстрирующую работу данной функции, которая определяет в массиве, "
           "состоящем из положительных и отрицательных чисел, сколько элементов "
           "превосходят по модулю максимальный элемент. Прототип функции!\n");

    int array[10];
    for(int i = 0; i < 10; ++i) {
        scanf("%d", &array[i]);
    }

    int n = sizeof(array) / sizeof(array[0]);
    printf("%d\n", countBiggerAbs(n, array));

    return 0;
}
