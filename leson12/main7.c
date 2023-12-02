#include <stdio.h>

// Функция нахождения среднего арифметического элементов главной диагонали
double averageDiagonal(int matrix[5][5], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += matrix[i][i];
    }
    return sum / n;
}

// Функция подсчёта количества положительных элементов, больших по величине усреднённой главной диагонали
int countAboveAverage(int matrix[5][5], int n, double avg) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] > avg) {
                count++;
            }
        }
    }
    return count;
}



int main() {
    printf("Hello, F19 ДЗ 6  Больше среднего\n"
           "Написать функцию и программу, демонстрирующую работу данной функции.\n"
           "Определить количество положительных элементов квадратной матрицы, "
           "превышающих по величине среднее арифметическое всех элементов главной диагонали. "
           "Реализовать функцию среднее арифметическое главной диагонали. !\n");

    int matrix[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    double avg = averageDiagonal(matrix, 5);

    printf("%d\n", countAboveAverage(matrix, 5, avg));

    return 0;
}
