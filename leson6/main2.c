#include <stdio.h>

int main() {
    printf("Ввести три числа и я выведу их сумму и произведение:\n");
    int input1 = 0;
    int input2 = 0;
    int input3 = 0;

    scanf("%d%d%d", &input1, &input2, &input3);

    printf("%d+%d+%d=%d\n", input1, input2, input3, input1 + input2 + input3);
    printf("%d*%d*%d=%d\n", input1, input2, input3, input1 * input2 * input3);
    return 0;
}
