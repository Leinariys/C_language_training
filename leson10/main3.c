#include <stdio.h>
#include <math.h>

void printSequence(int A, int B) {
    if (A < B) {
        if (A <= B) {
            printf("%d ", A);
            printSequence(A + 1, B);
        }
    } else if (A > B) {
        if (A >= B) {
            printf("%d ", A);
            printSequence(A - 1, B);
        }
    } else {
        printf("%d ", A);
    }
}

int main() {
    printf("Hello, От A до B\n"
           "Составить рекурсивную функцию, "
           "Выведите все числа от A до B включительно, в порядке возрастания, если A < B, "
           "или в порядке убывания в противном случае.!\n");


    int A = 0, B = 0;
    scanf("%d %d", &A, &B);
    printSequence(A, B);


    return 0;
}
