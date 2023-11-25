#include <stdio.h>
#include <math.h>


int main() {
    printf("Hello, E17\n"
           "Только один раз\n"
           "Дан массив из 10 элементов. В массиве найти элементы, которые в нем встречаются только один раз, и вывести их на экран. ");

    int arr[10];
    for(int i = 0; i < 10; i++) {
        scanf("%d", &arr[i]);
    }

    for(int i = 0; i < 10; i++) {
        int count = 0;
        for(int j = 0; j < 10; j++) {
            if(arr[i] == arr[j]) {
                count++;
            }
        }
        if(count == 1) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");


    return 0;
}

