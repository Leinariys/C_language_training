#include <stdio.h>
#include <complex.h>

int main() {
    char char1;
    short short2;
    int int3;
    long long4;
    float float5;
    double double6;


    printf("Hello, World!\n");

    printf("char1 sizeof: %d\n", sizeof(char1));
    printf("short2 sizeof: %d\n", sizeof(short2));
    printf("int3 sizeof: %d\n", sizeof(int3));
    printf("long4 sizeof: %d\n", sizeof(long4));
    printf("float5 sizeof: %d\n", sizeof(float5));
    printf("double6 sizeof: %d\n", sizeof(double6));
    printf("---------------------\n");
    printf("char1: %c\n", char1);
    printf("short2: %d\n", short2);
    printf("int3: %d\n", int3);
    printf("long4: %l\n", long4);
    printf("float5: %f\n", float5);
    printf("double6: %lf\n", double6);


    double complex z1 = 1.0 + 3.0*I;
    double complex z2 = 1.0 - 4.0*I;

    double complex sum = z1 + z2;

    printf("Результат: %f%+fi\n", creal(sum), cimag(sum));

    unsigned int answer = 123;


    printf("Итог: %c\n", 10+50);

    return 0;
}
