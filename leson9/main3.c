#include <stdio.h>
#include <math.h>

unsigned long long grainsOnCell(int cell) {
    return (unsigned long long) 1 << (cell - 1);
    return (unsigned long long) pow(2, cell - 1);
}

int main() {
    printf("Hello, C6 ДЗ \n"
           "Сколько зерен на доске\n"
           "\n"
           "Когда создатель шахмат, древнеиндийский мудрец и математик Сисса бен Дахир, "
           "показал своё изобретение Правителю страны, тому так понравилась игра, "
           "что он позволил изобретателю право самому выбрать награду. "
           "Мудрец попросил у Повелителя за первую клетку шахматной доски заплатить ему одно зерно риса, "
           "за второе — два, за третье — четыре и т. д., удваивая количество зёрен на каждой следующей клетке. "
           "Помоги повелителю сосчитать сколько зерен на какой клетке лежит.\n"
           "\n"
           "Необходимо составить функцию, которая определяет, сколько зерен попросил положить на N-ую клетку "
           "изобретатель шахмат (на 1-ую – 1 зерно, на 2-ую – 2 зерна, на 3-ю – 4 зерна, …)!\n");

    int cell = 64;
    scanf("%d", &cell);
    //todo ограничения на ввод
    unsigned long long grains = grainsOnCell(cell);
    printf("На клетке %d находится %llu зерен\n", cell, grains);

    return 0;

}