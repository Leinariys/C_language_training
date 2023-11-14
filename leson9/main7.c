#include <stdio.h>
#include <stdbool.h>

bool growUp(int number1);

int main() {
    printf("Hello, C15 Практ  Цифры по возрастанию\n"
           "\n"
           "Составить функцию логическую функцию, которая определяет, верно ли, что в заданном "
           "числе все цифры стоят по возрастанию. Используя данную функцию решить задачу.\n"
           "\n"
           "int growUp(int n)!\n");


    int number1 = 10;
    scanf("%d", &number1);

    if (growUp(number1)) {
        printf("YES \n");
    } else {
        printf("NO \n");
    }

    return 0;
}


bool growUp(int n) {
    int last = 10;
    while (n != 0) {
        if (n % 10 > last)
            return false;
        last = n % 10;
        n /= 10;
    }
    return true;
}
