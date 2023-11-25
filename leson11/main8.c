#include <stdio.h>
#include <stdbool.h>

void printDigits(int num) {
    char numStr[10];
    sprintf(numStr, "%d", num);

    for(int i = 0; numStr[i] != '\0'; i++) {
        printf("%c ", numStr[i]);
    }
}

int main() {
    printf("Hello, Цифры по порядку\n"
           "Вывести в порядке следования цифры, входящие в десятичную запись натурального числа N. !\n");

    int num = 9849849;
    //scanf("%d",&num);
    printDigits(num);

    return 0;
}

