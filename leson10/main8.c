#include <stdio.h>
#include <stdbool.h>


int acounter() {
    char c = getchar();
    if (c == '.')
        return 0;
    if (c == 'a')
        return 1 + acounter();
    else
        return acounter();
}

int main() {
    printf("Hello, D19 ДЗ 6\n"
           "Сколько раз встречается символ a\n"
           "Дана строка из английских символов, пробелов и знаков препинания. В конце строки символ точка. Необходимо реализовать рекурсивную функцию, которая считывает данную строку со стандартного потока ввода и возвращает целое число - количество символов 'a' в данной строке.\n"
           "int acounter(void)\n"
           "Используя данную функцию решить задачу.!\n");

    int count = acounter();
    printf("Символ «а» встречается %d раз.\n", count);

    return 0;
}
