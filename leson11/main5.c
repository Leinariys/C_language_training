#include <stdio.h>


int main() {
    printf("Hello, E16 Д3 6\n"
           "Чаще других\n"
           "Дан массив из 10 элементов. Определить, какое число в массиве встречается чаще всего. "
           "Гарантируется, что такое число ровно 1. !\n");

    int arr[10];
    for(int i = 0; i < 10; i++) {
        scanf("%d", &arr[i]);
    }

    int maxCount = 0;
    int maxNum = 0;
    for(int i = 0; i < 10; i++) {
        int count = 0;
        for(int j = 0; j < 10; j++) {
            if(arr[i] == arr[j]) {
                count++;
            }
        }
        if(count > maxCount) {
            maxCount = count;
            maxNum = arr[i];
        }
    }

    printf(" %d\n", maxNum);

    return 0;
}

