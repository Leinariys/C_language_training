#include <stdio.h>
#include <math.h>


float cosinus(float x);
int factorial(int number1);


int main() {
    printf("Hello, C13 Практика \n"
           "Вычислить cos\n"
           "Составить функцию, которая вычисляет синус как сумму ряда (с точностью 0.001)\n"
           "\n"
           "cos(x) = 1 - x2/2! + x4/4! - x6/6! + ... \n"
           "(x в радианах)\n"
           "float cosinus(float x)!\n");

    float number1 = 10;
    scanf("%f", &number1);

    float result = cosinus(number1);
    printf("Косинус %.0f равен %.3f\n", number1, result);


    return 0;
}


float cosinus(float x) {
    x = x * (3.14159 / 180);
    float term = 1, sum = 0;
    for(int i = 0; fabs(term) > 0.001; i++) {
        term = pow(-1, i) * pow(x, 2 * i) / factorial(2 * i);
        sum += term;
    }
    return sum;
}


int factorial(int number1) {
    int result = 1;
    for (int i = 1; i <= number1; ++i) {
        result *= i;
    }

    return result;
}
