#include <stdio.h>
#include <complex.h>

int main() {
    int num1, num2, num3;
    printf("Ввести три числа и найти наибольшее из них: \n");
    scanf("%d %d %d", &num1, &num2, &num3);

    int max_num;
    if(num1 > num2 && num1 > num3) {
        max_num = num1;
    } else if(num2 > num1 && num2 > num3) {
        max_num = num2;
    } else {
        max_num = num3;
    }

    printf("%d\n", max_num);
    return 0;
}
