#include <stdio.h>

int main() {
    printf("Трехзначное число, выведу произведение чисел:\n");
    int input0 = 0;

    scanf("%d", &input0);
    //printf("%d\n", input0 / 1 % 10);
    //printf("%d\n", input0 / 10 % 10);
    //printf("%d\n", input0 / 100 % 10);

    printf("%d\n",
           ((input0 / 1) % 10) *
           ((input0 / 10) % 10) *
           ((input0 / 100) % 10)
    );
    return 0;
}
