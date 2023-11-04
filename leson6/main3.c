#include <stdio.h>

int main() {
    printf("Ввести два числа и я выведу их разность:\n");
    int input1 = 0;
    int input2 = 0;
    scanf("%d%d", &input1, &input2);
    printf("%d\n", input1 - input2);
    //printf("%d-%d=%d\n", input1, input2, input1 - input2);
    return 0;
}
