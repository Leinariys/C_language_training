#include <stdio.h>

int main() {
    printf("Hello, B20!\n");

    int num;
    int i;
    int isPrime = 1;

    printf("Введите натуральное число: ");
    scanf("%d",&num);

    for(i = 2; i <= num/2; i++){
        if(num % i == 0){
            isPrime = 0;
            break;
        }
    }

    if(isPrime == 1 && num > 1){
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}
