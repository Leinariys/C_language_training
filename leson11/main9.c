#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int comparator(const void *p, const void *q)
{
    char *pChar = p;
    char *qChar = q;
    return *qChar - *pChar;
    //return *((char*)q) - *((char*)p);
}

void getMaximumNumber(int num)
{
    char numStr[10];
    //форматирования и вывода данных String.format
    sprintf(numStr, "%d", num);

    //base: Это указатель на первый элемент массива, который требуется отсортировать.
    //nitems: Это количество элементов в массиве.
    //size: Это размер каждого элемента в байтах.
    //compar: Это указатель на функцию, которая сравнивает два элемента.

    //Функция strlen() принимает в качестве аргумента строку и возвращает количество символов в этой строке до первого
    // встречающегося нулевого символа (терминатор строки '\0'), не включая сам терминатор строки.
    qsort((void*)numStr, strlen(numStr), sizeof(char), comparator);

    printf("%s\n", numStr);
}

int main() {
    printf("Hello, E20 ДЗ *\n"
           "Переставить цифры\n"
           "Переставить цифры в числе так, чтобы получилось максимальное число. !\n");


    int num = 0;
    scanf("%d", &num);

    getMaximumNumber(num);

    return 0;
}



