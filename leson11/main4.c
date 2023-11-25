#include <stdio.h>

int main() {
    printf("Hello, E13 ДЗ 5\n"
           "Вторая с конца ноль \n"
           "Считать массив из 10 элементов и отобрать в другой массив все числа, "
           "у которых вторая с конца цифра (число десятков) – ноль. !\n");

    int arr[10];
    for(int i = 0; i < 10; i++) {
        scanf("%d", &arr[i]);
    }

    int arrResult[10];
    int arrResultIndex = 0;
    for(int i = 0; i < 10; i++) {
        if((arr[i] % 100) / 10 == 0) {
            arrResult[arrResultIndex] = arr[i];
            arrResultIndex++;
        }
    }

    for(int i = 0; i < arrResultIndex; i++) {
        printf("%d ", arrResult[i]);
    }
    printf("\n");


    return 0;
}


