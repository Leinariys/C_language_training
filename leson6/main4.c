#include <stdio.h>

int main() {
    printf("Ввести три числа и я выведу их среднее арифметическое:\n");
    float input1 = 0;
    float input2 = 0;
    float input3 = 0;
    scanf("%f%f%f", &input1, &input2, &input3);
    printf("%.2f\n", (input1 + input2 + input3) / 3);
    return 0;
}
