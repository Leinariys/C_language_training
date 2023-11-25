#include <stdio.h>
#include <stdbool.h>


void countMultiples(int N) {
    int count[10] = {0};

    for (int i = 2; i <= N; i++) {
        for(int j = 2; j <= 9; j++) {
            if(i % j == 0) {
                count[j]++;
                break;
            }
        }
    }

    for(int j = 2; j <= 9; j++) {
        printf("%d %d ", j, count[j]);
    }
}

int main() {
    printf("Hello, Кратность прежде всего\n"
           "В диапазоне натуральных чисел от 2 до N определить, сколько из них кратны любому из чисел в диапазоне от 2 до 9. !\n");


    int N;
    scanf("%d", &N);
    countMultiples(N);

    return 0;
}

