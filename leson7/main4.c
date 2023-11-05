#include <stdio.h>
#include <complex.h>


int main() {
    int num[5];
    printf("Напечатать сумму максимума и минимума: \n");
    for(int i = 0; i < 5; i++){
        scanf("%d", &num[i]);
    }

    int max_num = num[0];
    int min_num = num[0];

    for(int i = 0; i < 5; i++){
        if(num[i] > max_num) {
            max_num = num[i];
        }

        if(num[i] < min_num) min_num = num[i];
    }

    printf("%d\n", max_num + min_num);
    return 0;
}
