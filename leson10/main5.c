#include <stdio.h>


void get_numbers() {
    int num;
    scanf("%d", &num);

    if(num == 0)
        return;

    if(num % 2 != 0)
        printf("%d ", num);

    get_numbers();
}

int main() {
    printf("Hello, Все нечетные\n"
           "Дана последовательность целых чисел через пробел, завершающаяся числом 0. "
           "Выведите все нечетные числа из этой последовательности, сохраняя их порядок. !\n");

    get_numbers();

    return 0;
}
