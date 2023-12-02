#include <stdio.h>


// Функция вычисления следа матрицы
int matrixTrace(int matrix[5][5], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += matrix[i][i];
    }
    return sum;
}


int main() {
    printf("Hello, F17 \n"
           "След матрицы \n"
           "Написать функцию и программу, демонстрирующую работу данной функции, "
           "которая находит след матрицы в двумерном массиве. "
           "Показать пример ее работы на матрице из 5 на 5 элементов. "
           "След матрицы - это сумма элементов на главной диагонали. !\n");

    int matrix[5][5];
    for(int i=0; i<5; i++) {
        for (int j = 0; j < 5; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("%d\n", matrixTrace(matrix, 5));

    return 0;
}
