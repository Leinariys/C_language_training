#include <stdio.h>
#include <complex.h>

int main() {
    int num1;
    int num2;
    printf("Ввести два числа и вывести их в порядке возрастания: \n");
    scanf("%d %d", &num1, &num2);

    if (num1 > num2) {
        num1 = num1 ^ num2;
        num2 = num1 ^ num2;
        num1 = num1 ^ num2;
    }

    printf("%d %d\n", num1, num2);
    return 0;
}
